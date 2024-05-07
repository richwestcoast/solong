/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwinder <rwinder@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:20:00 by rwinder           #+#    #+#             */
/*   Updated: 2023/09/04 16:20:00 by rwinder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (data);
	data->tiles = malloc(13 * sizeof(void *));
	if (!data->tiles)
	{
		free_game(data);
		return (data);
	}
	data->map = malloc(sizeof(t_map));
	if (!data->map)
	{
		free_game(data);
		return (data);
	}
	data->tile.y = SIZE;
	data->tile.x = SIZE;
	init_null(data);
	return (data);
}

void	init_img1(t_data *data)
{
	data->tiles[0] = mlx_xpm_file_to_image(data->mlx_ptr,
										   "./textures/wall.xpm", &data->tile.x, &data->tile.y);
	data->tiles[1] = mlx_xpm_file_to_image(data->mlx_ptr,
										   "./textures/wall.xpm", &data->tile.x, &data->tile.y);
	data->tiles[2] = mlx_xpm_file_to_image(data->mlx_ptr,
										   "./textures/wall.xpm", &data->tile.x, &data->tile.y);
	data->tiles[3] = mlx_xpm_file_to_image(data->mlx_ptr,
										   "./textures/wall.xpm", &data->tile.x, &data->tile.y);
	data->tiles[4] = mlx_xpm_file_to_image(data->mlx_ptr,
										   "./textures/wall.xpm", &data->tile.x, &data->tile.y);
	data->tiles[5] = mlx_xpm_file_to_image(data->mlx_ptr,
										   "./textures/wall.xpm", &data->tile.x, &data->tile.y);
	data->tiles[6] = mlx_xpm_file_to_image(data->mlx_ptr,
										   "./textures/wall.xpm", &data->tile.x, &data->tile.y);
	data->tiles[7] = mlx_xpm_file_to_image(data->mlx_ptr,
										   "./textures/wall.xpm", &data->tile.x, &data->tile.y);
	data->tiles[8] = mlx_xpm_file_to_image(data->mlx_ptr,
										   "./textures/wall.xpm", &data->tile.x, &data->tile.y);
}

void	init_img2(t_data *data)
{
	data->tiles[9] = mlx_xpm_file_to_image(data->mlx_ptr,
										   "./textures/clippy.xpm", &data->tile.x, &data->tile.y);
	data->tiles[10] = mlx_xpm_file_to_image(data->mlx_ptr,
											"./textures/floor.xpm", &data->tile.x, &data->tile.y);
	data->tiles[11] = mlx_xpm_file_to_image(data->mlx_ptr,
											"./textures/exit.xpm", &data->tile.x, &data->tile.y);
	data->tiles[12] = mlx_xpm_file_to_image(data->mlx_ptr,
											"./textures/document.xpm", &data->tile.x, &data->tile.y);
}

t_data	*init(void)
{
	t_data	*data;

	data = init_data();
	if (!data)
	{
		free_game(data);
		return (NULL);
	}
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		free_game(data);
		return (NULL);
	}
	init_img1(data);
	init_img2(data);
	return (data);
}

int	free_game(t_data *data)
{
	if (!data)
		return (0);
	if (data->tiles)
		free_tiles(data);
	if (data->img.mlx_img)
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
	if (data->map)
		free_map(data->map);
	free(data->mlx_ptr);
	free(data);
	return (0);
}

void	free_tiles(t_data *data)
{
	int	i;

	i = 0;
	while (i < 13)
		mlx_destroy_image(data->mlx_ptr, data->tiles[i++]);
	free(data->tiles);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (!map->layout)
	{
		free(map);
		return ;
	}
	i = 0;
	while (i < map->lines)
		free(map->layout[i++]);
	free(map->layout);
	free(map);
}