#include <stdio.h>
#include "../includes/so_long.h"

int main(void)
{
	t_data	*data;
	data = init();
	render(data);
	return (0);
}

int render(t_data *data)
{
	render_win(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask,
			 &ft_quit, data);
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

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		ft_printf("\033[1;33mYou give up this easily what a same... smh\033[1;33o\n");
//		ft_quit(data);
	}
	if (keysym == XK_Up || keysym == XK_w)
		move_up(data);
	if (keysym == XK_Down || keysym == XK_s)
		move_down(data);
	if (keysym == XK_Right || keysym == XK_d)
		move_right(data);
	if (keysym == XK_Left || keysym == XK_a)
		move_left(data);
	if (data->map->layout[data->map->player.y][data->map->player.x] == 'E')
	{
		ft_printf("\033[1;32mCongrats, you put clippy in the trash, good job!\033[0m\n");
		ft_quit(data);
	}
	return (0);
}

int	ft_quit(t_data *data)
{
	free_game(data);
	exit(0);
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

void	move_up(t_data *data)
{

}

void	move_down(t_data *data)
{

}

void	move_right(t_data *data)
{

}

void	move_left(t_data *data)
{

}

int render_win(t_data *data)
{
	int width = 896;
	int height = 384;
	data->win_ptr = mlx_new_window(data->mlx_ptr, width, height, "so_long");

	return (0);

}

t_data	*init(void)
{
	t_data	*data;

	data = init_data();
//	if (!data)
//	{
//		free_game(data);
//		return (NULL);
//	}
	data->mlx_ptr = mlx_init();
//	if (!data->mlx_ptr)
//	{
//		free_game(data);
//		return (NULL);
//	}
	init_img1(data);
	init_img2(data);
	return (data);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (data);
	data->tiles = malloc(13 * sizeof(void *));
//	if (!data->tiles)
//	{
//		free_game(data);
//		return (data);
//	}
	data->map = malloc(sizeof(t_map));
//	if (!data->map)
//	{
//		free_game(data);
//		return (data);
//	}
	data->tile.y = SIZE;
	data->tile.x = SIZE;
//	init_null(data);
	return (data);
}

void	init_img1(t_data *data)
{

}

void	init_img2(t_data *data)
{

}
