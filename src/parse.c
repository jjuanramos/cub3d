/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:28:43 by camunozg          #+#    #+#             */
/*   Updated: 2024/09/10 12:31:34 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int check_file_extension(char *file)
{
	size_t	i;

	i = ft_strlen(file);
	if (ft_strncmp((file + i - 4), ".cub", 4))
		return (1);
	else 
		return (0);
}
void	free_arr(char **arr)
{
	int	pos;

	if (!arr)
		return ;
	pos = -1;
	while (arr[++pos])
		free(arr[pos]);
	free(arr);
}

void	ft_arrdup(char **dst, char **src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		i++;
	}
	dst[i] = NULL;
}

int	get_line_nbr(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

char **append_str(char **map, char *buf) 
{
	char **new_map;
	int	line_nbr;

	line_nbr = get_line_nbr(map);
	new_map = ft_calloc(sizeof(char *), line_nbr + 2);
	if (!(*map)) 
	{
		new_map[0] = ft_strdup(buf);
		new_map[1] = NULL;
	}
	else
	{
		ft_arrdup(new_map, map);
		new_map[line_nbr] = ft_strdup(buf);
		new_map[line_nbr + 1] = NULL;
	}
	free_arr(map);
	return(new_map);
}

char **get_file_contents(int fd) // rellenar una matriz con cada linea del archivo. crear una funcion que sea append 
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
	return (map);
}

// char *clean_spaces(char *line) 
// {
// 	char *hold;
// 	char *clean_line;
	
// 	hold = line;
// 	while (*hold && *hold != ' ')
// 		hold++;
// 	while (*hold && *hold == ' ')
// 		hold++;
// 	clean_line = ft_strdup(line);
// 	free(line); // necesario?
// 	return (clean_line);
// }

char *get_text(char **read, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (read[i]) 
	{
		j = 0;
		while (read[i][j] && read[i][j] == ' ')
			j++;
		if (ft_strncmp(read[i], to_find, ft_strlen(to_find)) == 0)
			return (read[i]); // Aqui falta hacer algun tipo de comprobacion de que el path exista ? Quiza solo de que el texto este correcto y comprobar si existe se puede hacer despues
		i++;
	}
	return (NULL);
}

int *get_rgb_int_arr(char *line) //eg 255,1,99
{
	int 	*rgb;
	char	*hold;
	int		i;
	int		j;

	i = 0;
	j = 0;
	rgb = ft_calloc(sizeof(int), 3);
	while (j <= 3) 
	{
		while (line[i] && (line[i] >= 48 && line[i] <= 57))
			i++;
		hold = ft_calloc(sizeof(char), i + 1);
		ft_strlcpy(hold, line, i);
		rgb[j] = ft_atoi(hold);
		if (rgb[j] < 0 || rgb[j] > 255)
			return (free(hold), NULL);
		free(hold);
		line += i;
		i = 0;
		j++;
	}
	return (rgb);
}

int *get_color(char **read, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (read[i]) 
	{
		j = 0;
		while (read[i][j] && read[i][j] == ' ')
			j++;
		if (ft_strncmp(read[i], to_find, ft_strlen(to_find)) == 0)
			return (get_rgb_int_arr(read[i])); // Lo mismo, falta comprobacion creo
		i++;
	}
	return (NULL);
}

int	ft_arrlen(char **arr) 
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return(i);
}

bool is_empty(char *line) 
{
	int i;
	int	not_space;

	i = 0;
	not_space = 0;
	while (line[i] && line[i] != '\n') 
	{
		if (line[i] != ' ') not_space++;
		i++;
	}
	return (not_space == 0);
}

char **get_map(char **read) // contar que tex_lines llegue a 6 
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
	while (*read && is_empty(*read))
	{
		read++;
		blank_lines++;
	}
	clean_map = ft_calloc(sizeof(char *), (lines_in_file - tex_lines - blank_lines + 1));
	if (!clean_map)
		return (NULL);
	ft_arrdup(clean_map, read);
	return (clean_map);
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
	ret->map = get_map(read); // cargar el mapa y solo el mapa
	if (!ret->floor_color || !ret->ceiling_color)
		return (printf("Colors are incorrect\n"), exit(1), NULL);
	if (!ret->no_text || !ret->so_text || !ret->ea_text || !ret->we_text)
		return (printf("Texture paths are incorrect\n"), exit(1), NULL);
	free(read);
	return (ret);
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

int check_spaces(char c) 
{
	(void)c;
	return (0);
}

int check_row(char *line)
{
	char tmp;
	
	while (*line && *line == ' ')
		line++;
	if (*line && *line != '1')
		return (1);
	while (*line && *line != '\n')
	{
		if (*line != ' ')
			tmp = *line;
		line++;
	}
	if (tmp != '1')
		return(1);
	return(0);
}

int get_width(char **map)
{
	int		width;
	int		spaces;
	bool	found_space;
	int		i;
	int		j;

	found_space = false;
	i = 0;
	width = 0;
	while (map[i]) 
	{
		j = 0;
		while (map[i][j] && map[i][j] == ' ')
				j++;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (map[i][j] == ' ')
			{
				found_space = true;
				spaces++;
			}
			if (found_space == true && map[i][j] != ' ')
				spaces = 0;
			j++;
		}
		if (width < j - spaces)
			width = j - spaces;
		i++;
	}
	return (width);
}

void check_valid_map(t_map *map) 
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
			if ((i == 0 || i == map->height || check_spaces(map->map[i][j])) && map->map[i][j] != '1')
				(printf("Map is not enclosed: %c, (%d %d)\n", map->map[i][j], i, j), exit(1));
			else if (check_row(map->map[i]))
				(printf("Map is not enclosed 2\n"), exit(1));
			else if (!is_valid_char(map->map[i][j]))
				(printf("Wrong Character: %c\n", map->map[i][j]), exit(1));
			j++;
		}
		i++;
	}
	map->width = get_width(map->map);
}

void parse_map(char *file, t_mlx *mlx)
{
	int		fd;
	char	**read;

	fd = open(file, O_RDONLY);
	if (fd < 0 || check_file_extension(file))
		(printf("Issue with the file"), exit(1));
	read = get_file_contents(fd);
	printf("successful read\n");
	if (!read) // read esta vacio
		(printf("Empty map"), exit(1));
	mlx->map = fill_map_info(read);
	check_valid_map(mlx->map); // aqui hacer las comprobaciones de si el mapa es valido
}

// // Los calloc deberian ser malloc? por el hecho de que si fallase alguno deberiamos liberar toda la memoria que alocamos

// int main(int argc, char *argv[]) 
// {
// 	t_map	*map;
	
// 	if (argc != 2)
// 		ft_error("There must be two arguments"); // Crear ft ft_error
// 	parse_map(argv[1], map);
// }