#include "includes.h"
#include "stdio.h"

// 0.2 approx for division by num of ships for annexe
void		apply_contact_to_heatmap(t_map contact, t_master *bitmaps, int size)
{
	unsigned long	mask;
	int				i;

	bitmaps->total += 1;
	mask = MAXO;
	i = 0;
	while (i < 64)
	{
		if ((contact.one & mask) != 0)
		{
			bitmaps->heatmap_tmp[i] += (0.2 / size);
		}
		mask = mask >> 1;
		i++;
	}
	mask = MAXO;
	while (i < 100)
	{
		if ((contact.two & mask) != 0)
		{
			bitmaps->heatmap_tmp[i] += (0.2 / size);
		}
		mask = mask >> 1;
		i++;
	}
}

static int	splice(t_ship *ship, t_map hunted, t_master *bitmaps)
{
	int		pos;
	t_map	tmp;
	int		possible;

	tmp = ship->map;
	possible = 0;
	pos = 0;
	while (pos < 100)
	{
		if (is_pos_valid(ship, pos, bitmaps) && equals(hunted, map_and(&hunted, &tmp)))
		{
			possible = 1;
			apply_ship_map_to_heatmap(substract_map(tmp, hunted), bitmaps);
			if (bitmaps->annexe_sunk == 0)
				apply_contact_to_heatmap(substract_map(contact_pos(ship, pos), bitmaps->obstacles), bitmaps, ship->size);
		}
		pos++;
		right_shift(&tmp, 1);
	}
	return (possible);
}

int		make_surround_map(t_master *bitmaps, t_fleet *fleet)
{
	int		ship_no;
	double	heatmap[100];
	t_map	map;
	int		shielded;

	zero_tmp_heatmap(bitmaps);
	zero_heatmap(bitmaps);
	make_obstacles(bitmaps);
	shielded = 0;
	ship_no = 0;
	while (ship_no < 100)
	{
		heatmap[ship_no] = 0;
		ship_no++;
	}
	ship_no = 0;
	while (ship_no < 5)
	{
		if (fleet->live_ships[ship_no] == 1)
		{
			shielded += splice(&fleet->ships[ship_no], bitmaps->current_hunt, bitmaps);
			shielded += splice(&fleet->ships_90[ship_no], bitmaps->current_hunt, bitmaps);
		}
		ship_no++;
	}
	apply_heatmap_tmp(bitmaps);
	return (shielded);
}

//include rand skip if equal
void		make_cheap_heatmap_ship(t_master *bitmaps, t_ship *ship)
{
	int		pos;
	pos = 0;
	while (pos < 100)
	{
		if (is_pos_valid(ship, pos, bitmaps))
		{
			apply_ship_map_to_heatmap(right_shift_loc(ship->map, pos), bitmaps);
		}
		pos++;
	}
}

void		make_obstacles(t_master *bitmaps)
{
	bitmaps->obstacles = new_map();
	bitmaps->obstacles = map_or(&bitmaps->obstacles, &bitmaps->sunk);
	bitmaps->obstacles = map_or(&bitmaps->obstacles, &bitmaps->miss);
	bitmaps->obstacles = map_or(&bitmaps->obstacles, &bitmaps->contact);
}

void		zero_tmp_heatmap(t_master *bitmaps)
{
	int	i;

	i = 0;
	while (i < 100)
	{
		bitmaps->heatmap_tmp[i] = 0;
		i++;
	}
}

void		zero_heatmap(t_master *bitmaps)
{
	int	i;

	i = 0;
	while (i < 100)
	{
		bitmaps->heatmap[i] = 0;
		i++;
	}
}

void		apply_heatmap_tmp(t_master *bitmaps)
{
	int	i;

	normalize_heatmap_tmp(bitmaps);
	i = 0;
	while (i < 100)
	{
		bitmaps->heatmap[i] = bitmaps->heatmap[i] + bitmaps->heatmap_tmp[i];
		i++;
	}
}

void		make_cheap_heatmap(t_master *bitmaps, t_fleet *fleet)
{
	int	i;

	make_obstacles(bitmaps);
	zero_tmp_heatmap(bitmaps);
	zero_heatmap(bitmaps);
	bitmaps->total = 0;
	i = 0;
	while (i < 5)
	{
		if (fleet->live_ships[i])
		{
			make_cheap_heatmap_ship(bitmaps, &fleet->ships[i]);
			make_cheap_heatmap_ship(bitmaps, &fleet->ships_90[i]);
		}
		i++;
	}
	apply_heatmap_tmp(bitmaps);
}

int			heatmap_pick_highest(t_master *bitmaps)
{
	double	max;
	int		pos;
	int		pos_max;

	pos_max = -1;
	pos = 0;
	max = 0;
	while (pos < 100)
	{
		if (bitmaps->heatmap[pos] > max && bitmaps->heatmap[pos] > 0.0)
		{
			max = bitmaps->heatmap[pos];
			pos_max = pos;
		}
		pos++;
	}
	return (pos_max);
}

void		normalize_heatmap(t_master *bitmaps)
{
	int		i;
	double	total;

	i = 0;
	total = 0;
	while (i < 100)
	{
		total += bitmaps->heatmap[i];
		i++;
	}
	i = 0;
	while (i < 100)
	{
		bitmaps->heatmap[i] = (bitmaps->heatmap[i] / total) * 100;
		i++;
	}
}

void		normalize_heatmap_tmp(t_master *bitmaps)
{
	int		i;
	double	total;

	i = 0;
	total = 0;
	while (i < 100)
	{
		total += bitmaps->heatmap_tmp[i];
		i++;
	}
	i = 0;
	while (i < 100)
	{
		bitmaps->heatmap_tmp[i] = (bitmaps->heatmap_tmp[i] / total) * 100;
		i++;
	}
}

void		print_heatmap(t_master *bitmaps)
{
	int	i;

	i = 0;
	while (i < 100)
	{
		if (i % 10 == 0)
			printf("\n\n");
		printf("%.2f ", bitmaps->heatmap[i]);
		i++;
	}
	printf("\n");
}

void		write_heatmap(double heatmap[100])
{
	int	i;

	i = 0;
	while (i < 100)
	{
		if (i % 10 == 0)
			dprintf(2,"\n\n");
		dprintf(2, "%.2f ", heatmap[i]);
		i++;
	}
	dprintf(2, "\n");
}

void		printoo(t_master *bitmaps)
{
		int	i;

	i = 0;
	while (i < 100)
	{
		printf("\n");
		printf("%f ", bitmaps->heatmap[i]);
		i++;
	}
}