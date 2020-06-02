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

	bitmaps = make_bitmaps();
	make_shield_fleet(bitmaps);
	make_nation_fleet(bitmaps);
	result = 0;

	while (1)
	{
		if (bitmaps->shield_pos_nb < 7 && bitmaps->shield_fleet->live_ships[0] == 1)
		{
			shoot_for_shield(bitmaps);
		}
		if (result == SUNK)
		{
			sunk_id = identify_sunk_ship_fleet(bitmaps->nation_fleet, bitmaps);
			handle_sunk_ship(bitmaps, sunk_id);
		}
		if (result == MISS)
		{
			make_cheap_heatmap(bitmaps, bitmaps->nation_fleet);
			last_shot = heatmap_pick_highest(bitmaps);
			shoot(last_shot, bitmaps);
			result = handle_input(bitmaps, last_shot);
		}
		if (result == HIT || result == BLOCKED)
		{
			if (result == BLOCKED)
				write_map(&bitmaps->shield_pos);
			result = hunt_mode(bitmaps);
		}
		else
		{
			make_cheap_heatmap(bitmaps, bitmaps->nation_fleet);
			last_shot = heatmap_pick_highest(bitmaps);
			shoot(last_shot, bitmaps);
			result = handle_input(bitmaps, last_shot);
		}
	}

/*
	add_pos(&bitmaps->current_sunk, 55);
	add_pos(&bitmaps->current_sunk, 65);

	print_ship(identify_sunk_ship_fleet(bitmaps->nation_fleet, bitmaps).ship);
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