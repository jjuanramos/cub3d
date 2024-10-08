/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmunoz-g <cmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:09:45 by cmunoz-g          #+#    #+#             */
/*   Updated: 2024/09/23 10:26:28 by cmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define MAPWIDTH 24
# define MAPHEIGHT 24
# define SCREENWIDTH 1280
# define SCREENHEIGHT 960
# define TILE_SIZE 32
# define FOV 60
# define ROTATION_SPEED 0.04
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
	int		*floor_color;
	int		*ceiling_color;
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
	double	horiz_x;
	double	horiz_y;
	double	vert_x;
	double	vert_y;
	int		index;
}			t_ray;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bpp;
	int		size_line;
	int		endian;
}			t_img;

typedef struct s_texture
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
int			init_player(t_mlx *mlx);
void		display_player(t_player *plyr);
int			is_pos(char c);

/* utils */
int			free_mlx(t_mlx *mlx);
int			ft_error(char *errormsg, t_mlx *mlx);
double		normalize(double angle);

/* parse_map */
void		parse_map(char *file, t_mlx *mlx);

/* raycasting */
void		cast_rays(t_mlx *mlx);

/* raycasting_utils */
int			check_orientation(double norm_ngl, double *next_inter,
				double *delta, int is_horizon);
int			is_down_or_left(double norm_ngl, int is_horizon);
int			check_wall(double x, double y, t_mlx *mlx);

/* render */
void		render(t_mlx *mlx, int x);

/* render_utils */
int			get_rgb(int *rgb);
void		set_image_pixel(t_img *img, int x, int y, int color);
t_texture	*get_texture(t_mlx *mlx, double norm_ngl);
double		get_x_offset(t_texture *text, t_mlx *mlx);

/* clean_init */
void		init_empty_player(t_player *plyr);
void		init_empty_mlx(t_mlx *mlx);
int			init_empty_img(t_img **img);
int			init_empty_ray(t_mlx *mlx);
int			init_empty_text(t_texture **text);

/* game_loop */
void		start_game(t_mlx *mlx);

/* movement */
void		hook_player_mvmt(t_mlx *mlx);

/* key_hooks */
int			key_destroy(t_mlx *mlx);
int			key_push(int keycode, t_mlx *mlx);
int			key_release(int keycode, t_mlx *mlx);

/* textures */
int			init_textures(t_mlx *mlx);

/* parse_checks */
int			check_row(char *line);
void		check_zeros_out_of_bounds(char **map, t_mlx *mlx);
void		check_map_is_together(char **map, t_mlx *mlx);
int			check_file_extension(char *file);

/* parse_checks_2 */
int			is_empty(char *line);
int			is_valid_char(char c);
int			is_valid_str_clr_cntnt(char *str, char to_find);
int			ft_isspace2(char c);
int			check_space_edges(char **map, int row, int i);

/* parse_getters */
int			get_line_nbr(char **map);
char		*get_text(char **read, char *to_find);
int			*get_rgb_int_arr(char *line);
int			*get_color_parse(char **read, char *to_find);
int			get_width(char **map);

/* parse_arr_helpers */
void		free_arr(char **arr);
void		ft_arrdup(char **dst, char **src);
char		**append_str(char **map, char *buf);
int			ft_arrlen(char **arr);

/* parse_tools */
char		*trim_path(char *path, char *prefix);
void		replace_spaces_with_ones(t_map *map);
int			find_horizontal_zeros(char *line,
				int *row_col, int inc, char **map);

#endif