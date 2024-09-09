/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:58:31 by juramos           #+#    #+#             */
/*   Updated: 2024/09/09 13:33:27 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_dt(t_mlx *mlx)
{
	mlx->dt = ft_calloc(sizeof(t_data), 1);
	if (!mlx->dt)
		return (1);
	mlx->dt->map2d = ft_calloc(10, sizeof(char *));
	if (!mlx->dt->map2d)
		return (1);
	mlx->dt->map2d[0] = strdup("1111111111111111111111111");
	mlx->dt->map2d[1] = strdup("1000000000000000000100001");
	mlx->dt->map2d[2] = strdup("1001000000000S00000000001");
	mlx->dt->map2d[3] = strdup("1001000000000000001000001");
	mlx->dt->map2d[4] = strdup("1001000000000000001000001");
	mlx->dt->map2d[5] = strdup("1001000000100000001000001");
	mlx->dt->map2d[6] = strdup("1001000000000000001000001");
	mlx->dt->map2d[7] = strdup("1001000000001000001000001");
	mlx->dt->map2d[8] = strdup("1111111111111111111111111");
	mlx->dt->map2d[9] = NULL;
	mlx->dt->h_map = 10;
	mlx->dt->w_map = 25;
	return (0);
}

void	start_game(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, SCREENWIDTH, SCREENHEIGHT, "Cub3D");
	mlx_loop(mlx->mlx);
	mlx->img = mlx_new_image(mlx->mlx_p, SCREENWIDTH, SCREENHEIGHT);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int	main(void)
{
	t_mlx		mlx;

	if (init_dt(&mlx))
		return (1);
	if (init_player(&mlx))
		return (1);
	display_player(mlx.plyr);
	start_game(&mlx);
	free_mlx(&mlx);
	return (0);
}

