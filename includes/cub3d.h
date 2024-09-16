/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:09:45 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/09/16 13:55:25 by juramos          ###   ########.fr       */
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
# define ROTATION_SPEED 0.015
# define PLAYER_SPEED 4

/*	Buttons & Keys	*/
# ifdef __APPLE__
# include <TargetConditionals.h>
#if TARGET_OS_MAC
	# define KEY_ESC 61
	# define KEY_A 8
	# define KEY_W 21
	# define KEY_S 9
	# define KEY_D 10
	# define KEY_LEFT 131
	# define KEY_RIGHT 132
	#define SYSTEM_IS_MACOS 1
#endif
# endif

// Check if the system is Linux
#ifdef __linux__
#define SYSTEM_IS_LINUX 1
# define KEY_ESC 9
# define KEY_A 38
# define KEY_W 25
# define KEY_S 39
# define KEY_D 40
# define KEY_LEFT 100
# define KEY_RIGHT 102
#endif

/*	Key events */
# define ON_KEY_DOWN 2
# define ON_KEY_UP 3
# define ON_DESTROY 17

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "libft.h"
# include <unistd.h>
# include <errno.h>
# include <math.h>
# include <stdbool.h>
# include "../minilibx-linux/mlx.h"

typedef struct s_map
{
	char	**map;
	char	*no_text;
	char	*so_text;
	char	*we_text;
	char	*ea_text;
	// int		*floor_color;
	// int		*ceiling_color;
	int		width;
	int		height;	
}				t_map;

typedef struct s_player
{
	int		pos_x;
	int		pos_y;
	int		dir_x;
	int		dir_y;
	int		rot_dir;
	float	plyr_x;
	float	plyr_y;
	float	fov_rd;
	float	angle;
	int		l_r;
	int		u_d;
}			t_player;

typedef struct s_ray
{
	double	ray_ngl;
	double	distance;
	int		is_horizontal;
}			t_ray;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}			t_img;

typedef struct s_mlx
{
	void		*mlx;
	t_img		*img;
	void		*win;
	t_map		*map;
	t_ray		*ray;
	t_player	*plyr;
}			t_mlx;

/* init_player */
int		init_player(t_mlx *mlx);
void	display_player(t_player *plyr);

/* utils */
int		free_mlx(t_mlx *mlx);
int		ft_error(char *errormsg, t_mlx *mlx);
double	normalize(double angle);

/* parse_map */
void	parse_map(char *file, t_mlx *mlx);

/* raycasting */
void	cast_rays(t_mlx *mlx);

/* render */
void	render(t_mlx *mlx, int x);

/* clean_init */
void	init_empty_player(t_player *plyr);
void	init_mlx(t_mlx *mlx, char **argv);

/* game_loop */
void	start_game(t_mlx *mlx);

/* movement */
int		key_push(int keycode, t_mlx *mlx);
int		key_release(int keycode, t_mlx *mlx);
int		key_destroy(t_mlx *mlx);
void	update_player_mvmt(t_mlx *mlx, int move_x, int move_y);

#endif