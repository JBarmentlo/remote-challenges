#include "includes.h"
#include <strings.h>
#include <stdlib.h>

t_map	new_map(void)
{
	t_map	map;
	bzero(&map, sizeof(map));
	return (map);
}

t_ship	make_nation_ship(int size)
{
	t_ship	out;
	int		i;

	out.height = size;
	out.width = 1;
	out.size = size;
	i = 0;
	while (i < size)
	{
		out.pos[i] = 10 * i;
		i++;
	}
	return (out);
}

t_ship	make_nation_ship_90(int size)
{
	t_ship	out;
	int		i;

	out.height = 1;
	out.width = size;
	out.size = size;
	i = 0;
	while (i < size)
	{
		out.pos[i] = i;
		i++;
	}
	return (out);
}

void	init_live_ships(t_fleet *fleet)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		fleet->live_ships[i] = 1;
		i++;
	}
	fleet->nb_live_ships = 5;
	fleet->nb_last_live_ship = 4;
}

t_fleet	*make_nation_fleet(void)
{
	t_fleet	*out;
	int		i;

	out = malloc(sizeof(t_fleet));
	bzero(out, sizeof(t_fleet));
	init_live_ships(out);
	out->ships[0] = make_nation_ship(5);
	out->ships_90[0] = make_nation_ship_90(5);
	out->ships[1] = make_nation_ship(4);
	out->ships_90[1] = make_nation_ship_90(4);
	out->ships[2] = make_nation_ship(3);
	out->ships_90[2] = make_nation_ship_90(3);
	out->ships[3] = make_nation_ship(3);
	out->ships_90[3] = make_nation_ship_90(3);
	out->ships[4] = make_nation_ship(2);
	out->ships_90[4] = make_nation_ship_90(2);
	return (out);
}
