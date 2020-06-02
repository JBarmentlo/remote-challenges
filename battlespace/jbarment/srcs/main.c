#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <stdint.h>

#include "includes.h"




int	main()
{
	t_master	*bitmaps;
	t_fleet		*nation_fleet;

	bitmaps = make_bitmaps();
	nation_fleet = make_shield_fleet();

//	print_fleet(nation_fleet);
	t_map shipmap;
	bzero(&shipmap, 16);
	print_map(&nation_fleet->ships[0].contact);
	int i = 0;
	while (i < 100)
	{
		printf("%d\n\n",i);
		shipmap = shield_contact_from_pos(&nation_fleet->ships[0], i);
		printf("contact\n");
		print_map(&shipmap);
		i++;
	}
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