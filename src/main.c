/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camunozg <camunozg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:58:31 by juramos           #+#    #+#             */
/*   Updated: 2024/09/17 12:19:32 by camunozg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	debug_main(t_mlx *mlx)
{
	int y = 0;

	display_player(mlx->plyr);
	printf("textures: %s %s %s %s\n",
		mlx->map->no_path, mlx->map->so_path,
		mlx->map->we_path, mlx->map->ea_path
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
void	init_mlx(t_mlx *mlx, char **argv)
{
	init_empty_mlx(mlx);
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		ft_error("Could not initiate mlx", mlx);
	parse_map(argv[1], mlx);
	mlx->map->width = 9;
	mlx->map->height = 5;
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
	debug_main(&mlx);
	start_game(&mlx);
	return (0);
}

