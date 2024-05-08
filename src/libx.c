/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libx.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwinder <rwinder@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:20:00 by rwinder           #+#    #+#             */
/*   Updated: 2023/09/04 16:20:00 by rwinder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	render(t_data *data)
{
	int	width;
	int	height;

	height = 384;
	width = 896;
	data->win_ptr = mlx_new_window(data->mlx_ptr, width, height, "so_long");
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask, &ft_quit, data);
	render_map(data);
	mlx_loop(data->mlx_ptr);
	return (0);
}

int	render_map(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->map->lines)
	{
		x = -1;
		while (data->map->layout[y][++x])
		{
			if (data->map->layout[y][x] == '1')
			{
				render_wall_corner(data, y, x);
				render_wall_border(data, y, x);
			}
			else
				render_tile(data, y, x);
		}
	}
	return (0);
}

void	render_wall_corner(t_data *data, int y, int x)
{
	if (y == 0 && x == 0)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->tiles[0], x * SIZE, y * SIZE);
	if (y == data->map->lines - 1 && x == 0)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->tiles[6], x * SIZE, y * SIZE);
	if (y == 0 && x == data->map->len - 1)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->tiles[1], x * SIZE, y * SIZE);
	if (y == data->map->lines - 1 && x == data->map->len - 1)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->tiles[7], x * SIZE, y * SIZE);
	if (y > 0 && y < data->map->lines - 1 && x > 0 && x < data->map->len - 1)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->tiles[4], x * SIZE, y * SIZE);
}

void	render_wall_border(t_data *data, int y, int x)
{
	if (y == 0 && x > 0 && x < data->map->len - 1)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->tiles[2], x * SIZE, y * SIZE);
	if (y == data->map->lines - 1 && x > 0 && x < data->map->len - 1)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->tiles[8], x * SIZE, y * SIZE);
	if (y > 0 && y < data->map->lines - 1 && x == 0)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->tiles[5], x * SIZE, y * SIZE);
	if (y > 0 && y < data->map->lines - 1 && x == data->map->len - 1)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->tiles[3], x * SIZE, y * SIZE);
}

void	render_tile(t_data *data, int y, int x)
{
	if (data->map->layout[y][x] == '0')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->tiles[10], x * SIZE, y * SIZE);
	if (data->map->layout[y][x] == 'C')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->tiles[12], x * SIZE, y * SIZE);
	if (data->map->layout[y][x] == 'P')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->tiles[9], x * SIZE, y * SIZE);
	if (data->map->layout[y][x] == 'E')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->tiles[11], x * SIZE, y * SIZE);
}
