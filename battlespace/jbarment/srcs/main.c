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
	nation_fleet = make_nation_fleet();
//	print_fleet(nation_fleet);
	make_heatmap(nation_fleet, bitmaps, 0);
//	printoo(bitmaps);
	normalize_heatmap(bitmaps);
	print_heatmap(bitmaps);
	return (1);
}

//	write(1, "A0\n", 3);
//	read(0, buffer, 9);
//	write(2, "yayayaya\n", 5);
//	write(2, buffer, 5);total 65550000