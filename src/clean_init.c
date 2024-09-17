/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camunozg <camunozg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:28:46 by juramos           #+#    #+#             */
/*   Updated: 2024/09/17 10:50:16 by camunozg         ###   ########.fr       */
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
	plyr->u_d = 0;
	plyr->l_r = 0;
	plyr->plyr_x = 0;
	plyr->plyr_y = 0;
	plyr->fov_rd = 0;
	plyr->angle = 0;
}

void	init_empty_mlx(t_mlx *mlx)
{
	mlx->mlx = NULL;
	mlx->img = NULL;
	mlx->win = NULL;
	mlx->map = NULL;
	mlx->ray = NULL;
	mlx->plyr = NULL;
}

 int	init_empty_img(t_mlx *mlx)
{
	mlx->img = ft_calloc(1, sizeof(t_img));
	if (!mlx->img)
		return (1);
	mlx->img->img = NULL;
	mlx->img->addr = NULL;
	mlx->img->bits_per_pixel = 0;
	mlx->img->size_line = 0;
	mlx->img->endian = 0;
	return (0);
}

int init_empty_text(t_mlx *mlx)
{
	mlx->text->no_text = NULL;
	mlx->text->so_text = NULL;
	mlx->text->ea_text = NULL;
	mlx->text->we_text = NULL;
}

int	init_empty_ray(t_mlx *mlx)
{
	mlx->ray = ft_calloc(1, sizeof(t_ray));
	if (!mlx->ray)
		return (1);
	mlx->ray->distance = 0;
	mlx->ray->is_horizontal = 0;
	mlx->ray->ray_ngl = 0;
	return (0);
}