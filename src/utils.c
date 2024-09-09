/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:15:46 by juramos           #+#    #+#             */
/*   Updated: 2024/09/09 10:23:40 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	free_mlx(t_mlx *mlx)
{
	int	i;

	if (mlx->plyr)
		free(mlx->plyr);
	if (mlx->dt)
	{
		i = -1;
		while (++i < mlx->dt->h_map)
			free(mlx->dt->map2d[i]);
		free(mlx->dt->map2d);
		free(mlx->dt);
	}
	return (0);
}
