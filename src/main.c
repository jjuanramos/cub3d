/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:58:31 by juramos           #+#    #+#             */
/*   Updated: 2024/09/12 13:27:34 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	game_loop(void *ml)
{
	t_mlx	*mlx;

	mlx = ml;
	// mlx_destroy_image(mlx->mlx_p, mlx->img);
	mlx_clear_window(mlx->mlx_p, mlx->win);
	mlx->img = mlx_new_image(mlx->mlx_p, SCREENWIDTH, SCREENHEIGHT);
	// hook_player(mlx);
	cast_rays(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx		mlx;

	if (argc != 2)
		ft_error("There must be two arguments\n", &mlx);
	parse_map(argv[1], &mlx);
	if (init_player(&mlx))
		ft_error("Issue initiating player\n", &mlx);
	display_player(mlx.plyr);
	printf("textures: %s %s %s %s\n",
		mlx.map->no_text, mlx.map->so_text, mlx.map->we_text, mlx.map->ea_text
		// mlx.map->ceiling_color[0], mlx.map->ceiling_color[1],
		// mlx.map->ceiling_color[2], mlx.map->floor_color[0],
		// mlx.map->floor_color[1], mlx.map->floor_color[2]
		);
	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		ft_error("Could not initiate mlx", &mlx);
	mlx.win = mlx_new_window(mlx.mlx, SCREENWIDTH, SCREENHEIGHT, "Cub3D");
	mlx_loop_hook(mlx.mlx_p, &game_loop, NULL);
	// mlx_key_hook(mlx.win, &key_hook, NULL);
	//start_game(&mlx);
	mlx_loop(mlx.mlx);
	free_mlx(&mlx);
	return (0);
}

