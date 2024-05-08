/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwinder <rwinder@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:20:00 by rwinder           #+#    #+#             */
/*   Updated: 2023/09/04 16:20:00 by rwinder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/so_long.h"

int	main(int ac, char **av)
{
	t_data	*data;

	(void) ac;
	data = init();
	map_check(av[1], data);
	render(data);
	return (0);
}

char	**file_to_map(char *file)
{
	char	**map;
	int		lines;
	int		fd;
	int		i;

	lines = map_lines(file);
	map = ft_calloc(lines + 1, sizeof(char *));
	if (!map)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	i = -1;
	while (++i < lines)
	{
		map[i] = get_next_line(fd);
		if (!map[i] || map[i][0] == '\r')
		{
			free_array(map, lines);
			close(fd);
			return (NULL);
		}
	}
	close(fd);
	return (map);
}
