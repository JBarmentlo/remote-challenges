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
	bitmaps->obstacles = map_or(&bitmaps->obstacles, &bitmaps->miss);
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
			dprintf(2, "VALIUD SHIEALD POS\n");
			apply_ship_map_to_heatmap(shipmap, bitmaps);
		}
		pos++;
		right_shift(&shipmap, 1);
	}
	//write_heatmap(bitmaps);
}

int		choose_quarter(t_master *bitmaps)
{
		if (is_pos_one(&bitmaps->shot, 77) == 0)
			return (77);
		if (is_pos_one(&bitmaps->shot, 22) == 0)
			return (22);
		if (is_pos_one(&bitmaps->shot, 27) == 0)
			return (27);
		if (is_pos_one(&bitmaps->shot, 72) == 0)
			return (72);
		return (-1);
}

int		choose_shot_shield(t_master *bitmaps, t_ship *shield)
{
	t_map	map;

	map = new_map();
	if (bitmaps->blocked.one == 0 && bitmaps->blocked.two == 0)
		if (choose_quarter(bitmaps) != -1)
			return (choose_quarter(bitmaps));
	make_shield_heatmap(bitmaps, shield);
	return (heatmap_pick_highest(bitmaps));
}

void	shoot_for_shield(t_master *bitmaps, t_ship *shield)
{
	int	shield_dead;

	shield_dead = 0;
	while (!shield_dead)
	{
		shoot(choose_shot_shield(bitmaps, shield), bitmaps);
	}
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
	bitmaps->shield_pos = substract_map(bitmaps->shield_pos, bitmaps->miss);
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