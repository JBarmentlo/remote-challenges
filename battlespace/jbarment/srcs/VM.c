#include "includes.h"
#include <unistd.h>

int		shoot(int pos, t_master *bitmaps)
{
	char	l;
	char	c;
	char	out[3];

	add_pos(&bitmaps->shot, pos);
	l = 'A' + (pos / 10);
	c = '0' + (pos % 10);
	out[0] = l;
	out[1] = c;
	out[2] = '\n';
	write(1, out, 3);
	write(2, out, 3);
	return (handle_input(bitmaps, pos));
}

void	print_input()
{
	char		buffer[9];

	read(0, buffer, 9);
	write(2, buffer, 5);
}