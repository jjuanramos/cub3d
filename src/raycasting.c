/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camunozg <camunozg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:12:00 by juramos           #+#    #+#             */
/*   Updated: 2024/09/12 12:24:29 by camunozg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_orientation(t_mlx *mlx, int *next_inter, int *delta, int is_horizon)
{
	if (is_horizon)
	{
		if (mlx->plyr->angle >= 0 && mlx->plyr->angle < M_PI) // checks if the ray is facing downwards
		{
			*next_inter += TILE_SIZE;	// moves the y intersection point to a the horizontal line below
			return (1);
		}
		*delta *= -1; // increments are negative if facing south (upwards)
	}
	else 
	{
		if (!((mlx->plyr->angle >= M_PI / 2 ) && (mlx->plyr->angle < (3 * M_PI / 2))))
		{
			*next_inter += TILE_SIZE;
			return (1);
		}
		*delta *= -1;
	}
	return (-1);
}
int	is_neg_orientation(t_mlx *mlx, int is_horizon)
{
	if (is_horizon)
		if (!(mlx->plyr->angle >= 0 && mlx->plyr->angle < M_PI))
			return (1);
	else 
		if ((mlx->plyr->angle >= M_PI / 2 && mlx->plyr->angle < (3 * M_PI / 2)))
			return (1);
	return (0);
}

double	get_h_inter(t_mlx *mlx, double norm_ngl)
{
	float	x_delta;
	float	y_delta;
	float 	y_next_inter;
	float	x_next_inter;
	int		corrector;
	
	y_delta = TILE_SIZE;
	x_delta = TILE_SIZE * tan(norm_ngl);
	y_next_inter = (floor(mlx->plyr->plyr_y / TILE_SIZE) * TILE_SIZE);
	x_next_inter = mlx->plyr->plyr_x + (y_next_inter - mlx->plyr->plyr_y) / tan(norm_ngl);
	corrector = check_orientation(mlx, &y_next_inter, &y_delta, 1);
	if ((is_neg_orientation(mlx, 0) && x_delta > 0) || (!is_neg_orientation(mlx, 0) && x_delta < 0))
		x_delta *= -1;
	while (!check_wall(x_next_inter, y_next_inter + corrector, mlx))
	{
		x_next_inter += x_delta;
		y_next_inter += y_delta;
	}
	return (sqrt(pow(x_next_inter - mlx->plyr->plyr_x, 2) + pow(y_next_inter - mlx->plyr->plyr_y, 2))) 
	// we return the hypothenuse (distance) of the triangle formed by the original point and the final intersection (the one that hits a wall).
}

double	get_v_inter(t_mlx *mlx, double norm_ngl)
{
	float	x_delta;
	float	y_delta;
	float 	y_next_inter;
	float	x_next_inter;
	int		corrector;
	
	x_delta = TILE_SIZE;
	y_delta = TILE_SIZE * tan(norm_ngl);
	x_next_inter = (floor(mlx->plyr->plyr_x / TILE_SIZE) * TILE_SIZE);
	y_next_inter = mlx->plyr->plyr_y + (x_next_inter - mlx->plyr->plyr_x) / tan(norm_ngl);
	corrector = check_orientation(mlx, &x_next_inter, &x_delta, 1);
	if ((is_neg_orientation(mlx, 1) && y_delta > 0) || (!is_neg_orientation(mlx, 1) && y_delta < 0))
		y_delta *= -1;
	while (!check_wall(y_next_inter, x_next_inter + corrector, mlx))
	{
		x_next_inter += x_delta;
		y_next_inter += y_delta;
	}
	return (sqrt(pow(x_next_inter - mlx->plyr->plyr_x, 2) + pow(y_next_inter - mlx->plyr->plyr_y, 2))) 
}

double	normalize(double angle)
{
	if (angle < 0) 
		return (angle + 2 * M_PI);
	else if (angle > 2 * M_PI)
		return (angle - 2 * M_PI);
	return (angle);
}
int	get_color(t_mlx *mlx)
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

void	draw_wall(t_mlx *mlx, double t_pixel, double b_pixel, int x)
{
	int	color;

	color = get_color(mlx);
	while (t_pixel < b_pixel)
		mlx_put_pixel(mlx->img, x, t_pixel++, color);
}

void	draw_floor_ceiling(t_mlx *mlx, double t_pixel, double b_pixel, int x)
{
	int	i;

	i = SCREENHEIGHT - 1;
	while (i > b_pixel)
		mlx_put_pixel(mlx->img, x, i--, 0xB99470FF);
	i = 0;
	while (i < t_pixel)
		mlx_put_pixel(mlx->img, x, i++, 0x89CFF3FF);
}

void	render(t_mlx *mlx, int x)
{
	double	wall_height;
	double	b_pixel;
	double	t_pixel;
	
	mlx->ray->distance *= cos(normalize(mlx->ray->ray_ngl - mlx->plyr->angle));
	wall_height = (TILE_SIZE / mlx->ray->distance) * ((SCREENWIDTH / 2) / tan(mlx->plyr->fov_rd / 2));
	// (TILE_SIZE / distance): scales wall height by distance; (SCREENWIDTH / 2) / tan(fov/2): finds projection plane distance for FOV.
	b_pixel = (SCREENHEIGHT / 2) + (wall_height / 2);
	t_pixel = (SCREENHEIGHT / 2) - (wall_height / 2);
	if (b_pixel > SCREENHEIGHT)
		b_pixel = SCREENHEIGHT;
	if (t_pixel < 0)
		t_pixel = 0;
	draw_wall(mlx, t_pixel, b_pixel, x);
	draw_floor_ceiling(mlx, t_pixel, b_pixel, x);	
}

void	cast_rays(t_mlx *mlx)
{
	int		i;	
	double	h_inter;
	double	v_inter;

	i = 0;
	mlx->ray->ray_ngl = mlx->plyr->angle - (mlx->plyr->fov_rd / 2);
	mlx->ray->is_horizontal = 0;
	while (i < SCREENWIDTH)
	{
		h_inter = get_h_inter(mlx, normalize(mlx->ray->ray_ngl));
		v_inter = get_v_inter(mlx, normalize(mlx->ray->ray_ngl));
		if (h_inter < v_inter)
		{
			mlx->ray->distance = h_inter;
			mlx->ray->is_horizontal = 1;
		}
		else 
			mlx->ray->distance = v_inter;		
		render(mlx, i);
		mlx->ray->ray_ngl += (mlx->plyr->fov_rd / SCREENWIDTH);
		i++;
	}

}
