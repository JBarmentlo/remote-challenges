#include "includes.h"
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

static void	remove_left_cols(t_map *out, int cols)
{
	static t_map	left_co = {LCOLONE , LCOLTWO};
	int	tmp;

	tmp = cols;
	while (cols)
	{
		*out = map_not(out);
		*out = map_or(out, &left_co);
		*out = map_not(out);
		right_shift(&left_co, 1);
		cols--;
	}
	left_shift(&left_co, tmp);
}

static void	remove_right_cols(t_map *out, int cols)
{
	static t_map	right_co = {RCOLONE , RCOLTWO};
	int	tmp;

	tmp = cols;
	left_shift(&right_co, 5);
	while (cols)
	{
		*out = map_not(out);
		*out = map_or(out, &right_co);
		*out = map_not(out);
		left_shift(&right_co, 1);
		cols--;
	}
	right_shift(&right_co, tmp + 5);
}

t_map	shield_contact_from_pos(t_ship *shield, int pos)
{
	t_map			tmp;
	t_map			out;

	out = shield->contact;
	if (pos % 10 < 3)
	{
		remove_left_cols(&out, 2 - (pos % 10));
	}
	if (pos % 10 > 7)
	{
		remove_right_cols(&out, (pos % 10) - 7);
	}
	both_shift(&out, pos - 22);
	return (out);
}

void	make_contact_shield(t_ship *shield)
{
	shield->contact.one = 0b1111100000111110000011111000001111100000111110000000000000000000;
	shield->contact.two = 0;
}

void	make_ship(t_ship *out)
{
	out->height = 1;
	out->width = 1;
	out->size = 1;
	out->map.one = 0;
	out->map.two = 0;
	out->pos[0] = 0;


	make_map_from_pos(out);
	make_contact_shield(out);
}

static void	init_live_shield(t_fleet *fleet)
{
	int	i;

	i = 0;
	while (i < 5)
	{	if (i == 0)
			fleet->live_ships[0] = 1;
		if (i != 0)
			fleet->live_ships[i] = 0;
		i++;
	}
	fleet->nb_live_ships = 1;
	fleet->nb_last_live_ship = 0;
}

t_fleet	*make_shield_fleet(t_master *bitmaps)
{
	t_fleet	*out;
	int		i;

	out = malloc(sizeof(t_fleet));
	bzero(out, sizeof(t_fleet));
	init_live_shield(out);
	make_ship(&out->ships[0]);
	bitmaps->shield_fleet = out;
	out->odds = 1.0;
	return (out);
}
