/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:41:50 by juramos           #+#    #+#             */
/*   Updated: 2024/09/19 13:55:12 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		check_file_extension(char *file);
int		check_row(char *line);
void	check_zeros_out_of_bounds(char **map, t_mlx *mlx);
void	check_map_is_together(char **map, t_mlx *mlx);

int	check_file_extension(char *file)
{
	size_t	i;

	i = ft_strlen(file);
	if (ft_strncmp((file + i - 4), ".cub", 4))
		return (1);
	else
		return (0);
}

int	check_row(char *line)
{
	char	tmp;

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
		return (1);
	return (0);
}

void	check_zeros_out_of_bounds(char **map, t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' && map[i - 1]
			&& map[i + 1])
			{
				if (!map[i - 1][j] || !map[i + 1][j])
					ft_error("Map not enclosed.", mlx);
			}
			j++;
		}
		i++;
	}
}

void	check_map_is_together(char **map, t_mlx *mlx)
{
	int	i;
	int	last_empty;

	i = 0;
	last_empty = 0;
	while (map[i])
	{
		if (is_empty(map[i]))
			last_empty = 1;
		if (!is_empty(map[i]) && last_empty)
			ft_error("Map is not together.", mlx);
		i++;
	}
}
