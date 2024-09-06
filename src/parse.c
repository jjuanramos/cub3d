/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camunozg <camunozg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:28:43 by camunozg          #+#    #+#             */
/*   Updated: 2024/09/06 10:42:08 by camunozg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

typedef struct	s_map {
	char	**map;
	char 	*no_text;
	char 	*so_text;
	char 	*we_text;
	char	*ea_text;
	int		*floor_color;
	int		*ceiling_color;
	int		width;
	int		height;	
}				t_map;

int check_file_extension(char *file)
{
	size_t	i;

	i = ft_strlen(file);
	if (ft_strncmp((file + i - 4), ".cub"), 4)
		return (1);
	else 
		return (0);
}

char **get_file_contents(int fd) 
{
	
}

t_map *fill_map_info(char **read)
{
	t_map	*ret;
	
	ret = ft_calloc(sizeof(t_map), 1);
	ret->no_text = get_text(read, "NO ");
	ret->so_text = get_text(read, "SO ");
	ret->we_text = get_text(read, "WE ");
	ret->ea_text = get_text(read, "EA ");
	ret->floor_color = get_color(read, "F");
	ret->ceiling_color = get_color(read, "C");
	if (!ret->floor_color || !ret->ceiling_color)
		error("Colors are incorrect");
	else if (!ret->no_text || !ret->so_text || !ret->ea_text || !ret->we_text);
		error("Texture paths are incorrect");
	return (ret);
}

void parse_map(char *file, t_map *map) 
{
	int		fd;
	char	**read;

	fd = open(file, O_RDONLY);
	if (fd < 0 || check_file_extension(file))
		error("Issue with the file");
	read = get_file_contents(fd);
	if () // read esta vacio
		error("Empty map");
	map = fill_map_info(read);
	
}

int main(int argc, char *argv[])
{
	t_map	*map;
	
	if (argc != 2)
		error("There must be two arguments"); // Crear ft error
	parse_map(argv[1], map);
}