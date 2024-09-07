/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juramos <juramos@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:58:31 by juramos           #+#    #+#             */
/*   Updated: 2024/09/07 11:14:41 by juramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(void)
{
	char		**map2d;
	t_player	*plyr;

	map2d = ft_calloc(10, sizeof(char *));
	if (!map2d)
		return (1);
	map2d[0] = strdup("1111111111111111111111111");
	map2d[1] = strdup("1000000000000000000100001");
	map2d[2] = strdup("1001000000000S00000000001");
	map2d[3] = strdup("1001000000000000001000001");
	map2d[4] = strdup("1001000000000000001000001");
	map2d[5] = strdup("1001000000100000001000001");
	map2d[6] = strdup("1001000000000000001000001");
	map2d[7] = strdup("1001000000001000001000001");
	map2d[8] = strdup("1111111111111111111111111");
	map2d[9] = NULL;
	plyr = init_player(map2d);
	if (!plyr)
		return (1);
	display_player(plyr);
	free(plyr);
	int i = -1;
	while (++i < 9)
		free(map2d[i]);
	free(map2d);
	return (0);
}

