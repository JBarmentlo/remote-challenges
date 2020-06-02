#include "includes.h"
#include <stdlib.h>
#include <stdio.h>

void		print_ship(t_ship *ship)
{
	int	i;
	int	piece;

	piece = 0;
	i = 0;
	printf("width: %d\n height: %d\n size: %d\n", ship->width, ship->height, ship->size);
	while (i < ship->size)
	{
		printf("%d  ", ship->pos[i]);
		i++;
	}
	printf("\n");
	print_map(&(ship->map));
	printf("\n contact: \n");
	print_map(&(ship->contact));

	printf("\n");
}

void		print_fleet(t_fleet *fleet)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (fleet->live_ships[i])
		{
			print_ship(&(fleet->ships[i]));
			print_ship(&(fleet->ships_90[i]));
		}
		i++;
	}
}

int			is_pos_valid(t_ship *ship, int pos, t_master *bitmaps)
{
	int		posi;
	int		posj;
	t_map	ship_map;

	posi = pos / 10;
	if ((posi + ship->height) > 10) // check these bitches
		return (0);
	posj = pos % 10;
	if ((posj + ship->width) > 10)
		return (0);
	ship_map = ship->map;
	right_shift(&ship_map, pos);
	if (is_bitwise_and_zero(&(bitmaps->obstacles), &ship_map))
		return (1);
	return (0);
}

// APLIES TO TMP
void		apply_ship_map_to_heatmap(t_map ship_map,t_master *bitmaps)
{
	unsigned long	mask;
	int				i;

	bitmaps->total += 1;
	mask = MAXO;
	i = 0;
	while (i < 64)
	{
		if ((ship_map.one & mask) != 0)
		{
			bitmaps->heatmap_tmp[i] += 1;
		}
		mask = mask >> 1;
		i++;
	}
	mask = MAXO;
	while (i < 100)
	{
		if ((ship_map.two & mask) != 0)
		{
			bitmaps->heatmap_tmp[i] += 1;
		}
		mask = mask >> 1;
		i++;
	}
}

void		make_heatmap_bit(t_master *bitmaps, t_fleet *fleet, int ship_no, t_map ship_map)
{
	int		pos;
	t_map	tmp_obstacles;
	t_map	tmp_ship_map;
	t_ship	*ship;

	while ((ship_no < 5) && (fleet->live_ships[ship_no] == 0))
		ship_no++;
	if (ship_no == 0)
		printf("ZERO\n");
	if (ship_no == 1)
		printf("ONE\n");
	if (ship_no == 5)
	{
		apply_ship_map_to_heatmap(ship_map, bitmaps);
		bitmaps->total += 1;
		//printf("END\n");
		//printf("shipmap\n");
		//print_map(&ship_map);
		//printf("obstacles\n");
		//print_map(&bitmaps->obstacles);
		return;
	}
	pos = 0;
	while (pos < 100)
	{
		ship = &fleet->ships[ship_no];
		if (is_pos_valid(ship, pos, bitmaps))
		{
			tmp_obstacles = bitmaps->obstacles;
			tmp_ship_map = ship_map;
			//printf("ship: %d\n pos: %d \n",ship_no, pos);
			add_ship(bitmaps, &ship_map, ship, pos);
			//printf("shipmap\n");
			//print_map(&ship_map);
			make_heatmap_bit(bitmaps, fleet, ship_no + 1, ship_map); //bitmaps->contact forgotten for now
			ship_map = tmp_ship_map;
			bitmaps->obstacles = tmp_obstacles;
		}
		ship = &fleet->ships_90[ship_no];
		if (is_pos_valid(ship, pos, bitmaps))
		{
			tmp_obstacles = bitmaps->obstacles;
			tmp_ship_map = ship_map;
			//printf("ship: %d\n pos: %d \n",ship_no, pos);
			add_ship(bitmaps, &ship_map, ship, pos);
			//printf("shipmap\n");
			//print_map(&ship_map);
			make_heatmap_bit(bitmaps, fleet, ship_no + 1, ship_map);
			ship_map = tmp_ship_map;
			bitmaps->obstacles = tmp_obstacles;
		}
		pos++;
	}
	return;
}

/*
// WILL CHANGE OBSTACLES MAP MAKE A TMP !! ASSUMES POS TO BE VALID
// Updates heatmap, for now no contact
void	drop_ship(t_ship *ship, int pos, t_master *bitmaps)
{
	int	i;
	int square;

	i = 0;
	while (i < ship->size)
	{
		square = pos + ship->pos[i];
		bitmaps->obstacles[square] = 1;
		if (square > 9)
			bitmaps->obstacles[square - 10] = 1;
		if (square < 90)
			bitmaps->obstacles[square + 10] = 1;
		if (square % 10 < 9)
			bitmaps->obstacles[square + 1] = 1;
		if (square % 10 > 0)
			bitmaps->obstacles[square - 1] = 1;
		i++;
	}
}

void	add_ship_to_heatmap(t_master *bitmaps, t_ship *ship, int pos)
{
	int	i;

	i = 0;
	while (i < ship->size)
	{
		bitmaps->heatmap[pos + ship->pos[i]] += 1;
		i++;
	}
}

int		make_heatmap(t_fleet *fleet, t_master *bitmaps, int ship_no)
{
	t_byte	*tmp;
	t_ship	*ship;
	t_ship	*ship_90;
	int		next_ship;
	int		pos;

	if (ship_no > fleet->nb_last_live_ship)
	{
		bitmaps->total += 1;
		return (1);
	}
	if (fleet->ships[ship_no].size == 4)
		printf("%d\n", fleet->ships[ship_no].size);
	pos = 0;
	ship = &(fleet->ships[ship_no]);
	ship_90 = &(fleet->ships_90[ship_no]);
	tmp = malloc(100);
	while (pos < 100)
	{
		if (is_pos_valid(ship, pos, bitmaps->obstacles))
		{
			copy_map_data(bitmaps->obstacles, tmp);
			drop_ship(ship, pos, bitmaps);
			if (make_heatmap(fleet, bitmaps, ship_no + 1));
				add_ship_to_heatmap(bitmaps, ship, pos);
			copy_map_data(tmp, bitmaps->obstacles);
		}
		if (is_pos_valid(ship_90, pos, bitmaps->obstacles))
		{
			copy_map_data(bitmaps->obstacles, tmp);
			drop_ship(ship_90, pos, bitmaps);
			if (make_heatmap(fleet, bitmaps, ship_no + 1));
				add_ship_to_heatmap(bitmaps, ship_90, pos);
			copy_map_data(tmp, bitmaps->obstacles);
		}
		pos++;
	}
	if (ship_no == 0)
		printf("total %d\n", bitmaps->total);
	return (0);
}
*/