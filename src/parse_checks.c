/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:41:50 by juramos           #+#    #+#             */
/*   Updated: 2024/09/20 13:35:48 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			check_file_extension(char *file);
int			check_row(char *line);
void		check_zeros_out_of_bounds(char **map, t_mlx *mlx);
int			check_space_edges(char **map, int row, int i);
static int	check_space_edges_aux(char **map, int row, int adjust_row, int i);

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
					ft_error("Map is not enclosed.", mlx);
			}
			j++;
		}
		i++;
	}
}

static int	check_space_edges_aux(char **map, int row, int adjust_row, int i)
{
	int	row_col[2];

	row_col[0] = row;
	row_col[1] = i;
	if (find_horizontal_zeros(map[row + adjust_row], row_col, -1, map))
		return (1);
	else if (find_horizontal_zeros(map[row + adjust_row], row_col, 1, map))
		return (1);
	return (0);
}

int	check_space_edges(char **map, int row, int i)
{
	int	adjust_row;
	int	inc;

	adjust_row = 1;
	if (row != 0)
		adjust_row = -1;
	inc = adjust_row;
	while (map[row][++i])
	{
		if (map[row][i] == ' ')
		{
			while (map[row + adjust_row] && map[row + adjust_row][i]
				&& map[row + adjust_row][i] == ' ')
			{
				if (check_space_edges_aux(map, row, adjust_row, i))
					return (1);
				adjust_row += inc;
			}
			if (map[row + adjust_row][i] && map[row + adjust_row][i] != '1')
				return (1);
		}
		else if (map[row][i] == '0')
			return (1);
	}
	return (0);
}
