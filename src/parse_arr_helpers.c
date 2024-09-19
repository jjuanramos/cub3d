/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arr_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:51:51 by juramos           #+#    #+#             */
/*   Updated: 2024/09/19 13:52:35 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_arr(char **arr);
void	ft_arrdup(char **dst, char **src);
char	**append_str(char **map, char *buf);
int		ft_arrlen(char **arr);

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

char	**append_str(char **map, char *buf)
{
	char	**new_map;
	int		line_nbr;

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
	return (new_map);
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
