/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:12:00 by juramos           #+#    #+#             */
/*   Updated: 2024/09/13 12:07:59 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_orientation(double norm_ngl, float *next_inter,
				float *delta, int is_horizon);
static int	is_neg_orientation(double norm_ngl, int is_horizon);
static int	check_wall(float x, float y, t_mlx *mlx);

static int	check_orientation(double norm_ngl, float *next_inter,
		float *delta, int is_horizon)
{
	if (is_horizon)
	{
		if (norm_ngl > 0 && norm_ngl < M_PI) // checks if the ray is facing downwards
		{
			*next_inter += TILE_SIZE;	// moves the y intersection point to a the horizontal line below
			return (1);
		}
		*delta *= -1; // increments are negative if facing south (upwards)
	}
	else 
	{
		if (!((norm_ngl > M_PI / 2 ) && (norm_ngl < (3 * M_PI / 2))))
		{
			*next_inter += TILE_SIZE;
			return (1);
		}
		*delta *= -1;
	}
	return (-1);
}

static int	is_neg_orientation(double norm_ngl, int is_horizon)
{
	if (is_horizon)
	{
		if (!(norm_ngl > 0 && norm_ngl < M_PI))
			return (1);
	}
	else
	{
		if ((norm_ngl > M_PI / 2 && norm_ngl < (3 * M_PI / 2)))
			return (1);
	}
	return (0);
}

static int	check_wall(float x, float y, t_mlx *mlx)
{
	int	x_map;
	int	y_map;

	if (x < 0 || y < 0)
		return (1);
	x_map = floor(x / TILE_SIZE);
	y_map = floor(y / TILE_SIZE);
	if (x_map > mlx->map->width
		|| y_map > mlx->map->height)
		return (1);
	if (mlx->map->map[y_map] && x_map <= (int)ft_strlen(mlx->map->map[y_map]))
		if (mlx->map->map[y_map][x_map] == '1')
			return (1);
	return (0);
}

double	get_h_inter(t_mlx *mlx, double norm_ngl)
{
	float	x_delta;
	float	y_delta;
	float	y_next_inter;
	float	x_next_inter;
	int		corrector;

	y_delta = TILE_SIZE;
	x_delta = TILE_SIZE / tan(norm_ngl);
	y_next_inter = (floor(mlx->plyr->plyr_y / TILE_SIZE) * TILE_SIZE);
	x_next_inter = mlx->plyr->plyr_x + (y_next_inter - mlx->plyr->plyr_y) / tan(norm_ngl);
	corrector = check_orientation(norm_ngl, &y_next_inter, &y_delta, 1);
	if ((is_neg_orientation(norm_ngl, 0) && x_delta > 0) || (!is_neg_orientation(norm_ngl, 0) && x_delta < 0))
		x_delta *= -1;
	while (!check_wall(x_next_inter, y_next_inter + corrector, mlx))
	{
		x_next_inter += x_delta;
		y_next_inter += y_delta;
	}
	return (sqrt(pow(x_next_inter - mlx->plyr->plyr_x, 2) + pow(y_next_inter - mlx->plyr->plyr_y, 2)));
	// we return the hypothenuse (distance) of the triangle formed by the original point and the final intersection (the one that hits a wall).
}

double	get_v_inter(t_mlx *mlx, double norm_ngl)
{
	float	x_delta;
	float	y_delta;
	float	y_next_inter;
	float	x_next_inter;
	int		corrector;

	x_delta = TILE_SIZE;
	y_delta = TILE_SIZE * tan(norm_ngl);
	x_next_inter = (floor(mlx->plyr->plyr_x / TILE_SIZE) * TILE_SIZE);
	y_next_inter = mlx->plyr->plyr_y + (x_next_inter - mlx->plyr->plyr_x) * tan(norm_ngl);
	corrector = check_orientation(norm_ngl, &x_next_inter, &x_delta, 0);
	if ((is_neg_orientation(norm_ngl, 1) && y_delta < 0) || (!is_neg_orientation(norm_ngl, 1) && y_delta > 0))
		y_delta *= -1;
	while (!check_wall(x_next_inter + corrector, y_next_inter, mlx))
	{
		x_next_inter += x_delta;
		y_next_inter += y_delta;
	}
	return (sqrt(pow(x_next_inter - mlx->plyr->plyr_x, 2) + pow(y_next_inter - mlx->plyr->plyr_y, 2)));
}

void	cast_rays(t_mlx *mlx)
{
	int		i;	
	double	h_inter;
	double	v_inter;

	i = 0;
	mlx->ray->ray_ngl = mlx->plyr->angle - (mlx->plyr->fov_rd / 2);
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
