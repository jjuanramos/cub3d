/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:52:36 by juramos           #+#    #+#             */
/*   Updated: 2024/09/19 12:47:15 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		hook_player_mvmt(t_mlx *mlx);
static void	move_left_right(t_mlx *mlx, int *move_x, int *move_y);
static void	move_up_down(t_mlx *mlx, int *move_x, int *move_y);
static void	rotate_player(t_mlx *mlx);
static void	move_player(t_mlx *mlx, int move_x, int move_y);

/*
	1 equals moving to the right,
	-1, to the left.
*/
static void	move_left_right(t_mlx *mlx, int *move_x, int *move_y)
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
static void	move_up_down(t_mlx *mlx, int *move_x, int *move_y)
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
static void	rotate_player(t_mlx *mlx)
{
	if (mlx->plyr->rot_dir == 1)
		mlx->plyr->angle = normalize(mlx->plyr->angle + ROTATION_SPEED);
	else
		mlx->plyr->angle = normalize(mlx->plyr->angle - ROTATION_SPEED);
}

static void	move_player(t_mlx *mlx, int move_x, int move_y)
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
		&& mlx->map->map[map_y][(int)floor \
		(mlx->plyr->plyr_x / TILE_SIZE)] != '1'
		&& mlx->map->map[(int)floor \
		(mlx->plyr->plyr_y / TILE_SIZE)][map_x] != '1')
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
