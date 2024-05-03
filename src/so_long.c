#include <stdio.h>
#include "../includes/so_long.h"

int main(int ac, char **av)
{
	t_data	*data;
	data = init();
	map_check(av[1], data);
	render(data);
	return (0);
}

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

void	free_array(char **arr, int lines)
{
	int	i;

	i = 0;
	while (i <= lines)
		free(arr[i++]);
	free(arr);
}

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

void print_coordinates(t_data *data){
	ft_printf("Type of square: %c\n", data->map->layout[data->map->player.y][data->map->player.x - 1]);
	ft_printf("Coordinates: Y: %i - ", data->map->player.y);
	ft_printf("X: %i \n", data->map->player.x);
	ft_printf("Collectibles: %i left\n", data->map->gathered);
}

void	move_up(t_data *data)
{
	//print_coordinates(data);
	if (data->map->layout[data->map->player.y - 1][data->map->player.x] == 'C')
	{
		data->map->gathered--;
		data->map->layout[data->map->player.y - 1][data->map->player.x] = 'C';
	}
	if (data->map->layout[data->map->player.y - 1][data->map->player.x] == '1'
		|| (data->map->layout[data->map->player.y - 1]
			[data->map->player.x] == 'E' && data->map->gathered >= 1)) {
		ft_printf("%i", data->map->gathered);
		return;
	}else
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->tiles[10],
								data->map->player.x * SIZE, data->map->player.y * SIZE);
		data->map->player.y -= 1;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->tiles[9],
								data->map->player.x * SIZE, data->map->player.y * SIZE);
		data->moves++;
		ft_printf("\033[1;37mMOVES:\033[0m%i\n", data->moves);
	}
}

void	move_down(t_data *data)
{
	//print_coordinates(data);
	if (data->map->layout[data->map->player.y + 1][data->map->player.x] == 'C')
	{
		data->map->gathered--;
		data->map->layout[data->map->player.y + 1][data->map->player.x] = '0';
	}
	if (data->map->layout[data->map->player.y + 1][data->map->player.x] == '1'
		|| (data->map->layout[data->map->player.y + 1]
			[data->map->player.x] == 'E' && data->map->gathered >= 1))
		return ;
	else
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->tiles[10],
								data->map->player.x * SIZE, data->map->player.y * SIZE);
		data->map->player.y += 1;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->tiles[9],
								data->map->player.x * SIZE, data->map->player.y * SIZE);
		data->moves++;
		ft_printf("\033[1;37mMOVES:\033[0m%i\n", data->moves);
	}
}

void	move_right(t_data *data)
{
	//print_coordinates(data);
	if (data->map->layout[data->map->player.y][data->map->player.x + 1] == 'C')
	{
		data->map->gathered--;
		data->map->layout[data->map->player.y][data->map->player.x + 1] = '0';
	}
	if (data->map->layout[data->map->player.y][data->map->player.x + 1] == '1'
		|| (data->map->layout[data->map->player.y]
			[data->map->player.x + 1] == 'E' && data->map->gathered >= 1))
		return ;
	else
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->tiles[10],
								data->map->player.x * SIZE, data->map->player.y * SIZE);
		data->map->player.x += 1;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->tiles[9],
								data->map->player.x * SIZE, data->map->player.y * SIZE);
		data->moves++;
		ft_printf("\033[1;37mMOVES:\033[0m%i\n", data->moves);
	}
}

void	move_left(t_data *data)
{
	//print_coordinates(data);

	if (data->map->layout[data->map->player.y][data->map->player.x - 1] == 'C')
	{
		data->map->gathered--;
		data->map->layout[data->map->player.y][data->map->player.x - 1] = '0';
	}
	if (data->map->layout[data->map->player.y][data->map->player.x - 1] == '1'
		|| (data->map->layout[data->map->player.y]
			[data->map->player.x - 1] == 'E' && data->map->gathered >= 1)) {
		return;
	}else
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->tiles[10],
								data->map->player.x * SIZE, data->map->player.y * SIZE);
		data->map->player.x -= 1;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->tiles[9],
								data->map->player.x * SIZE, data->map->player.y * SIZE);
		data->moves++;
		ft_printf("\033[1;37mMOVES:\033[0m%i\n", data->moves);
	}
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
//	init_null(data);
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
