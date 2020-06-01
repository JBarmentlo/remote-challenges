#include "includes.h"
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>


void		add_ship(t_master *bitmaps, t_map *ship_map, t_ship *ship, int pos)
{
	t_map	contact;
	t_map	ship_in_pos;

	ship_in_pos = right_shift_loc(ship->map, pos);
	contact = contact_pos(ship, pos);
//	bitmaps->contact = map_or(&contact, &(bitmaps->contact));
	*ship_map = map_or(&ship_in_pos, ship_map);
	contact = map_or(&contact, ship_map);
	bitmaps->obstacles = map_or(&contact, &(bitmaps->obstacles));
}

t_map		contact_pos(const t_ship *ship, int pos)
{
	static t_map	left_col = {LCOLONE , LCOLTWO};
	static t_map	right_col = {RCOLONE , RCOLTWO};
	t_map	out;

	out = ship->contact;
	if (pos % 10 == 0)
	{
		out = map_not(&out);
		out = map_or(&out, &left_col);
		out = map_not(&out);
	}
	if ((pos + ship->width ) % 10 == 9)
	{
		out = map_not(&out);
		out = map_or(&out, &right_col);
		out = map_not(&out);
	}
	both_shift(&out, pos - 11);
	return (out);
}

void		make_contact_from_map(t_map *map, t_map *contact)
{
	t_map	tmp;

	tmp = *map;
	right_shift(&tmp, 1);
	*contact = map_or(contact, &tmp);
	right_shift(&tmp, 9);
	*contact = map_or(contact, &tmp);
	right_shift(&tmp, 2);
	*contact = map_or(contact, &tmp);
	right_shift(&tmp, 9);
	*contact = map_or(contact, &tmp);
	left_shift(&tmp, 10);
	*contact = map_xor(contact, &tmp);
}

t_map		map_not(t_map *one)
{
	t_map out;

	out.one = ~ one->one;
	out.two = ~ one->two;
	return (out);
}

t_map		map_and(t_map *one, t_map *two)
{
	t_map out;

	out.one = (one->one & two->one);
	out.two = (one->two & two->two);
	return (out);
}

t_map		map_or(t_map *one, t_map *two)
{
	t_map out;

	out.one = one->one | two->one;
	out.two = one->two | two->two;
	return (out);
}

t_map		map_xor(t_map *one, t_map *two)
{
	t_map out;

	out.one = one->one ^ two->one;
	out.two = one->two ^ two->two;
	return (out);
}

int			is_bitwise_and_zero(t_map *one, t_map *two)
{
	if ((one->one & two->one) != 0)
		return (0);
	if ((one->two & two->two) != 0)
		return (0);
	return (1);
}

void		print_map(t_map *map)
{
	unsigned long	mask;
	int				i;

	mask = MAXO;
	i = 0;
	while (i < 64)
	{
		if (i % 10 == 0)
		{
			printf("\n");
		}
		if (map->one & mask)
		{
			printf("X ");
		}
		else
		{
			printf("- ");
		}
		mask = mask >> 1;
		i++;
	}
	mask = MAXO;
	while (i < 100)
	{
		if (i % 10 == 0)
		{
			printf("\n");
		}
		if (map->two & mask)
		{
			printf("X ");
		}
		else
		{
			printf("- ");
		}
		mask = mask >> 1;
		i++;
	}
	printf("\n\n");
}

inline void	both_shift(t_map *map, int shift)
{
	if (shift >= 0)
		right_shift(map, shift);
	else
		left_shift(map, -shift);
}

inline void	right_shift(t_map *map, int shift)
{
	if (shift == 0)
		return ;
	if (shift >= 64)
	{
		map->two = map->one >> (shift - 64);
		map->one = 0;
		return ;
	}
	map->two = (map->two >> shift) | (map->one << (64 - shift));
	map->one = map->one >> shift;
}

inline void	left_shift(t_map *map, int shift)
{
	if (shift == 0)
		return ;
	if (shift == 64)
	{
		map->one = map->two << (shift - 64);
		map->two = 0;
		return ;
	}
	map->one = (map->one << shift) | (map->two >> (64 - shift));
	map->two = map->two << shift;
}

inline t_map	right_shift_loc(t_map map, int shift)
{
	map.two = (map.two >> shift) | (map.one << (64 - shift));
	map.one = map.one >> shift;
	return (map);
}

inline void	add_pos(t_map *map, int pos)
{
	if (pos < 64)
	{
		map->one = (map->one | (MAXO >> pos));
	}
	else
	{
		map->two = (map->two | (MAXO >> pos));
	}
}

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