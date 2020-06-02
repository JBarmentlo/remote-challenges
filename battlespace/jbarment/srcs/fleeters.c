#include "includes.h"

void	guess_odds_shit(t_master *bitmaps)
{
	bitmaps->merc_fleet->odds = 0.2 * bitmaps->merc_fleet->nb_live_ships;
	bitmaps->nation_fleet->odds = 0.2 * bitmaps->nation_fleet->nb_live_ships;
	bitmaps->alien_fleet->odds = 0.2 * bitmaps->alien_fleet->nb_live_ships;
}

void	alien_transform(t_master *bitmaps)
{
	int	alive;

	alive = bitmaps->alien_fleet->live_ships[0];
	make_alien_ship_180_0(5, &bitmaps->alien_fleet->ships[0]);
	make_alien_ship_270_0(5, &bitmaps->alien_fleet->ships_90[0]);
	bitmaps->alien_fleet->live_ships[0] = alive;
}

void	alien_transform_back(t_master *bitmaps)
{
	int	alive;

	alive = bitmaps->alien_fleet->live_ships[0];
	make_alien_ship_0(5, &bitmaps->alien_fleet->ships[0]);
	make_alien_ship_90_0(5, &bitmaps->alien_fleet->ships_90[0]);
	bitmaps->alien_fleet->live_ships[0] = alive;
}