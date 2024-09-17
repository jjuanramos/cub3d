/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camunozg <camunozg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:43:39 by camunozg          #+#    #+#             */
/*   Updated: 2024/09/17 10:50:55 by camunozg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_textures(t_mlx *mlx)
{
	mlx->text = ft_calloc(1, sizeof(t_textures));
	if (!mlx->text)
		return (1);
	init_empty_text(mlx);
	mlx->text->no_text = mlx_xpm
}