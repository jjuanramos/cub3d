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

int		key_destroy(t_mlx *mlx);
int		key_push(int keycode, t_mlx *mlx);
int		key_release(int keycode, t_mlx *mlx);
void	hook_player_mvmt(t_mlx *mlx);
void	move_left_right(t_mlx *mlx, int *move_x, int *move_y);
void	move_up_down(t_mlx *mlx, int *move_x, int *move_y);
void	rotate_player(t_mlx *mlx);
void	move_player(t_mlx *mlx, int move_x, int move_y);

/*
	1 equals moving to the right,
	-1, to the left.
*/
void	move_left_right(t_mlx *mlx, int *move_x, int *move_y)
{
	if (mlx->plyr->l_r == 1)
	{
		*move_x = -sin(mlx->plyr->angle) * PLAYER_SPEED;
		*move_y = cos(mlx->plyr->angle) * PLAYER_SPEED;
	}
	else
	{
		*move_x = sin(mlx->plyr->angle) * PLAYER_SPEED;
		*move_y = -cos(mlx->plyr->angle) * PLAYER_SPEED;
	}
}

/*
	1 equals moving up,
	-1, down.
*/
void	move_up_down(t_mlx *mlx, int *move_x, int *move_y)
{
	if (mlx->plyr->u_d == 1)
	{
		*move_x = cos(mlx->plyr->angle) * PLAYER_SPEED;
		*move_y = sin(mlx->plyr->angle) * PLAYER_SPEED;
	}
	else
	{
		*move_x = -cos(mlx->plyr->angle) * PLAYER_SPEED;
		*move_y = -sin(mlx->plyr->angle) * PLAYER_SPEED;
	}
}

/*
	1 equals rotating right,
	-1, left.
*/
void	rotate_player(t_mlx *mlx)
{
	if (mlx->plyr->rot_dir == 1)
		mlx->plyr->angle = normalize(mlx->plyr->angle + ROTATION_SPEED);
	else
		mlx->plyr->angle = normalize(mlx->plyr->angle - ROTATION_SPEED);
}

void	move_player(t_mlx *mlx, int move_x, int move_y)
{
	int	map_x;
	int	map_y;
	int	new_plyr_x;
	int	new_plyr_y;

	new_plyr_x = roundf(mlx->plyr->plyr_x + move_x);
	new_plyr_y = roundf(mlx->plyr->plyr_y + move_y);
	map_x = (new_plyr_x / TILE_SIZE);
	map_y = (new_plyr_y / TILE_SIZE);
	if (mlx->map->map[map_y][map_x] != '1'
		&& mlx->map->map[map_y][(int)floor(mlx->plyr->plyr_x / TILE_SIZE)] != '1'
		&& mlx->map->map[(int)floor(mlx->plyr->plyr_y / TILE_SIZE)][map_x] != '1')
	{
		mlx->plyr->plyr_x = new_plyr_x;
		mlx->plyr->plyr_y = new_plyr_y;
	}
}

void	hook_player_mvmt(t_mlx *mlx)
{
	int	move_x;
	int	move_y;

	move_x = 0;
	move_y = 0;
	if (mlx->plyr->l_r)
		move_left_right(mlx, &move_x, &move_y);
	if (mlx->plyr->u_d)
		move_up_down(mlx, &move_x, &move_y);
	if (mlx->plyr->rot_dir)
		rotate_player(mlx);
	move_player(mlx, move_x, move_y);
}

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

// void	update_player_mvmt(t_mlx *mlx, int move_x, int move_y)
// {

// }
