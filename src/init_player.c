/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 10:45:05 by juramos           #+#    #+#             */
/*   Updated: 2024/09/07 12:21:31 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			is_pos(char c);
t_player	*init_player(char **str);
int			fill_player(char **str, t_player *plyr);
void		display_player(t_player *plyr);
void		add_dir(t_player *plyr, char c);

void	display_player(t_player *plyr)
{
	printf("<--- Player Stats --->\n");
	printf("\tpos_x: %d\n", plyr->pos_x);
	printf("\tpos_y: %d\n", plyr->pos_y);
	printf("\tdir_x: %d\n", plyr->dir_x);
	printf("\tdir_y: %d\n", plyr->dir_y);
	printf("\tplyr_x: %f\n", plyr->plyr_x);
	printf("\tplyr_y: %f\n", plyr->plyr_y);
	printf("\tfov_rd: %f\n", plyr->fov_rd);
	printf("\tangle: %f\n", plyr->angle);
	printf("<------------------->\n");
}

int	is_pos(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/*
	We are assuming that N equals -1 in the y-axis,
	and not 1.
*/
void	add_dir(t_player *plyr, char c)
{
	if (c == 'N')
	{
		plyr->dir_x = 0;
		plyr->dir_y = -1;
	}
	else if (c == 'E')
	{
		plyr->dir_x = 1;
		plyr->dir_y = 0;
	}
	else if (c == 'S')
	{
		plyr->dir_x = 0;
		plyr->dir_y = 1;
	}
	else if (c == 'W')
	{
		plyr->dir_x = -1;
		plyr->dir_y = 0;
	}
}

t_player	*init_player(char **str)
{
	t_player	*plyr;

	plyr = ft_calloc(1, sizeof(t_player));
	if (!plyr)
		return (NULL);
	plyr->fov_rd = (M_PI * FOV) / 180;
	plyr->angle = M_PI;
	if (fill_player(str, plyr))
		return (NULL);
	plyr->plyr_x = TILE_SIZE * plyr->pos_x + TILE_SIZE / 2;
	plyr->plyr_y = TILE_SIZE * plyr->pos_y + TILE_SIZE / 2;
	return (plyr);
}

int	fill_player(char **str, t_player *plyr)
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
				if (!is_pos(str[y][x]) || times == 1)
					return (1);
				times++;
				plyr->pos_x = x;
				plyr->pos_y = y;
				add_dir(plyr, str[y][x]);
			}
			x++;
		}
		y++;
	}
	return (0);
}
