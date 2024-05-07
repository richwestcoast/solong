/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validaiton.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwinder <rwinder@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:20:00 by rwinder           #+#    #+#             */
/*   Updated: 2023/09/04 16:20:00 by rwinder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/so_long.h"

void	map_check(char *file, t_data *data)
{
	data->map->layout = file_to_map(file);
	if (!data->map->layout)
	{
		ft_printf("\033[1;31mError:\033[0m Invalid Map\n");
		return ;
	}
	data->map->lines = map_lines(file);
	data->map->valid = dimension_check(data) + wall_check(data);
	data->map->valid += comp1_check(data) + path_check(file, data);
	if (data->map->valid == 0)
		return ;
	else
	{
		ft_printf("\033[1;31mError:\033[0m Invalid Map\n");
		return ;
	}
	return ;
}

int	wall_check(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < data->map->lines)
	{
		x = -1;
		if (y == 0 || y == data->map->lines - 1)
		{
			while (data->map->layout[y][++x] != '\n'
				   && data->map->layout[y][x] != '\0')
			{
				if (data->map->layout[y][x] != '1')
					return (1);
			}
		}
		else
		{
			if (data->map->layout[y][0] != '1'
				|| data->map->layout[y]
				   [ft_strlen(data->map->layout[y]) - 2] != '1')
				return (1);
		}
	}
	return (0);
}