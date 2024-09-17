/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:42:47 by juramos           #+#    #+#             */
/*   Updated: 2024/09/17 08:43:40 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

int		key_destroy(t_mlx *mlx);
int		key_push(int keycode, t_mlx *mlx);
int		key_release(int keycode, t_mlx *mlx);

int	key_push(int keycode, t_mlx *mlx)
{
	if (keycode == XK_a)
		mlx->plyr->l_r = -1;
	if (keycode == XK_s)
		mlx->plyr->u_d = -1;
	if (keycode == XK_w)
		mlx->plyr->u_d = 1;
	if (keycode == XK_d)
		mlx->plyr->l_r = 1;
	if (keycode == XK_Left)
		mlx->plyr->rot_dir = -1;
	if (keycode == XK_Right)
		mlx->plyr->rot_dir = 1;
	if (keycode == XK_Escape)
		key_destroy(mlx);
	return (0);
}

int	key_release(int keycode, t_mlx *mlx)
{
	if (keycode == XK_a || keycode == XK_d)
		mlx->plyr->l_r = 0;
	if (keycode == XK_s || keycode == XK_w)
		mlx->plyr->u_d = 0;
	if (keycode == XK_Left || keycode == XK_Right)
		mlx->plyr->rot_dir = 0;
	return (0);
}

int	key_destroy(t_mlx *mlx)
{
	free_mlx(mlx);
	exit(0);
	return (0);
}
