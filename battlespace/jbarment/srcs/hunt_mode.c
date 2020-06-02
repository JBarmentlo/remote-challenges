#include "includes.h"
#include <stdio.h>

static int	splice(t_ship *ship, t_map sunk, t_master *bitmaps)
{
	int		pos;
	t_map	tmp;
	int		possible;

	tmp = ship->map;
	possible = 0;
	pos = 0;
	while (pos < 100)
	{
		if (is_pos_valid(ship, pos, bitmaps) && equals(tmp, map_and(&sunk, &tmp)))
		{
			possible = 1;
			if (count(&tmp) < count(&sunk))
				bitmaps->annexe_sunk =1;
		}
		pos++;
		right_shift(&tmp, 1);
	}
	return (possible);
}

// ASSUMES SHIPS ARE SORTED BY SIZE
t_id	identify_sunk_ship_fleet(t_fleet *fleet, t_master *bitmaps)
{
	int		i;
	t_id	out;

	i = 0;
	while (i < 5)
	{
		if (fleet->live_ships[i] == 1)
		{
			if (splice(&fleet->ships[i], bitmaps->current_sunk, bitmaps) == 1)
			{
				out.fleet = fleet;
				out.is_90 = 0;
				out.num = i;
				out.ship = &fleet->ships[i];
				return (out);
			}
			if (splice(&fleet->ships_90[i],  bitmaps->current_sunk, bitmaps) == 1)
			{
				out.fleet = fleet;
				out.is_90 = 0;
				out.num = i;
				out.ship = &fleet->ships_90[i];
				return (out);
			}
			i++;
		}
	}

}

int		hunt_mode(t_master *bitmaps)
{
	int	last_shot;
	int	result;

	dprintf(2, "hunt mode\n");
	last_shot = 0;
	result = 0;
	while (last_shot != -1 && result != SUNK)
	{
//		write_map(&bitmaps->obstacles);
//		write_map(&bitmaps->hit);
//		write_map(&bitmaps->current_hunt);
		last_shot = choose_hunt_shot(bitmaps);
//		write_heatmap(bitmaps->heatmap);
		if (last_shot != -1)
		{
			shoot(last_shot, bitmaps);
			result = handle_input(bitmaps, last_shot);
		}
	}
	dprintf(2, "Exiting hunt mode\n");
	return (result);
}

int		choose_hunt_shot(t_master *bitmaps)
{
	if (make_surround_map(bitmaps, bitmaps->nation_fleet) == 0)
	{
		write_heatmap(bitmaps->heatmap);
		write_map(&bitmaps->hit);
		write_map(&bitmaps->current_hunt);
		printf("getting cock blocked\n");
		dprintf(2, "getting cock blocked\n");
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