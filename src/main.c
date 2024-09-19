/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:58:31 by juramos           #+#    #+#             */
/*   Updated: 2024/09/19 13:22:35 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// void	debug_main(t_mlx *mlx)
// {
// 	int y = 0;

// 	display_player(mlx->plyr);
// 	printf("textures: %s %s %s %s\n",
// 		mlx->map->no_path, mlx->map->so_path,
// 		mlx->map->we_path, mlx->map->ea_path
// 		// mlx->map->ceiling_color[0], mlx->map->ceiling_color[1],
// 		// mlx->map->ceiling_color[2], mlx->map->floor_color[0],
// 		// mlx->map->floor_color[1], mlx.map->floor_color[2]
// 		);
// 	while (mlx->map->map[y])
// 	{
// 		printf("%s", mlx->map->map[y]);
// 		y++;
// 	}
// }
void	init_mlx(t_mlx *mlx, char **argv)
{
	init_empty_mlx(mlx);
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		ft_error("Could not initiate mlx", mlx);
	parse_map(argv[1], mlx);
	if (init_player(mlx))
		ft_error("Issue initiating player\n", mlx);
	if (init_empty_img(&(mlx->img)))
		ft_error("Issue initiating image\n", mlx);
	if (init_empty_ray(mlx))
		ft_error("Issue initiating ray\n", mlx);
	if (init_textures(mlx))
		ft_error("Issue initating textures\n", mlx);
}

int	main(int argc, char **argv)
{
	t_mlx		mlx;

	if (argc != 2)
		ft_error("There must be two arguments.", NULL);
	init_mlx(&mlx, argv);
	start_game(&mlx);
	return (0);
}

