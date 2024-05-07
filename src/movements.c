/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwinder <rwinder@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:20:00 by rwinder           #+#    #+#             */
/*   Updated: 2023/09/04 16:20:00 by rwinder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/so_long.h"

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		ft_printf("\033[1;33mYou give up this easily what a same... smh\033[1;33o\n");
//		ft_quit(data);
	}
	if (keysym == XK_Up || keysym == XK_w)
		up(data);
	if (keysym == XK_Down || keysym == XK_s)
		down(data);
	if (keysym == XK_Right || keysym == XK_d)
		right(data);
	if (keysym == XK_Left || keysym == XK_a)
		left(data);
	if (data->map->layout[data->map->player.y][data->map->player.x] == 'E')
	{
		ft_printf("\033[1;32mCongrats, you put clippy in the trash, good job!\033[0m\n");
		ft_quit(data);
	}
	return (0);
}

void	up(t_data *data)
{
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

void	right(t_data *data)
{
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

void	down(t_data *data)
{
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

void	left(t_data *data)
{
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