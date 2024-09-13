/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:58:31 by juramos           #+#    #+#             */
/*   Updated: 2024/09/13 11:29:03 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	debug_main(t_mlx *mlx)
{
	int y = 0;

	display_player(mlx->plyr);
	printf("textures: %s %s %s %s\n",
		mlx->map->no_text, mlx->map->so_text,
		mlx->map->we_text, mlx->map->ea_text
		// mlx->map->ceiling_color[0], mlx->map->ceiling_color[1],
		// mlx->map->ceiling_color[2], mlx->map->floor_color[0],
		// mlx->map->floor_color[1], mlx.map->floor_color[2]
		);
	while (mlx->map->map[y])
	{
		printf("%s", mlx->map->map[y]);
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_mlx		mlx;

	if (argc != 2)
		ft_error("There must be two arguments.", NULL);
	init_mlx(&mlx, argv);
	debug_main(&mlx);
	start_game(&mlx);
	return (0);
}

