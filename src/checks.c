/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwinder <rwinder@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:20:00 by rwinder           #+#    #+#             */
/*   Updated: 2023/09/04 16:20:00 by rwinder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	dimension_check(t_data *data)
{
	int	len;
	int	x;

	data->map->len = strlen_solong(data->map->layout[0]);
	len = 0;
	x = 1;
	while (x < data->map->lines)
	{
		len = strlen_solong(data->map->layout[x]);
		if (len == data->map->len)
			x++;
		else
			return (1);
	}
	return (0);
}

int	comp2_check(t_data *data, int x, int y)
{
	int	start_exit;

	start_exit = 0;
	if (data->map->layout[y][x] == 'C')
		data->map->collect++;
	if (data->map->layout[y][x] == 'P')
	{
		data->map->player.x = x;
		data->map->player.y = y;
		start_exit++;
	}
	if (data->map->layout[y][x] == 'E')
	{
		data->map->exit.x = x;
		data->map->exit.y = y;
		start_exit++;
	}
	return (start_exit);
}

int	comp3_check(t_data *data, int start_exit)
{
	int		i;
	int		x;
	int		y;
	char	*str;

	if (start_exit != 2 || data->map->collect < 1)
		return (1);
	str = "01CEP";
	y = -1;
	while (++y < data->map->lines)
	{
		x = -1;
		while (data->map->layout[y][++x] != '\n'
			&& data->map->layout[y][x] != '\0')
		{
			i = -1;
			while (str[++i])
				if (data->map->layout[y][x] == str[i])
					break ;
			if (i == 5)
				return (1);
		}
	}
	return (0);
}

int	comp1_check(t_data *data)
{
	int	start_exit;
	int	x;
	int	y;

	data->map->collect = 0;
	start_exit = 0;
	y = -1;
	while (++y < data->map->lines)
	{
		x = -1;
		while (data->map->layout[y][++x])
			start_exit += comp2_check(data, x, y);
	}
	return (comp3_check(data, start_exit));
}

int	path_check(char *file, t_data *data)
{
	char	**layout_cpy;
	int		lines;

	layout_cpy = file_to_map(file);
	if (!layout_cpy)
		return (1);
	lines = map_lines(file);
	fill(layout_cpy, data, data->map->player.x, data->map->player.y);
	if (!data->map->exit.y || !data->map->exit.x)
	{
		free_array(layout_cpy, lines);
		return (1);
	}
	if (layout_cpy[data->map->exit.y][data->map->exit.x] != 'W')
	{
		free_array(layout_cpy, lines);
		return (1);
	}
	if (data->map->collect != data->map->gathered)
	{
		free_array(layout_cpy, lines);
		return (1);
	}
	free_array(layout_cpy, lines);
	return (0);
}
