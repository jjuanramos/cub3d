/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camunozg <camunozg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:43:39 by camunozg          #+#    #+#             */
/*   Updated: 2024/09/18 13:05:25 by camunozg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	new_text(t_mlx *mlx, t_texture *text, char *path)
{
	if (!(text->text->img = mlx_xpm_file_to_image(mlx->mlx, path,
		&(text->width), &(text->height))))
			return (1);
	if (!(text->text->addr = (int *)mlx_get_data_addr(text->text->img,
		&(text->text->bpp), &(text->text->size_line), &(text->text->endian))))
		return (1);
	return (0);
}

int	init_textures(t_mlx *mlx)
{
	if (init_empty_text(&(mlx->no_text))
			|| new_text(mlx, mlx->no_text, mlx->map->no_path))
		return (1);
	if (init_empty_text(&(mlx->so_text))
			|| new_text(mlx, mlx->so_text, mlx->map->so_path))
		return (1);
	if (init_empty_text(&(mlx->ea_text))
			|| new_text(mlx, mlx->ea_text, mlx->map->ea_path))
		return (1);
	if (init_empty_text(&(mlx->we_text))
			|| new_text(mlx, mlx->we_text, mlx->map->we_path))
		return (1);
	return (0);
}
