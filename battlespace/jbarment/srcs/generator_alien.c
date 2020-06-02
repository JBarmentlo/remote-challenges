#include "includes.h"
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

void	make_alien_ship_0(int size, t_ship *out)
{
	int		i;

	out->height = 4;
	out->width = 3;
	out->size = size;
	out->map.one = 0;
	out->map.two = 0;
	out->pos[0] = 1;
	out->pos[1] = 11;
	out->pos[2] = 21;
	out->pos[3] = 30;
	out->pos[4] = 32;
	make_map_from_pos(out);
	make_contact_from_map(&out->map, &out->contact);
}

void	make_alien_ship_180_0(int size, t_ship *out)
{
	int		i;

	out->height = 4;
	out->width = 3;
	out->size = size;
	out->map.one = 0;
	out->map.two = 0;
	out->pos[0] = 0;
	out->pos[1] = 2;
	out->pos[2] = 11;
	out->pos[3] = 21;
	out->pos[4] = 31;
	make_map_from_pos(out);
	make_contact_from_map(&out->map, &out->contact);
}

void	make_alien_ship_270_0(int size, t_ship *out)
{
	int		i;

	out->height = 3;
	out->width = 4;
	out->size = size;
	out->map.one = 0;
	out->map.two = 0;
	out->pos[0] = 3;
	out->pos[1] = 10;
	out->pos[2] = 11;
	out->pos[3] = 12;
	out->pos[4] = 23;
	make_map_from_pos(out);
	make_contact_from_map(&out->map, &out->contact);
}

void	make_alien_ship_1(int size, t_ship *out)
{
	int		i;

	out->height = 3;
	out->width = 3;
	out->size = size;
	out->map.one = 0;
	out->map.two = 0;
	out->pos[0] = 1;
	out->pos[1] = 10;
	out->pos[2] = 12;
	out->pos[3] = 21;
	make_map_from_pos(out);
	make_contact_from_map(&out->map, &out->contact);
}

void	make_alien_ship_2(int size, t_ship *out)
{
	int		i;

	out->height = 3;
	out->width = 3;
	out->size = size;
	out->map.one = 0;
	out->map.two = 0;
	out->pos[0] = 2;
	out->pos[1] = 11;
	out->pos[2] = 20;
	make_map_from_pos(out);
	make_contact_from_map(&out->map, &out->contact);
}

void	make_alien_ship_4(int size, t_ship *out)
{
	int		i;

	out->height = 2;
	out->width = 1;
	out->size = size;
	out->map.one = 0;
	out->map.two = 0;
	out->pos[0] = 0;
	out->pos[1] = 10;
	make_map_from_pos(out);
	make_contact_from_map(&out->map, &out->contact);
}



void	make_alien_ship_90_0(int size, t_ship *out)
{
	int		i;

	out->height = 3;
	out->width = 4;
	out->size = size;
	out->map.one = 0;
	out->map.two = 0;
	out->pos[0] = 0;
	out->pos[1] = 11;
	out->pos[2] = 12;
	out->pos[3] = 13;
	out->pos[4] = 20;
	make_map_from_pos(out);
	make_contact_from_map(&out->map, &out->contact);
}

void	make_alien_ship_90_1(int size, t_ship *out)
{
	int		i;

	out->height = 3;
	out->width = 3;
	out->size = size;
	out->map.one = 0;
	out->map.two = 0;
	out->pos[0] = 1;
	out->pos[1] = 10;
	out->pos[2] = 12;
	out->pos[3] = 21;
	make_map_from_pos(out);
	make_contact_from_map(&out->map, &out->contact);
}

void	make_alien_ship_90_2(int size, t_ship *out)
{
	int		i;

	out->height = 3;
	out->width = 3;
	out->size = size;
	out->map.one = 0;
	out->map.two = 0;
	out->pos[0] = 0;
	out->pos[1] = 11;
	out->pos[2] = 22;
	make_map_from_pos(out);
	make_contact_from_map(&out->map, &out->contact);
}

void	make_alien_ship_90_4(int size, t_ship *out)
{
	int		i;

	out->height = 1;
	out->width = 2;
	out->size = size;
	out->map.one = 0;
	out->map.two = 0;
	out->pos[0] = 0;
	out->pos[1] = 1;
	make_map_from_pos(out);
	make_contact_from_map(&out->map, &out->contact);
}

t_fleet	*make_alien_fleet(t_master *bitmaps)
{
	t_fleet	*out;
	int		i;

	out = malloc(sizeof(t_fleet));
	bzero(out, sizeof(t_fleet));
	init_live_ships(out);
	make_alien_ship_0(5, &(out->ships[0]));
	make_alien_ship_90_0(5, &(out->ships_90[0]));
	make_alien_ship_1(4, &(out->ships[1]));
	make_alien_ship_90_1(4, &(out->ships_90[1]));
	make_alien_ship_2(3, &(out->ships[2]));
	make_alien_ship_90_2(3, &(out->ships_90[2]));
	make_alien_ship_2(3, &(out->ships[3]));
	make_alien_ship_90_2(3, &(out->ships_90[3]));
	make_alien_ship_4(2, &(out->ships[4]));
	make_alien_ship_90_4(2, &(out->ships_90[4]));
	bitmaps->alien_fleet = out;
	out->odds = 1.0;
	return (out);
}
