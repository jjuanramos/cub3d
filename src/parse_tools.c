/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camunozg <camunozg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:53:32 by juramos           #+#    #+#             */
/*   Updated: 2024/09/20 11:19:47 by camunozg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			find_horizontal_zeros(char *line, int *row_col, int inc, char **map); 
static int	find_vertical_zeros(char **map, int row, int col, int inc);
char		*trim_path(char *path, char *prefix);
void		replace_spaces_with_ones(t_map *map);

static int	find_vertical_zeros(char **map, int row, int col, int inc)
{
	while (map[row] && map[row][col] && map[row][col] == ' ')
		row += inc;
	if (map[row][col] && map[row][col] != '1'
		&& !is_pos(map[row][col]))
			return (1);
	return (0);
}

int	find_horizontal_zeros(char *line, int *row_col, int inc, char **map) 
{
	int	local_row;
	int	local_col;

	local_row = row_col[0];
	local_col = row_col[1];
	
	while (line[local_col] && line[local_col] == ' ')
	{
		if (find_vertical_zeros(map, local_col, local_row, 1)
			|| find_vertical_zeros(map, local_col, local_row, -1))
			return (1);
		local_col += inc;
	}
	if (line[local_col] && line[local_col] != '1' && !is_pos(line[local_col]))
		return (1);
	return (0);
}

char	*trim_path(char *path, char *prefix)
{
	char	*new_path;
	char	*helper;
	char	*ref;		

	if (!path)
		return (NULL);
	while (ft_isspace2(*path))
		path++;
	helper = ft_strtrim(path, "\n");
	ref = helper;
	while (*helper == *prefix)
	{
		helper++;
		prefix++;
	}
	while (ft_isspace2(*helper))
		helper++;
	new_path = ft_strtrim(helper, " ");
	return (free(ref), new_path);
}

void	replace_spaces_with_ones(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == ' ')
				map->map[i][j] = '1';
			j++;
		}
		i++;
	}
}
