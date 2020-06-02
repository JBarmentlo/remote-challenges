#include "includes.h"

int		qualify_string(char buffer[9])
{
	if (buffer[0] == 'M')
		return (MISS);
	if (buffer[0] == 'H')
		return (HIT);
	if (buffer[0] == 'B')
		return (BLOCKED);
	if (buffer[0] == 'S')
		return (SUNK);
	return (0);
}

int		update_bitmaps_from_input(char buffer[9], t_master *bitmaps, int pos)
{
	int	result;

	result = qualify_string(buffer);
	if (result == MISS)
	{
		add_pos(&bitmaps->miss, pos);
		add_pos(&bitmaps->obstacles, pos);
		return (MISS);
	}
	if (result == HIT)
	{
		add_pos(&bitmaps->hit, pos);
		return (HIT);
	}
	if (result == BLOCKED)
	{
		add_pos(&bitmaps->blocked, pos);
		return (BLOCKED);
	}
	if (result == SUNK)
	{
		add_pos(&bitmaps->hit, pos);
		add_pos(&bitmaps->sunk, pos);
		return (SUNK);
	}
	

}