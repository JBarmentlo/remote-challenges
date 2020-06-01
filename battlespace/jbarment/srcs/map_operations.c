#include "includes.h"
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>

t_byte	*copy_map(t_byte *map)
{
	t_byte	*copy;
	int		i;

	copy = malloc(100);
	i = 0;
	while (i < 100)
	{
		copy[i] = map[i];
		i++;
	}
	return (copy);
}

void	copy_map_data(t_byte *src, t_byte *dest)
{
	int	i;

	i = 0;
	while (i < 100)
	{
		dest[i] = src[i];
		i++;
	}
}

t_master	*make_bitmaps(void)
{
	t_master	*out;

	out = malloc(sizeof(*out));
	bzero(out, sizeof(*out));
}

void	normalize_heatmap(t_master *bitmaps)
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

void	print_heatmap(t_master *bitmaps)
{
	int	i;

	i = 0;
	while (i < 100)
	{
		if (i % 10 == 0)
			printf("\n");
		printf("%.2f ", bitmaps->heatmap[i]);
		i++;
	}
}

void	printoo(t_master *bitmaps)
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