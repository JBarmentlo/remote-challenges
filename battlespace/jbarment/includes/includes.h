#ifndef INCLUDES_H
# define INCLUDES_H
# define ONE 	0b1
# define MAXO		0b1000000000000000000000000000000000000000000000000000000000000000
# define LCOLONE	0b1000000000100000000010000000001000000000100000000010000000001000
# define LCOLTWO	0b0000001000000000100000000010000000000000000000000000000000000000
# define RCOLONE	0b0000000001000000000100000000010000000001000000000100000000010000
# define RCOLTWO	0b0000010000000001000000000100000000010000000000000000000000000000 
# define ROW		0b1111111100000000000000000000000000000000000000000000000000000000
# define HIT		0b0001
# define MISS		0b0010
# define SUNK		0b0100
# define BLOCKED	0b1000

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
	t_map		shot;
	t_map		shield_pos;
	t_map		current_hunt;
	t_map		current_sunk;
	int			annexe_sunk;
	int			shield_pos_nb;
	t_fleet		*shield_fleet;
	t_fleet		*nation_fleet;
	t_fleet		*mercenary_fleet;
	t_fleet		*alien_fleet;
	double		heatmap[100];
	double		heatmap_tmp[100];
	int			total;
}				t_master;

typedef struct	s_id
{
	t_ship		*ship;
	t_fleet		*fleet;
	int			num;
	int			is_90;
	int			pos;
}				t_id;


t_map		new_map(void);
t_fleet		*make_nation_fleet(t_master *bitmaps);
t_byte		*copy_map(t_byte *map);
void		copy_map_data(t_byte *src, t_byte *dest);
t_master	*make_bitmaps(void);
int			make_heatmap(t_fleet *fleet, t_master *bitmaps, int ship_no);
void		normalize_heatmap(t_master *bitmaps);
void		normalize_heatmap_tmp(t_master *bitmaps);
void		print_heatmap(t_master *bitmaps);
void		printoo(t_master *bitmaps);
void		print_ship(t_ship *ship);
void		write_ship(t_ship *ship);
void		print_fleet(t_fleet *fleet);
int			is_pos_valid(t_ship *ship, int pos, t_master *bitmaps);
int			is_pos_valid_no_obst(t_ship *ship, int pos, t_master *bitmaps);


t_map		right_shift_loc(t_map map, int shift);
void		right_shift(t_map *map, int shift);
void		left_shift(t_map *map, int shift);
void		both_shift(t_map *map, int shift);
t_map		substract_map(t_map dest, t_map sub);

void		add_pos(t_map *map, int pos);
void		print_map(t_map *map);
int			is_bitwise_and_zero(t_map *one, t_map *two);
int			is_bitwise_and_one(t_map *one, t_map *two);
t_map		map_or(t_map *one, t_map *two);
t_map		map_and(t_map *one, t_map *two);
t_map		map_xor(t_map *one, t_map *two);
t_map		map_not(t_map *one);
int			equals(t_map one, t_map two);
int			count(t_map	*map);

void		make_contact_from_map(t_map *map, t_map *contact);
t_map		contact_pos(const t_ship *ship, int pos);
void		add_ship(t_master *bitmaps, t_map *ship_map, t_ship *ship, int pos);
void		make_heatmap_bit(t_master *bitmaps, t_fleet *fleet, int ship_no, t_map ship_map);
void		make_cheap_heatmap(t_master *bitmaps, t_fleet *fleet);
int			is_pos_one(t_map *map, int pos);

int			qualify_string(char buffer[9]);
int			update_bitmaps_from_input(char buffer[9], t_master *bitmaps, int pos);
int			is_pos_one_coord(t_map *map, int i, int j);
void		make_map_from_pos(t_ship *ship);
t_map		new_map(void);

t_fleet		*make_shield_fleet(t_master *bitmaps);
t_map		shield_contact_from_pos(t_ship *shield, int pos);
void		make_shield_heatmap(t_master *bitmaps, t_ship *shield);
void		update_shield_pos(t_master *bitmaps, int last_pos);
void		update_shield_pos_hit(t_master *bitmaps, int last_pos);


void		apply_ship_map_to_heatmap(t_map ship_map,t_master *bitmaps);
int			heatmap_pick_highest(t_master *bitmaps);
int			make_surround_map(t_master *bitmaps, t_fleet *fleet);

void		make_obstacles(t_master *bitmaps);
void		apply_heatmap_tmp(t_master *bitmaps);
void		zero_tmp_heatmap(t_master *bitmaps);
void		zero_heatmap(t_master *bitmaps);


int			shoot(int pos, t_master *bitmaps);
void		print_input();
int			handle_input(t_master *bitmaps, int pos);

void		write_map(t_map *map);
void		write_heatmap(double heatmap[100]);

int			shoot_for_shield(t_master *bitmaps);
int			choose_shot_shield(t_master *bitmaps, t_ship *shield);

int			hunt_mode(t_master *bitmaps);
int			choose_hunt_shot(t_master *bitmaps);
t_id		identify_sunk_ship_fleet(t_fleet *fleet, t_master *bitmaps);
void		handle_sunk_ship(t_master *bitmaps, t_id sunk_id);

void	finish_blocked(t_master *bitmaps);

#endif