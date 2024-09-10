/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:15:46 by juramos           #+#    #+#             */
/*   Updated: 2024/09/10 11:43:09 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	free_mlx(t_mlx *mlx)
{
	int	i;

	if (mlx->plyr)
		free(mlx->plyr);
	if (mlx->map)
	{
		i = -1;
		while (++i < mlx->map->height)
			free(mlx->map->map[i]);
		free(mlx->map->map);
		free(mlx->map);
	}
	mlx_destroy_window(mlx->mlx, mlx->win);
	return (0);
}

int	ft_error(char *errormsg, t_mlx *mlx)
{
	printf("%s\n", errormsg);
	free_mlx(mlx);
	exit(1);
}
