/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:53:32 by juramos           #+#    #+#             */
/*   Updated: 2024/09/19 13:54:02 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*trim_path(char *path, char *prefix);
void	replace_spaces_with_ones(t_map *map);

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
