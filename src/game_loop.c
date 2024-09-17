/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camunozg <camunozg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:36:51 by juramos           #+#    #+#             */
/*   Updated: 2024/09/17 12:19:28 by camunozg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	game_loop(void *ml)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)ml;
	mlx->img->img = mlx_new_image(mlx->mlx, SCREENWIDTH, SCREENHEIGHT);
	if (!mlx->img->img)
		ft_error("Error creating image", mlx);
	mlx->img->addr = (int *)mlx_get_data_addr(mlx->img->img,
			&(mlx->img->bpp),
			&(mlx->img->size_line), &(mlx->img->endian));
	hook_player_mvmt(mlx);
	cast_rays(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
	mlx_destroy_image(mlx->mlx, mlx->img->img);
	return (0);
}

void	start_game(t_mlx *mlx)
{
	mlx->win = mlx_new_window(mlx->mlx, SCREENWIDTH, SCREENHEIGHT, "Cub3D");
	mlx_loop_hook(mlx->mlx, &game_loop, mlx);
	mlx_hook(mlx->win, ON_KEY_DOWN, 1L << 0, key_push, mlx);
	mlx_hook(mlx->win, ON_KEY_UP, 1L << 1, key_release, mlx);
	mlx_hook(mlx->win, ON_DESTROY, 0L, key_destroy, mlx);
	mlx_loop(mlx->mlx);
	free_mlx(mlx);
}
