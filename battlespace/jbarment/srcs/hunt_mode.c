#include "includes.h"
#include <stdio.h>

static int	splice(t_ship *ship, t_map sunk, t_master *bitmaps)
{
	int		pos;
	t_map	tmp;
	int		possible;

	tmp = ship->map;
	possible = -1;
	pos = 0;
	while (pos < 100)
	{
		if (is_pos_valid_no_obst(ship, pos, bitmaps) && equals(tmp, map_and(&sunk, &tmp)))
		{
			possible = pos;
			if (count(&tmp) < count(&sunk))
				bitmaps->annexe_sunk =1;
		}
		pos++;
		right_shift(&tmp, 1);
	}
	return (possible);
}

void	handle_cock_block_fleet(t_master *bitmaps, t_fleet *fleet)
{
	t_id	sunk_id;

	bitmaps->current_sunk = bitmaps->current_hunt;
	if (count(&bitmaps->current_sunk) != 1)
	{
		sunk_id = identify_sunk_ship_fleet(fleet, bitmaps);

		handle_sunk_ship(bitmaps, sunk_id);
	}
	bitmaps->current_hunt = new_map();
	return ;
}

// ASSUMES SHIPS ARE SORTED BY SIZE
t_id	identify_sunk_ship_fleet(t_fleet *fleet, t_master *bitmaps)
{
	int		i;
	t_id	out;

	i = 0;
	if (count(&bitmaps->current_sunk) == 1)
	{
		out.fleet = bitmaps->shield_fleet;
		out.is_90 = 0;
		out.num = 0;
		out.ship = &bitmaps->shield_fleet->ships[0];
		out.pos = splice(&bitmaps->shield_fleet->ships[0], bitmaps->current_sunk, bitmaps);
		return (out);
	}

	while (i < 5)
	{
		if (fleet->live_ships[i] == 1)
		{
			if (splice(&fleet->ships[i], bitmaps->current_sunk, bitmaps) != -1)
			{
				out.fleet = fleet;
				out.is_90 = 0;
				out.num = i;
				out.ship = &fleet->ships[i];
				out.pos = splice(&fleet->ships[i], bitmaps->current_sunk, bitmaps);
				return (out);
			}
			if (splice(&fleet->ships_90[i],  bitmaps->current_sunk, bitmaps) != -1)
			{
				out.fleet = fleet;
				out.is_90 = 0;
				out.num = i;
				out.ship = &fleet->ships_90[i];
				out.pos = splice(&fleet->ships_90[i], bitmaps->current_sunk, bitmaps);
				return (out);
			}
		}
		i++;
	}
}

int		hunt_mode(t_master *bitmaps)
{
	int		last_shot;
	int		result;
	t_map	tmp;

	dprintf(2, "hunt mode\n");
	last_shot = 0;
	result = 0;
	while (last_shot != -1 && result != SUNK)
	{
		last_shot = choose_hunt_shot(bitmaps);
		if (last_shot != -1)
		{
			if (bitmaps->shield_pos_nb < 7 && bitmaps->shield_fleet->live_ships[0] == 1)
			{
				tmp = bitmaps->current_hunt;
				bitmaps->current_hunt = new_map();
				shoot_for_shield(bitmaps); //FUCK UP ?
				bitmaps->current_hunt = tmp;
				last_shot = 0;
				dprintf(2, "done shield");
			}
			else
			{
				result = shoot(last_shot, bitmaps);
			}
		}
	}
	if (last_shot == -1)
	{
		dprintf(2, "getting cock blocked\n");
		handle_cock_block_fleet(bitmaps, bitmaps->nation_fleet);
		write_map(&bitmaps->current_hunt);
	}
	dprintf(2, "Exiting hunt mode\n");
	return (result);
}

int		choose_hunt_shot(t_master *bitmaps)
{
	if (make_surround_map(bitmaps, bitmaps->nation_fleet) == 0)
	{
		return (-1);
	}
//	dprintf(2, "hunt out heat\n");
//	write_heatmap(bitmaps->heatmap);
//	dprintf(2, "current:\n");
//	write_map(&bitmaps->current_hunt);	
//	dprintf(2, "sunk:\n");
//	write_map(&bitmaps->sunk);
	return (heatmap_pick_highest(bitmaps));
}

int		get_blocked(t_master *bitmaps)
{
	int		i;

	i = 0;
	while (i < 100)
	{
		if (is_pos_one(&bitmaps->blocked, i) == 1)
			return (i);
		i++;
	}
	return (-1);
}
void	finish_blocked(t_master *bitmaps)
{
	int	last_shot;

	bitmaps->blocked = substract_map(bitmaps->blocked, bitmaps->sunk);
	last_shot = 0;
	while (last_shot != -1)
	{
		last_shot = get_blocked(bitmaps);
		shoot(last_shot, bitmaps);
	}
	
}