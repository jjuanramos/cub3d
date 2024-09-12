/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:28:46 by juramos           #+#    #+#             */
/*   Updated: 2024/09/12 16:23:56 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_empty_player(t_player *plyr)
{
	plyr->pos_x = 0;
	plyr->pos_y = 0;
	plyr->dir_x = 0;
	plyr->dir_y = 0;
	plyr->rot_dir = 0;
	plyr->plyr_x = 0;
	plyr->plyr_y = 0;
	plyr->fov_rd = 0;
	plyr->angle = 0;
}

static void	init_empty_mlx(t_mlx *mlx)
{
	mlx->mlx = NULL;
	mlx->img = NULL;
	mlx->win = NULL;
	mlx->map = NULL;
	mlx->ray = NULL;
	mlx->plyr = NULL;
}

static void	init_empty_img(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bits_per_pixel = 0;
	img->size_line = 0;
	img->endian = 0;
}

void	init_mlx(t_mlx *mlx, char **argv)
{
	init_empty_mlx(mlx);
	parse_map(argv[1], mlx);
	mlx->plyr = ft_calloc(1, sizeof(t_player));
	if (!mlx->plyr)
		ft_error("Issue initiating player\n", mlx);
	if (init_player(mlx))
		ft_error("Issue initiating player\n", mlx);
	mlx->img = ft_calloc(1, sizeof(t_img));
	if (!mlx->img)
		ft_error("Issue initiating image\n", mlx);
	mlx->ray = ft_calloc(1, sizeof(t_ray));
	if (!mlx->ray)
		ft_error("Issue initiating ray\n", mlx);
	init_empty_img(mlx->img);
}

