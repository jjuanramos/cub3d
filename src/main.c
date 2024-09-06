/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:58:31 by juramos           #+#    #+#             */
/*   Updated: 2024/09/06 17:21:16 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_pos(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/* TODO
	> maybe init_player should be a standalone function that
	provides an empty struct with just angle and fov_rd filled.

	> init_player should receive an empty t_player struct,
	otherwise init it inside (and then return the struct).
*/
int	init_player(char **str)
{
	int	y;
	int	x;
	int	times;

	y = 0;
	times = 0;
	while (str[y])
	{
		x = 0;
		while (str[y][x])
		{
			if (str[y][x] != '0' && str[y][x] != '1')
			{
				if (!is_pos(str[y][x]))
					return (1);
				if (times == 1)
					return (1);
				times++;
				/* TODO
					t_player.pos_x = x;
					t_player.pos_y = y;
					t_player.plyr_x = TILE_SIZE * x + TILE_SIZE / 2;
					t_player.plyr_y = TILE_SIZE * y + TILE_SIZE / 2;
					add_dir(t_player, str[y][x]);
				*/
			}
			x++;
		}
	}
	return (0);
}

int	main(void)
{
	char	**map2d;
	int		pos_x;
	int		pos_y;

	map2d = ft_calloc(10, sizeof(char *));
	if (!map2d)
		return (1);
	map2d[0] = strdup("1111111111111111111111111");
	map2d[1] = strdup("1000000000000000000100001");
	map2d[2] = strdup("1001000000000S00000000001");
	map2d[3] = strdup("1001000000000000001000001");
	map2d[4] = strdup("1001000000000000001000001");
	map2d[5] = strdup("1001000000100000001000001");
	map2d[6] = strdup("1001000000000000001000001");
	map2d[7] = strdup("1001000000001000001000001");
	map2d[8] = strdup("1111111111111111111111111");
	map2d[9] = NULL;
	/* TODO
		We receive the char **above from Carlos' parsing. Thus:
		[] Check that there is a player in the map, otherwise return error;
		[] Add to t_player:
			[] pos_x: position x of player in map;
			[] pos_y: position y of player in map;
			[] dir_x: starting direction of x player in map;
			[] dir_y: starting direction of y player in map;
			[] plyr_x: position x of player in map (in pixels);
			[] plyr_y: position y of player in map (in pixels);
			[] fov_rd: field of vision in radians; (FOV * M_PI) / 180;
			[] angle: player angle (starts at pi); (M_PI);
	*/
	pos_x = 14;
	pos_y = 3;
	return (0);
}

