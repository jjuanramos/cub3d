/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:15:46 by juramos           #+#    #+#             */
/*   Updated: 2024/09/19 12:21:29 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->no_path)
		free(map->no_path);
	if (map->so_path)
		free(map->so_path);
	if (map->ea_path)
		free(map->ea_path);
	if (map->we_path)
		free(map->we_path);
	if (map->floor_color)
		free(map->floor_color);
	if (map->ceiling_color)
		free(map->ceiling_color);
	if (map->map)
	{
		i = -1;
		while (map->map[++i])
			free(map->map[i]);
		free(map->map);
	}
}

int	free_mlx(t_mlx *mlx)
{
	if (mlx->plyr)
		free(mlx->plyr);
	if (mlx->img)
		free(mlx->img);
	free_map(mlx->map);
	if (mlx->mlx && mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	exit(0);
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
