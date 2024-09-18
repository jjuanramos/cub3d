/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:23:11 by juramos           #+#    #+#             */
/*   Updated: 2024/09/18 11:45:28 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// static int	get_color(t_mlx *mlx);
static void	draw_wall(t_mlx *mlx, double t_pixel, double b_pixel,
				double wall_height);
static void	draw_floor_ceiling(t_mlx *mlx, double t_pixel,
				double b_pixel);
static void	set_image_pixel(t_img *img, int x, int y, int color);
void		render(t_mlx *mlx, int x);

static void	set_image_pixel(t_img *img, int x, int y, int color)
{
	int	pixel;

	pixel = y * (img->size_line / 4) + x;
	img->addr[pixel] = color;
}

// static int	get_color(t_mlx *mlx)
// {
// 	double	norm_ngl;

// 	norm_ngl = normalize(mlx->ray->ray_ngl);
// 	if (mlx->ray->is_horizontal)
// 	{
// 		if (norm_ngl > 0 && norm_ngl < M_PI)
// 			return (0xB5B5B5FF);
// 		else
// 			return (0x959595FF);
// 	}
// 	else
// 	{
// 		if (norm_ngl > M_PI / 2 && norm_ngl < (3 * M_PI / 2))
// 			return (0xD5D5D5FF);
// 		else
// 			return (0xF5F5F5FF);
// 	}
// }

static t_texture	*get_texture(t_mlx *mlx, double norm_ngl)
{
	if (mlx->ray->is_horizontal)
	{
		if (norm_ngl > 0 && norm_ngl < M_PI)
			return (mlx->no_text);
		else
			return (mlx->so_text);
	}
	else
	{
		if (norm_ngl > M_PI / 2 && norm_ngl < (3 * M_PI / 2))
			return (mlx->we_text);
		else
			return (mlx->ea_text);
	}
	return (NULL);
}

static double	get_x_offset(t_texture *text, t_mlx *mlx)
{
	double	x_offset;

	if (mlx->ray->is_horizontal)
		x_offset = (int)fmodf(
				(mlx->ray->horiz_x * (text->width / TILE_SIZE)),
				text->width
				);
	else
		x_offset = (int)fmodf(
				(mlx->ray->vert_y * (text->width / TILE_SIZE)),
				text->width
				);
	return (x_offset);
}

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
		set_image_pixel(mlx->img, mlx->ray->index, i++, 0xB99470FF);
	i = t_pixel;
	while (i > 0)
		set_image_pixel(mlx->img, mlx->ray->index, i--, 0x89CFF3FF);
}

// (TILE_SIZE / distance): scales wall height by distance;
// (SCREENWIDTH / 2) / tan(fov/2): finds projection plane distance for FOV.
void	render(t_mlx *mlx, int i)
{
	double	wall_height;
	double	b_pixel;
	double	t_pixel;

	mlx->ray->distance *= cos(normalize(mlx->ray->ray_ngl - mlx->plyr->angle)); // to prevent fisheye
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
