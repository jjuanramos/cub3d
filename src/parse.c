/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camunozg <camunozg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:28:43 by camunozg          #+#    #+#             */
/*   Updated: 2024/09/20 09:55:19 by camunozg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* parse */
void	check_valid_map(t_map *map, t_mlx *mlx);
void	parse_map(char *file, t_mlx *mlx);
t_map	*fill_map_info(t_mlx *mlx, char **read);
char	**get_file_contents(int fd);
char	**get_map(char **read);

char	**get_file_contents(int fd)
{
	char	**map;
	char	*buf;

	buf = get_next_line(fd);
	if (!buf)
		return (NULL);
	map = ft_calloc(sizeof(char *), 1);
	map[0] = NULL;
	while (buf)
	{
		map = append_str(map, buf);
		free(buf);
		buf = get_next_line(fd);
	}
	free(buf);
	return (map);
}

char	**get_map(char **read)
{
	char	**clean_map;
	int		lines_in_file;
	int		tex_lines;
	int		blank_lines;

	lines_in_file = ft_arrlen(read);
	tex_lines = 0;
	blank_lines = 0;
	while (*read && tex_lines != 6)
	{
		if (is_empty(*read))
			blank_lines++;
		else
			tex_lines++;
		read++;
	}
	while (*read && is_empty(*read) && read++)
		blank_lines++;
	clean_map = ft_calloc(sizeof(char *),
			(lines_in_file - tex_lines - blank_lines + 1));
	if (!clean_map)
		return (NULL);
	ft_arrdup(clean_map, read);
	return (clean_map);
}

t_map	*fill_map_info(t_mlx *mlx, char **read)
{
	t_map	*ret;

	ret = ft_calloc(sizeof(t_map), 1);
	ret->no_path = trim_path(get_text(read, "NO "), "NO");
	ret->so_path = trim_path(get_text(read, "SO "), "SO");
	ret->we_path = trim_path(get_text(read, "WE "), "WE");
	ret->ea_path = trim_path(get_text(read, "EA "), "EA");
	if (!ret->no_path || !ret->so_path || !ret->ea_path || !ret->we_path)
		ft_error("Texture paths are incorrect", mlx);
	ret->floor_color = get_color_parse(read, "F ");
	ret->ceiling_color = get_color_parse(read, "C ");
	if (!ret->floor_color || !ret->ceiling_color)
		ft_error("Colors are incorrect", mlx);
	ret->map = get_map(read);
	free_arr(read);
	return (ret);
}

void	check_valid_map(t_map *map, t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	map->height = get_line_nbr(map->map);
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j] && map->map[i][j] != '\n')
		{
			if ((i == 0 || i == map->height - 1)
				&& (map->map[i][j] != '1' && check_space_edges(map->map, i, -1)))
				ft_error("Map is not enclosed.", mlx);
			else if (!is_valid_char(map->map[i][j]))
				ft_error("Wrong Character.", mlx);
			else if (check_row(map->map[i]))
				ft_error("Issue reading map.", mlx);
			j++;
		}
		i++;
	}
	map->width = get_width(map->map);
}

void	parse_map(char *file, t_mlx *mlx)
{
	int		fd;
	char	**read;

	fd = open(file, O_RDONLY);
	if (fd < 0 || check_file_extension(file))
		(printf("Issue with the file"), exit(1));
	read = get_file_contents(fd);
	if (!read)
		(printf("Empty map"), exit(1));
	mlx->map = fill_map_info(mlx, read);
	check_valid_map(mlx->map, mlx);
	replace_spaces_with_ones(mlx->map);
	check_zeros_out_of_bounds(mlx->map->map, mlx); // segf
	check_map_is_together(mlx->map->map, mlx);
}
