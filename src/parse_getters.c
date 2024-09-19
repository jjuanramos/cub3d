/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_getters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:49:06 by juramos           #+#    #+#             */
/*   Updated: 2024/09/19 13:50:50 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		get_line_nbr(char **map);
char	*get_text(char **read, char *to_find);
int		*get_rgb_int_arr(char *line);
int		*get_color_parse(char **read, char *to_find);
int		get_width(char **map);

int	get_line_nbr(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

char	*get_text(char **read, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (read[i])
	{
		j = 0;
		while (read[i][j] && read[i][j] == ' ')
			j++;
		if (ft_strncmp(read[i] + j, to_find, ft_strlen(to_find)) == 0)
			return (read[i] + j);
		i++;
	}
	return (NULL);
}

int	*get_rgb_int_arr(char *line)
{
	int		*rgb;
	char	*hold;
	int		i;
	int		j;

	j = -1;
	rgb = ft_calloc(sizeof(int), 3);
	if (!rgb)
		return (NULL);
	while (++j < 3)
	{
		i = 0;
		while (*line && !(*line >= 48 && *line <= 57))
			line++;
		while (line[i] && (line[i] >= 48 && line[i] <= 57))
			i++;
		hold = ft_calloc(sizeof(char), i + 1);
		ft_strlcpy(hold, line, i + 1);
		rgb[j] = ft_atoi(hold);
		if (rgb[j] < 0 || rgb[j] > 255 || is_empty(hold))
			return (free(rgb), free(hold), NULL);
		free(hold);
		line += i;
	}
	return (rgb);
}

int	*get_color_parse(char **read, char *to_find)
{
	int		i;
	int		j;

	i = 0;
	while (read[i])
	{
		j = 0;
		while (read[i][j] && read[i][j] == ' ')
			j++;
		if (ft_strncmp(read[i] + j, to_find, ft_strlen(to_find)) == 0
			&& is_valid_str_clr_cntnt(read[i] + j, to_find[0]))
			return (get_rgb_int_arr(read[i] + j));
		i++;
	}
	return (NULL);
}

int	get_width(char **map)
{
	int	max_row_len;
	int	current_row;
	int	current_row_len;

	max_row_len = 0;
	current_row = 0;
	while (map[current_row])
	{
		current_row_len = ft_strlen(map[current_row]);
		if (current_row_len > max_row_len)
			max_row_len = current_row_len;
		current_row++;
	}
	return (max_row_len);
}
