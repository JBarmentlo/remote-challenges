#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct	s_map
{
	unsigned long one;
	unsigned long two;
}				t_map;

void right_shift(t_map *map, int shift)
{
	map->two = (map->two >> shift) | (map->one << (64 - shift));
	map->one = map->one >> shift;
} 


int	main(void)
{
	
	int				i;
	int				total = 0;
	t_map			*tab1;
	t_map			*tab2;

	srand((long)time(NULL));
	printf("sizeof : %lu\n", sizeof(t_map));
	tab1 = malloc(10000000 * sizeof(t_map));
	tab2 = malloc(10000000 * sizeof(t_map));
	i = 0;
	while (i < 10000000)
	{
		tab1[i].one = rand();
		tab1[i].two = rand();
		tab2[i].one = rand();
		tab2[i].two = rand();
		right_shift(&(tab1[i]), 25);
		i++;
	}
	printf("total: %d\n", total);
	free(tab1);
	free(tab2);
}