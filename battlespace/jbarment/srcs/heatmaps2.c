#include "includes.h"

void		apply_heatmap_tmp_alien(t_master *bitmaps)
{
	int	i;

	normalize_heatmap_tmp(bitmaps);
	i = 0;
	while (i < 100)
	{
		bitmaps->heatmap_alien[i] = bitmaps->heatmap_alien[i] + bitmaps->heatmap_tmp[i];
		i++;
	}
}

void		apply_heatmap_tmp_merc(t_master *bitmaps)
{
	int	i;

	normalize_heatmap_tmp(bitmaps);
	i = 0;
	while (i < 100)
	{
		bitmaps->heatmap_merc[i] = bitmaps->heatmap_merc[i] + bitmaps->heatmap_tmp[i];
		i++;
	}
}

void		apply_heatmap_tmp_nation(t_master *bitmaps)
{
	int	i;

	normalize_heatmap_tmp(bitmaps);
	i = 0;
	while (i < 100)
	{
		bitmaps->heatmap_nation[i] = bitmaps->heatmap_nation[i] + bitmaps->heatmap_nation[i];
		i++;
	}
}

void		make_alien_heatmapp(t_master *bitmaps)
{
	int		i;
	t_fleet	*fleet;

	fleet = bitmaps->alien_fleet;
	make_obstacles(bitmaps);
	zero_tmp_heatmap(bitmaps);
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
	apply_heatmap_tmp_alien(bitmaps);
}

void		make_merc_heatmapp(t_master *bitmaps)
{
	int		i;
	t_fleet	*fleet;

	fleet = bitmaps->merc_fleet;
	make_obstacles(bitmaps);
	zero_tmp_heatmap(bitmaps);
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
	apply_heatmap_tmp_merc(bitmaps);
}

void		make_nation_heatmap(t_master *bitmaps)
{
	int		i;
	t_fleet	*fleet;
	
	fleet = bitmaps->nation_fleet;
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
}

void		normalize_heat(double heatmap[100])
{
	int		i;
	double	total;

	i = 0;
	total = 0;
	while (i < 100)
	{
		total += heatmap[i];
		i++;
	}
	i = 0;
	while (i < 100)
	{
		heatmap[i] = (heatmap[i] / total) * 100;
		i++;
	}
}

#include <stdio.h>

void		combine_heatmaps(t_master *bitmaps)
{
	int	i;

	normalize_heat(bitmaps->heatmap_alien);
	normalize_heat(bitmaps->heatmap_merc);
	normalize_heat(bitmaps->heatmap_nation);
	i = 0;
	while (i < 100)
	{
		bitmaps->heatmap[i] = (bitmaps->heatmap_nation[i] * bitmaps->nation_fleet->odds);
		bitmaps->heatmap[i] = bitmaps->heatmap[i] + (bitmaps->heatmap_merc[i] * bitmaps->merc_fleet->odds);
		bitmaps->heatmap[i] = bitmaps->heatmap[i] + (bitmaps->heatmap_alien[i] * bitmaps->alien_fleet->odds);
		printf("%f\n", bitmaps->heatmap[i]);
		i++;
	}
}
void		make_general_heatmap(t_master *bitmaps)
{
	zero_heatmap(bitmaps);
	make_alien_heatmapp(bitmaps);
	print_heatmap(bitmaps);
	alien_transform(bitmaps);
	make_alien_heatmapp(bitmaps);
	alien_transform_back(bitmaps);
	make_merc_heatmapp(bitmaps);
	make_nation_heatmap(bitmaps);
	combine_heatmaps(bitmaps);
}