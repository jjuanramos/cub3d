/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camunozg <camunozg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:23:11 by juramos           #+#    #+#             */
/*   Updated: 2024/09/16 10:18:40 by camunozg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	get_color(t_mlx *mlx);
static void	draw_wall(t_mlx *mlx, double t_pixel, double b_pixel, int x);
static void	draw_floor_ceiling(t_mlx *mlx, double t_pixel,
				double b_pixel, int x);
static void	set_image_pixel(t_img *img, int x, int y, int color);
void		render(t_mlx *mlx, int x);

static void	set_image_pixel(t_img *img, int x, int y, int color)
{
	int	pixel;

	pixel = y * (img->size_line / 4) + x;
	img->addr[pixel] = color;
}

static int	get_color(t_mlx *mlx)
{
	double	norm_ngl;

	norm_ngl = normalize(mlx->ray->ray_ngl);
	if (mlx->ray->is_horizontal)
	{
		if (norm_ngl > 0 && norm_ngl < M_PI)
			return (0xB5B5B5FF);
		else
			return (0x959595FF);
	}
	else
	{
		if (norm_ngl > M_PI / 2 && norm_ngl < (3 * M_PI / 2))
			return (0xD5D5D5FF);
		else
			return (0xF5F5F5FF);
	}
}

static void	draw_wall(t_mlx *mlx, double t_pixel, double b_pixel, int x)
{
	int	color;

	color = get_color(mlx);
	while (t_pixel < b_pixel)
		set_image_pixel(mlx->img, x, t_pixel++, color);
}

static void	draw_floor_ceiling(t_mlx *mlx, double t_pixel,
	double b_pixel, int x)
{
	int	i;

	i = b_pixel;
	while (i < SCREENHEIGHT)
		set_image_pixel(mlx->img, x, i++, 0xB99470FF);
	i = t_pixel;
	while (i > 0)
		set_image_pixel(mlx->img, x, i--, 0x89CFF3FF);
}
// (TILE_SIZE / distance): scales wall height by distance;
// (SCREENWIDTH / 2) / tan(fov/2): finds projection plane distance for FOV.
void	render(t_mlx *mlx, int x)
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
	draw_wall(mlx, t_pixel, b_pixel, x);
	draw_floor_ceiling(mlx, t_pixel, b_pixel, x);
}
