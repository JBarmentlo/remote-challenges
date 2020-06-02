#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <stdint.h>

#include "includes.h"




int	main()
{
	t_master	*bitmaps;
	int			last_shot;
	int			result;
	t_id		sunk_id;
	t_fleet	*alien_f;
	t_fleet	*merc_f;

	bitmaps = make_bitmaps();
	alien_f = make_alien_fleet(bitmaps);
	merc_f = make_merc_fleet(bitmaps);
	make_shield_fleet(bitmaps);
	make_nation_fleet(bitmaps);
	result = 0;
	make_general_heatmap(bitmaps);
	print_heatmap(bitmaps);
/*
	while (1)
	{
		dprintf(2, "ships left %d\n result %d\n", bitmaps->nation_fleet->nb_live_ships, result);
		if (bitmaps->shield_pos_nb < 7 && bitmaps->shield_fleet->live_ships[0] == 1)
		{
			shoot_for_shield(bitmaps);
		}
		if (result == MISS)
		{
			make_cheap_heatmap(bitmaps, bitmaps->nation_fleet);
			last_shot = heatmap_pick_highest(bitmaps);
			result = shoot(last_shot, bitmaps);
		}
		if (result == HIT || result == BLOCKED)
		{
			if (result == BLOCKED)
				write_map(&bitmaps->shield_pos);
			result = hunt_mode(bitmaps);
		}
		if (bitmaps->nation_fleet->nb_live_ships == 0)
		{
			finish_blocked(bitmaps);
		}
		else
		{
			dprintf(2, "else\n");
			make_cheap_heatmap(bitmaps, bitmaps->nation_fleet);
			write_heatmap(bitmaps->heatmap);
			last_shot = heatmap_pick_highest(bitmaps);
			result = shoot(last_shot, bitmaps);
		}
	}
*/

/*
	add_pos(&bitmaps->current_sunk, 55);

	print_ship(identify_sunk_ship_fleet(bitmaps->nation_fleet, bitmaps).ship);
	handle_sunk_ship(bitmaps, identify_sunk_ship_fleet(bitmaps->nation_fleet, bitmaps));
*/
//	make_surround_map(bitmaps, bitmaps->nation_fleet);
//	print_heatmap(bitmaps);





//	make_shield_heatmap(bitmaps, &shield_fleet->ships[0]);


//	make_heatmap_bit(bitmaps, nation_fleet, 2, shipmap);
//	printf("TOTAL: %d\n", bitmaps->total);
	//printoo(bitmaps);
//	normalize_heatmap(bitmaps);
//	print_heatmap(bitmaps);
	return (1);
}


//	write(1, "A0\n", 3);
//	read(0, buffer, 9);
//	write(2, "yayayaya\n", 5);
//	write(2, buffer, 5);total 65550000

/*
void	dooo(void)
{
	write(1, "A0\n", 3);
}

void    print_input()
{
	char		buffer[9];

	read(0, buffer, 9);
	write(2, buffer, 5);
}

int	main()
{
	static t_master		*bitmaps;
	static t_fleet		*nation_fleet;
	char				buffer[9];
	char				out[4];
	int	i;

	while (1)
	{
		dooo();
		print_input();

	}

	write(2, "YAYAYA\n", 5);
}
*/