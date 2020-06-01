#ifndef INCLUDES_H
# define INCLUDES_H
# define ONE 	0b1
# define MAXO		0b1000000000000000000000000000000000000000000000000000000000000000
# define LCOLONE	0b1000000000100000000010000000001000000000100000000010000000001000
# define LCOLTWO	0b0000001000000000100000000010000000000000000000000000000000000000
# define RCOLONE	0b0000000001000000000100000000010000000001000000000100000000010000
# define RCOLTWO	0b0000010000000001000000000100000000010000000000000000000000000000 
# define ROW	0b1111111100000000000000000000000000000000000000000000000000000000

typedef unsigned char	t_byte;

typedef struct	s_map
{
	unsigned long one;
	unsigned long two;
}				t_map;

typedef struct	s_heatmap
{
	double		heatmap[100];
}				t_heatmap;

typedef struct	s_ship
{
	int			height;
	int			width;
	int			size;
	int			pos[5];
	int			top_left_corner_pos;
	t_map		map;
	t_map		contact;
	/*
	int			contact_pos[12];
	int			contact_pos_left[12];
	int			contact_pos_right[12];
	int			contact_pos_top[12];
	int			contact_pos_bottom[12];
	*/
}				t_ship;	

typedef struct	s_fleet
{
	t_ship		ships[5];
	t_ship		ships_90[5];
	int			live_ships[5];
	int			nb_live_ships;
	int			nb_last_live_ship;
}				t_fleet;

typedef struct	s_master
{
	t_map		hit;
	t_map		miss;
	t_map		sunk;
	t_map		blocked;
	t_map		contact;
	t_map		obstacles;
	double		heatmap[100];
	int			total;
}				t_master;

t_map		new_map(void);
t_fleet		*make_nation_fleet(void);
t_byte		*copy_map(t_byte *map);
void		copy_map_data(t_byte *src, t_byte *dest);
t_master	*make_bitmaps(void);
int			make_heatmap(t_fleet *fleet, t_master *bitmaps, int ship_no);
void		normalize_heatmap(t_master *bitmaps);
void		print_heatmap(t_master *bitmaps);
void		printoo(t_master *bitmaps);
void		print_ship(t_ship *ship);
void		print_fleet(t_fleet *fleet);
void		right_shift(t_map *map, int shift);
void		left_shift(t_map *map, int shift);
void		both_shift(t_map *map, int shift);
void		add_pos(t_map *map, int pos);
void		print_map(t_map *map);
int			is_bitwise_and_zero(t_map *one, t_map *two);
t_map		map_or(t_map *one, t_map *two);
t_map		map_and(t_map *one, t_map *two);
t_map		map_xor(t_map *one, t_map *two);
t_map		map_not(t_map *one);

void		make_contact_from_map(t_map *map, t_map *contact);
t_map		contact_pos(const t_ship *ship, int pos);



#endif