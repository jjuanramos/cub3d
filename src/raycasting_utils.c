/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camunozg <camunozg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:53:36 by juramos           #+#    #+#             */
/*   Updated: 2024/09/20 12:03:55 by camunozg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_orientation(double norm_ngl, double *next_inter,
		double *delta, int is_horizon);
int	is_down_or_left(double norm_ngl, int is_horizon);
int	check_wall(double x, double y, t_mlx *mlx);

/*
	When our angle is oriented towards the horizontal plane (that is,
	north or south), if we are looking north then we'll jump to the
	following tile. If we are looking south, we'll change the delta,
	as we'll be going upwards in the map (that is, substracting).

	We do the same when the angle is looking east or west, east being
	positive and west, negative.
*/
int	check_orientation(double norm_ngl, double *next_inter,
		double *delta, int is_horizon)
{
	if (is_horizon)
	{
		if (norm_ngl > 0 && norm_ngl < M_PI)
		{
			*next_inter += TILE_SIZE;
			return (1);
		}
		*delta *= -1;
	}
	else
	{
		if (!((norm_ngl > M_PI / 2) && (norm_ngl < (3 * M_PI / 2))))
		{
			*next_inter += TILE_SIZE;
			return (1);
		}
		*delta *= -1;
	}
	return (-1);
}

int	is_down_or_left(double norm_ngl, int is_horizon)
{
	if (is_horizon)
	{
		if (norm_ngl > 0 && norm_ngl < M_PI)
			return (1);
	}
	else
	{
		if ((norm_ngl > (M_PI) / 2 && norm_ngl < (3 * M_PI / 2)))
			return (1);
	}
	return (0);
}

int	check_wall(double x, double y, t_mlx *mlx)
{
	int	x_map;
	int	y_map;

	if (x < 0 || y < 0)
		return (1);
	x_map = floor(x / TILE_SIZE);
	y_map = floor(y / TILE_SIZE);
	if (x_map > mlx->map->width - 1
		|| y_map > mlx->map->height - 1)
		return (1);
	if (mlx->map->map[y_map] && x_map <= (int)ft_strlen(mlx->map->map[y_map]))
		if (mlx->map->map[y_map][x_map] == '1')
			return (1);
	return (0);
}
