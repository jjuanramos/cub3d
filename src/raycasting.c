/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camunozg <camunozg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:12:00 by juramos           #+#    #+#             */
/*   Updated: 2024/09/20 11:58:11 by camunozg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	We return the hypothenuse (distance) of the triangle formed by
	the original point and the final intersection
	(the one that hits a wall).
*/
static double	get_h_inter(t_mlx *mlx, double norm_ngl)
{
	float	x_delta;
	float	y_delta;
	float	y_next_inter;
	float	x_next_inter;
	int		corrector;

	y_delta = TILE_SIZE;
	x_delta = TILE_SIZE / tan(norm_ngl);
	y_next_inter = (floor(mlx->plyr->plyr_y / TILE_SIZE) * TILE_SIZE);
	corrector = check_orientation(norm_ngl, &y_next_inter, &y_delta, 1);
	x_next_inter = mlx->plyr->plyr_x + (y_next_inter - mlx->plyr->plyr_y) \
	/ tan(norm_ngl);
	if ((is_down_or_left(norm_ngl, 0) && x_delta > 0)
		|| (!is_down_or_left(norm_ngl, 0) && x_delta < 0))
		x_delta *= -1;
	while (!check_wall(x_next_inter, y_next_inter + corrector, mlx))
	{
		x_next_inter += x_delta;
		y_next_inter += y_delta;
	}
	mlx->ray->horiz_x = x_next_inter;
	mlx->ray->horiz_y = y_next_inter;
	return (sqrt(pow(x_next_inter - mlx->plyr->plyr_x, 2)
			+ pow(y_next_inter - mlx->plyr->plyr_y, 2)));
}

static double	get_v_inter(t_mlx *mlx, double norm_ngl)
{
	float	x_delta;
	float	y_delta;
	float	y_next_inter;
	float	x_next_inter;
	int		corrector;

	x_delta = TILE_SIZE;
	y_delta = TILE_SIZE * tan(norm_ngl);
	x_next_inter = (floor(mlx->plyr->plyr_x / TILE_SIZE) * TILE_SIZE);
	corrector = check_orientation(norm_ngl, &x_next_inter, &x_delta, 0);
	y_next_inter = mlx->plyr->plyr_y + (x_next_inter - mlx->plyr->plyr_x) \
	* tan(norm_ngl);
	if ((is_down_or_left(norm_ngl, 1) && y_delta < 0)
		|| (!is_down_or_left(norm_ngl, 1) && y_delta > 0))
		y_delta *= -1;
	while (!check_wall(x_next_inter + corrector, y_next_inter, mlx))
	{
		x_next_inter += x_delta;
		y_next_inter += y_delta;
	}
	mlx->ray->vert_x = x_next_inter;
	mlx->ray->vert_y = y_next_inter;
	return (sqrt(pow(x_next_inter - mlx->plyr->plyr_x, 2)
			+ pow(y_next_inter - mlx->plyr->plyr_y, 2)));
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
		mlx->ray->is_horizontal = 0;
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
