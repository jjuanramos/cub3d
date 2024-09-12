/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:15:46 by juramos           #+#    #+#             */
/*   Updated: 2024/09/12 16:08:22 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	free_mlx(t_mlx *mlx)
{
	int	i;

	if (mlx->plyr)
		free(mlx->plyr);
	if (mlx->img)
		free(mlx->img);
	if (mlx->map)
	{
		i = -1;
		while (++i < mlx->map->height)
			free(mlx->map->map[i]);
		free(mlx->map->map);
		free(mlx->map);
	}
	if (mlx->mlx && mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	return (0);
}

int	ft_error(char *errormsg, t_mlx *mlx)
{
	printf("%s\n", errormsg);
	if (mlx)
		free_mlx(mlx);
	exit(1);
}

double	normalize(double angle)
{
	if (angle < 0)
		return (angle + 2 * M_PI);
	else if (angle > 2 * M_PI)
		return (angle - 2 * M_PI);
	return (angle);
}
