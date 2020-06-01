typedef unsigned char	t_byte;

typedef struct	s_map
{
	t_byte		map[100];
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
	t_byte		hit[100];
	t_byte		miss[100];
	t_byte		sunk[100];
	t_byte		blocked[100];
	t_byte		contact[100];
	t_byte		obstacles[100];
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
