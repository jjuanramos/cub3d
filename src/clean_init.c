/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:28:46 by juramos           #+#    #+#             */
/*   Updated: 2024/09/19 12:43:31 by juramos          ###   ########.fr       */
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

int	init_empty_img(t_img **img)
{
	(*img) = ft_calloc(1, sizeof(t_img));
	if (!(*img))
		return (1);
	(*img)->img = NULL;
	(*img)->addr = NULL;
	(*img)->bpp = 0;
	(*img)->size_line = 0;
	(*img)->endian = 0;
	return (0);
}

int	init_empty_text(t_texture **text)
{
	*text = ft_calloc(1, sizeof(t_texture));
	if (!(*text))
		return (1);
	if (init_empty_img(&((*text)->text)))
		return (1);
	(*text)->height = 0;
	(*text)->width = 0;
	return (0);
}

int	init_empty_ray(t_mlx *mlx)
{
	mlx->ray = ft_calloc(1, sizeof(t_ray));
	if (!mlx->ray)
		return (1);
	mlx->ray->distance = 0;
	mlx->ray->is_horizontal = 0;
	mlx->ray->ray_ngl = 0;
	mlx->ray->horiz_x = 0;
	mlx->ray->horiz_y = 0;
	mlx->ray->vert_x = 0;
	mlx->ray->vert_y = 0;
	mlx->ray->index = 0;
	return (0);
}
