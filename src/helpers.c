/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwinder <rwinder@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:20:00 by rwinder           #+#    #+#             */
/*   Updated: 2023/09/04 16:20:00 by rwinder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	map_lines(char *file)
{
	int		lines;
	int		fd;
	char	*gnl;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	lines = 0;
	gnl = get_next_line(fd);
	while (gnl && lines++ >= 0)
	{
		free(gnl);
		gnl = get_next_line(fd);
	}
	free(gnl);
	close(fd);
	return (lines);
}

int	ft_quit(t_data *data)
{
	free_game(data);
	exit(0);
}

void	fill(char **layout_cpy, t_data *data, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->map->len || y >= data->map->lines)
		return ;
	if (layout_cpy[y][x] == 'W' || layout_cpy[y][x] == '1'
		|| layout_cpy[y][x] == 'G')
		return ;
	if (layout_cpy[y][x] == 'C')
	{
		layout_cpy[y][x] = 'G';
		data->map->gathered++;
	}
	if (layout_cpy[y][x] == 'E')
	{
		layout_cpy[y][x] = 'W';
		return ;
	}
	else
		layout_cpy[y][x] = 'W';
	fill(layout_cpy, data, x - 1, y);
	fill(layout_cpy, data, x + 1, y);
	fill(layout_cpy, data, x, y - 1);
	fill(layout_cpy, data, x, y + 1);
}

int	strlen_solong(char	*str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str [i] != '\n')
		i++;
	return (i);
}

void	free_array(char **arr, int lines)
{
	int	i;

	i = 0;
	while (i <= lines)
		free(arr[i++]);
	free(arr);
}
