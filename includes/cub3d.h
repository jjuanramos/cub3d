/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:09:45 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/09/09 10:22:57 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define MAPWIDTH 24
# define MAPHEIGHT 24
# define SCREENWIDTH 640
# define SCREENHEIGHT 480
# define TILE_SIZE 30
# define FOV 60

/*	Buttons & Keys	*/
# define CLOSE_BUTTON 17
# define KEY_ESC 53
# define KEY_W 13
# define KEY_D 2
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_SPACE 49
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5
# define MOUSE_WHEEL_BTN 3
# define MOUSE_BTN 1
# define MOUSE_BTN_2 3
# define KEY_K 107

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "libft.h"
# include <unistd.h>
# include <errno.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"

typedef struct s_data
{
	char	**map2d;
	int		w_map;
	int		h_map;
}			t_data;

typedef struct s_player
{
	int		pos_x;
	int		pos_y;
	int		dir_x;
	int		dir_y;
	float	plyr_x;
	float	plyr_y;
	float	fov_rd;
	float	angle;
}			t_player;

typedef struct s_mlx
{
	void		*img;
	void		*mlx_p;
	t_data		*dt;
	t_player	*plyr;
}			t_mlx;

/* init_player.c */
int		init_player(t_mlx *mlx);
void	display_player(t_player *plyr);

/* free_mlx.c */
int	free_mlx(t_mlx *mlx);

#endif