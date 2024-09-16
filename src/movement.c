/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:52:36 by juramos           #+#    #+#             */
/*   Updated: 2024/09/16 13:53:59 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_destroy(t_mlx *mlx);

int	key_push(int keycode, t_mlx *mlx)
{
	printf("on push called!\n");
	if (keycode == KEY_A)
		mlx->plyr->l_r = -1;
	if (keycode == KEY_S)
		mlx->plyr->u_d = -1;
	if (keycode == KEY_W)
		mlx->plyr->u_d = 1;
	if (keycode == KEY_D)
		mlx->plyr->l_r = 1;
	if (keycode == KEY_LEFT)
		mlx->plyr->rot_dir = -1;
	if (keycode == KEY_RIGHT)
		mlx->plyr->rot_dir = 1;
	if (keycode == KEY_ESC)
		key_destroy(mlx);
	return (0);
}

int	key_release(int keycode, t_mlx *mlx)
{
	printf("on release called!\n");
	if (keycode == KEY_A || keycode == KEY_D)
		mlx->plyr->l_r = 0;
	if (keycode == KEY_S || keycode == KEY_W)
		mlx->plyr->u_d = 0;
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		mlx->plyr->rot_dir = 0;
	return (0);
}

int	key_destroy(t_mlx *mlx)
{
	printf("on destroy called!\n");
	free_mlx(mlx);
	exit(0);
	return (0);
}

// void	update_player_mvmt(t_mlx *mlx, int move_x, int move_y)
// {

// }
