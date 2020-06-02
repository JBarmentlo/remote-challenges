#include "includes.h"
#include "stdio.h"
#include <unistd.h>

int		is_valid_shield_pos(t_master *bitmaps, t_ship *shield, t_map *contact, int pos)
{
//	dprintf(2, "obstacles: \n");
//	write_map(&bitmaps->obstacles);
//	write_map(contact);
//	dprintf(2, "and == 0: %d\n", is_bitwise_and_zero(&bitmaps->obstacles, contact));
	if (is_bitwise_and_zero(&bitmaps->obstacles, contact))
		return (1);
	return (0);
}

void	make_shield_heatmap(t_master *bitmaps, t_ship *shield)
{
	int		pos;
	t_map	contact;
	t_map	shipmap;

	shipmap = new_map();
	shipmap.one = MAXO;
	bitmaps->obstacles = map_or(&bitmaps->obstacles, &bitmaps->hit);
	pos = 0;
	while (pos < 100)
	{
		bitmaps->heatmap[pos] = 0;
		pos++;
	}
	pos = 0;
	while (pos < 100)
	{
		contact = shield_contact_from_pos(shield, pos);
		if (is_valid_shield_pos(bitmaps, shield, &contact, pos))
		{
			apply_ship_map_to_heatmap(shipmap, bitmaps);
		}
		pos++;
		right_shift(&shipmap, 1);
	}
	write_heatmap(bitmaps->heatmap);
}

int		choose_shot_shield(t_master *bitmaps, t_ship *shield)
{
	t_map	map;

	write_map(&bitmaps->shield_pos);
	write_map(&bitmaps->hit);
	dprintf(2, "shield pos nb: %d \n", count(&bitmaps->shield_pos));
	make_shield_heatmap(bitmaps, shield);
	return (heatmap_pick_highest(bitmaps));
}

int		shoot_for_shield(t_master *bitmaps)
{
	int		last_shot;
	int		result;
	t_ship	*shield;

	result = 0;
	last_shot = 0;
	shield = &bitmaps->shield_fleet->ships[0];
	while (result != SUNK)
	{
		last_shot = choose_shot_shield(bitmaps, shield), bitmaps;
		dprintf(2, "shield shot %d\n", last_shot);
		shoot(last_shot, bitmaps);
		result = handle_input(bitmaps, last_shot);
	}
	return (result);
}

void	update_shield_pos_hit(t_master *bitmaps, int last_pos)
{
	t_map	tmp;
	t_ship	*shield;
	int		nb;
	int		i;

	shield = &bitmaps->shield_fleet->ships[0];
	tmp = shield_contact_from_pos(shield, last_pos);
	bitmaps->shield_pos = substract_map(bitmaps->shield_pos, tmp);
	bitmaps->shield_pos = substract_map(bitmaps->shield_pos, bitmaps->hit);
	bitmaps->shield_pos = substract_map(bitmaps->shield_pos, bitmaps->sunk);

	tmp.one = MAXO;
	tmp.two = 0;
	i = 0;
	nb = 0;
	while (i < 100)
	{
		if (is_bitwise_and_one(&tmp, &bitmaps->shield_pos))
			nb += 1;
		i++;
	}
	bitmaps->shield_pos_nb = nb;
	return ;
}

void	update_shield_pos(t_master *bitmaps, int last_pos)
{
	t_map	tmp;
	t_ship	*shield;
	int		nb;
	int		i;

	shield = &bitmaps->shield_fleet->ships[0];
	tmp = shield_contact_from_pos(shield, last_pos);
	bitmaps->shield_pos = map_and(&bitmaps->shield_pos, &tmp);
	bitmaps->shield_pos = substract_map(bitmaps->shield_pos, bitmaps->hit);
	bitmaps->shield_pos = substract_map(bitmaps->shield_pos, bitmaps->sunk);

	tmp.one = MAXO;
	tmp.two = 0;
	i = 0;
	nb = 0;
	while (i < 100)
	{
		if (is_bitwise_and_one(&tmp, &bitmaps->shield_pos))
			nb += 1;
		i++;
	}
	bitmaps->shield_pos_nb = nb;
	return ;
}