#include "includes.h"
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>

t_map				substract_map(t_map dest, t_map sub)
{
		dest = map_not(&dest);
		dest = map_or(&dest, &sub);
		dest = map_not(&dest);
}

int				equals(t_map one, t_map two)
{
	if (one.one != two.one)
		return (0);
	if (one.two != two.two)
		return (0);
	return (1);
}

int				count(t_map	*map)
{
	unsigned long	mask;
	int				i;
	int				count;

	mask = MAXO;
	count = 0;
	i = 0;
	while (i < 64)
	{
		if ((map->one & mask) != 0)
		{
			count += 1;
		}
		mask = mask >> 1;
		i++;
	}
	mask = MAXO;
	while (i < 100)
	{
		if ((map->two & mask) != 0)
		{
			count += 1;
		}
		mask = mask >> 1;
		i++;
	}
	return (count);
}

int				is_pos_one_coord(t_map *map, int i, int j)
{
	return (is_pos_one(map, 10 * i + j));
}

int				is_pos_one(t_map *map, int pos)
{
	static t_map	mask;
	t_map			tmp;

	mask.one = MAXO;
	mask.two = 0;
	tmp = right_shift_loc(mask, pos);
	if (is_bitwise_and_zero(&tmp, map))
		return (0);
	return (1);
}

void			add_ship(t_master *bitmaps, t_map *ship_map, t_ship *ship, int pos)
{
	t_map	contact;
	t_map	ship_in_pos;

	ship_in_pos = ship->map;
	right_shift(&ship_in_pos, pos);
//	printf("POS: %d\n", pos);
//	printf("ship to add:\n");
//	print_map(&ship_in_pos);
	contact = contact_pos(ship, pos);
//	printf("contact:\n");
//	print_map(&contact);
//	bitmaps->contact = map_or(&contact, &(bitmaps->contact));
	*ship_map = map_or(&ship_in_pos, ship_map);
	contact = map_or(&contact, ship_map);
	bitmaps->obstacles = map_or(&contact, &(bitmaps->obstacles));
	//printf("obstacles:\n");
	//print_map(&bitmaps->obstacles);
}

t_map			contact_pos(const t_ship *ship, int pos)
{
	static t_map	left_col = {LCOLONE , LCOLTWO};
	static t_map	right_col = {RCOLONE , RCOLTWO};
	t_map			tmp;
	t_map	out;

	out = ship->contact;
	if (pos % 10 == 0)
	{
		out = map_not(&out);
		out = map_or(&out, &left_col);
		out = map_not(&out);
	}
	if ((pos + ship->width - 1) % 10 == 9)
	{
		tmp = left_col;
		right_shift(&tmp, ship->width + 1);
		out = map_not(&out);
		out = map_or(&out, &tmp);
		out = map_not(&out);
	}
	both_shift(&out, pos - 11);
	return (out);
}

void			make_contact_from_map(t_map *map, t_map *contact)
{
	t_map	tmp;

	tmp = *map;
	*contact = map_or(contact, &tmp);
	right_shift(&tmp, 1);
	*contact = map_or(contact, &tmp);
	right_shift(&tmp, 1);
	*contact = map_or(contact, &tmp);
	right_shift(&tmp, 8);
	*contact = map_or(contact, &tmp);
	right_shift(&tmp, 1);
	*contact = map_or(contact, &tmp);
	right_shift(&tmp, 1);
	*contact = map_or(contact, &tmp);
	right_shift(&tmp, 8);
	*contact = map_or(contact, &tmp);
	right_shift(&tmp, 1);
	*contact = map_or(contact, &tmp);
	right_shift(&tmp, 1);
	*contact = map_or(contact, &tmp);
	left_shift(&tmp, 11);
	*contact = map_xor(contact, &tmp);
}

t_map			map_not(t_map *one)
{
	t_map out;

	out.one = ~ one->one;
	out.two = ~ one->two;
	return (out);
}

t_map			map_and(t_map *one, t_map *two)
{
	t_map out;

	out.one = (one->one & two->one);
	out.two = (one->two & two->two);
	return (out);
}

t_map			map_or(t_map *one, t_map *two)
{
	t_map out;

	out.one = one->one | two->one;
	out.two = one->two | two->two;
	return (out);
}

t_map			map_xor(t_map *one, t_map *two)
{
	t_map out;

	out.one = one->one ^ two->one;
	out.two = one->two ^ two->two;
	return (out);
}

//SCARY
int				is_bitwise_and_zero(t_map *one, t_map *two)
{
	if ((one->one & two->one) != 0)
		return (0);
	if ((one->two & two->two) != 0)
		return (0);
	return (1);
}

int				is_bitwise_and_one(t_map *one, t_map *two)
{
	if (((one->one & two->one) == 0) && ((one->two & two->two) == 0))
		return (0);
	return (1);
}

void			write_map(t_map *map)
{
	unsigned long	mask;
	int				i;

	mask = MAXO;
	i = 0;
	while (i < 64)
	{
		if (i % 10 == 0)
		{
			write(2,"\n", 1);
		}
		if (map->one & mask)
		{
			write(2,"X ", 2);
		}
		else
		{
			write(2,"- ", 2);
		}
		mask = mask >> 1;
		i++;
	}
	mask = MAXO;
	while (i < 100)
	{
		if (i % 10 == 0)
		{
			write(2,"\n", 1);
		}
		if (map->two & mask)
		{
			write(2,"X ", 2);
		}
		else
		{
			write(2,"- ", 2);
		}
		mask = mask >> 1;
		i++;
	}
	write(2, "\n\n", 2);
}

void			print_map(t_map *map)
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

inline void		both_shift(t_map *map, int shift)
{
	if (shift >= 0)
		right_shift(map, shift);
	else
		left_shift(map, -shift);
}

inline void		right_shift(t_map *map, int shift)
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

inline void		left_shift(t_map *map, int shift)
{
	if (shift == 0)
		return ;
	if (shift >= 64)
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
	if (shift == 0)
		return (map) ;
	if (shift >= 64)
	{
		map.two = map.one >> (shift - 64);
		map.one = 0;
		return (map) ;
	}
	map.two = (map.two >> shift) | (map.one << (64 - shift));
	map.one = map.one >> shift;
	return (map);
}

inline void		add_pos(t_map *map, int pos)
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

t_master		*make_bitmaps(void)
{
	t_master	*out;

	out = malloc(sizeof(*out));
	bzero(out, sizeof(*out));
	out->shield_pos.one = 0b1111111111111111111111111111111111111111111111111111111111111111;
	out->shield_pos.two = 0b1111111111111111111111111111111100000000000000000000000000000000;
}
