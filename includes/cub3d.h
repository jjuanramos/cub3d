/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:09:45 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/09/17 13:32:30 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define MAPWIDTH 24
# define MAPHEIGHT 24
# define SCREENWIDTH 640
# define SCREENHEIGHT 480
# define TILE_SIZE 32
# define FOV 60
# define ROTATION_SPEED 0.025
# define PLAYER_SPEED 4

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
# include <X11/keysym.h>
# include <X11/X.h>

typedef struct s_map
{
	char	**map;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
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
	int		bpp;
	int		size_line;
	int		endian;
}			t_img;

typedef struct	s_texture
{
	t_img	*text;
	int		width;
	int		height;	
}				t_texture;		

typedef struct s_mlx
{
	void		*mlx;
	t_img		*img;
	void		*win;
	t_map		*map;
	t_ray		*ray;
	t_player	*plyr;
	t_texture	*no_text;
	t_texture	*so_text;
	t_texture	*ea_text;
	t_texture	*we_text;
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
void	init_empty_mlx(t_mlx *mlx);
int		init_empty_img(t_img **img);
int		init_empty_ray(t_mlx *mlx);
int 	init_empty_text(t_texture **text);

/* game_loop */
void	start_game(t_mlx *mlx);

/* movement */
void	hook_player_mvmt(t_mlx *mlx);

/* key_hooks */
int		key_destroy(t_mlx *mlx);
int		key_push(int keycode, t_mlx *mlx);
int		key_release(int keycode, t_mlx *mlx);

/* textures */
int		init_textures(t_mlx *mlx);

#endif