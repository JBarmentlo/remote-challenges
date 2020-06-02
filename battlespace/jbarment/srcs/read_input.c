#include "includes.h"
#include <unistd.h>
#include "stdio.h"

int		handle_input(t_master *bitmaps, int pos)
{
	char	buffer[9];
	int		i;

	i = 0;
	while(i < 9)
	{
		buffer[i] = 0;
		i++;
	}
	read(0, buffer, 9);
	write(2, buffer,8);
	update_bitmaps_from_input(buffer, bitmaps, pos);
	return (qualify_string(buffer));
	return (1);
}

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

//ADD CONTACT
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
	if (result == HIT || result == SUNK)
	{
		add_pos(&bitmaps->hit, pos);
		add_pos(&bitmaps->current_hunt, pos);
		update_shield_pos_hit(bitmaps, pos);
		write_map(&bitmaps->shield_pos);
		return (HIT);
	}
	if (result == BLOCKED)
	{
		add_pos(&bitmaps->blocked, pos);
		update_shield_pos(bitmaps, pos);
		add_pos(&bitmaps->current_hunt, pos); //DUVIOUS ??
		return (BLOCKED);
	}
	if (result == SUNK)
	{
		add_pos(&bitmaps->hit, pos);
		add_pos(&bitmaps->current_hunt, pos);
		bitmaps->sunk = map_or(&bitmaps->sunk, &bitmaps->current_hunt);
		bitmaps->current_sunk = bitmaps->current_hunt;
		bitmaps->current_hunt = new_map();
		//bitmaps->contact = map_or(make_contact_from_map(&bitmaps->current_hunt))
		printf("UPDATE CONTACT MAP\n");
		return (SUNK);
	}
	

}