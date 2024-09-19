/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:23:11 by juramos           #+#    #+#             */
/*   Updated: 2024/09/19 13:00:20 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// static int	get_color(t_mlx *mlx);
static void	draw_wall(t_mlx *mlx, double t_pixel, double b_pixel,
				double wall_height);
static void	draw_floor_ceiling(t_mlx *mlx, double t_pixel,
				double b_pixel);
void		render(t_mlx *mlx, int x);

static void	draw_wall(t_mlx *mlx, double t_pixel, double b_pixel,
	double wall_height)
{
	t_texture	*texture;
	double		factor;
	double		x_offset;
	double		y_offset;
	int			text_pos;

	texture = get_texture(mlx, normalize(mlx->ray->ray_ngl));
	factor = (double)texture->height / wall_height;
	x_offset = get_x_offset(texture, mlx);
	if (x_offset >= texture->width)
		x_offset = texture->width - 1;
	y_offset = (t_pixel - (SCREENHEIGHT / 2) + (wall_height / 2)) * factor;
	if (y_offset < 0)
		y_offset = 0;
	while (t_pixel < b_pixel)
	{
		if (y_offset >= texture->height)
			y_offset = texture->height - 1;
		text_pos = (int)y_offset * (texture->text->size_line / 4) \
			+ (int)x_offset;
		set_image_pixel(mlx->img, mlx->ray->index, t_pixel++,
			texture->text->addr[text_pos]);
		y_offset += factor;
	}
}

static void	draw_floor_ceiling(t_mlx *mlx, double t_pixel,
	double b_pixel)
{
	int	i;

	i = b_pixel;
	while (i < SCREENHEIGHT)
		set_image_pixel(mlx->img, mlx->ray->index, i++, \
		get_rgb(mlx->map->floor_color));
	i = t_pixel;
	while (i > 0)
		set_image_pixel(mlx->img, mlx->ray->index, i--, \
		get_rgb(mlx->map->ceiling_color));
}

/*
	(TILE_SIZE / distance): scales wall height by distance;
	(SCREENWIDTH / 2) / tan(fov/2): finds projection plane distance for FOV.
	mlx->ray->distance implements cos of
	normalized angle in order to prevent fisheye.
*/
void	render(t_mlx *mlx, int i)
{
	double	wall_height;
	double	b_pixel;
	double	t_pixel;

	mlx->ray->distance *= cos(normalize(mlx->ray->ray_ngl - mlx->plyr->angle));
	wall_height = (TILE_SIZE / mlx->ray->distance)
		* ((SCREENWIDTH / 2) / tan(mlx->plyr->fov_rd / 2));
	b_pixel = (SCREENHEIGHT / 2) + (wall_height / 2);
	t_pixel = (SCREENHEIGHT / 2) - (wall_height / 2);
	if (b_pixel > SCREENHEIGHT)
		b_pixel = SCREENHEIGHT;
	if (t_pixel < 0)
		t_pixel = 0;
	mlx->ray->index = i;
	draw_wall(mlx, t_pixel, b_pixel, wall_height);
	draw_floor_ceiling(mlx, t_pixel, b_pixel);
}
