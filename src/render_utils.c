/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:59:39 by juramos           #+#    #+#             */
/*   Updated: 2024/09/19 13:01:25 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			get_rgb(int *rgb);
void		set_image_pixel(t_img *img, int x, int y, int color);
t_texture	*get_texture(t_mlx *mlx, double norm_ngl);
double		get_x_offset(t_texture *text, t_mlx *mlx);

int	get_rgb(int *rgb)
{
	return (255 << 24 | rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void	set_image_pixel(t_img *img, int x, int y, int color)
{
	int	pixel;

	pixel = y * (img->size_line / 4) + x;
	img->addr[pixel] = color;
}

t_texture	*get_texture(t_mlx *mlx, double norm_ngl)
{
	if (mlx->ray->is_horizontal)
	{
		if (norm_ngl > 0 && norm_ngl < M_PI)
			return (mlx->no_text);
		else
			return (mlx->so_text);
	}
	else
	{
		if (norm_ngl > M_PI / 2 && norm_ngl < (3 * M_PI / 2))
			return (mlx->we_text);
		else
			return (mlx->ea_text);
	}
	return (NULL);
}

double	get_x_offset(t_texture *text, t_mlx *mlx)
{
	double	x_offset;

	if (mlx->ray->is_horizontal)
		x_offset = (int)fmodf(
				(mlx->ray->horiz_x * (text->width / TILE_SIZE)),
				text->width
				);
	else
		x_offset = (int)fmodf(
				(mlx->ray->vert_y * (text->width / TILE_SIZE)),
				text->width
				);
	return (x_offset);
}
