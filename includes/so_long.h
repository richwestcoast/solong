#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>

# define SIZE 64

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_map
{
	char	**layout;
	int		valid;
	int		lines;
	int		len;
	int		collect;
	int		gathered;
	t_point	player;
	t_point	exit;
}	t_map;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**tiles;
	int		moves;
	t_map	*map;
	t_img	img;
	t_point	tile;
}	t_data;

t_data	*init(void);
t_data	*init_data(void);
t_data	*init(void);

int		map_lines(char *file);
void	map_check(char *file, t_data *data);
char	**file_to_map(char *file);
void	fill(char **layout_cpy, t_data *data, int x, int y);
int		comp1_check(t_data *data);
int		comp3_check(t_data *data, int start_exit);
int		path_check(char *file, t_data *data);
int		strlen_solong(char	*str);
int		comp2_check(t_data *data, int x, int y);
int		dimension_check(t_data *data);

int 	render(t_data *data);
int 	render_win(t_data *data);

void	free_array(char **arr, int lines);

int		render_map(t_data *data);
void	render_wall_corner(t_data *data, int y, int x);
void	render_wall_border(t_data *data, int y, int x);
void	render_tile(t_data *data, int y, int x);
int		wall_check(t_data *data);

void	init_img1(t_data *data);
void	init_img2(t_data *data);

t_data	*init_data(void);
int		handle_keypress(int keysym, t_data *data);
void	up(t_data *data);
void	down(t_data *data);
void	right(t_data *data);
void	left(t_data *data);

int		ft_quit(t_data *data);
int		free_game(t_data *data);
void	free_tiles(t_data *data);
void	free_map(t_map *map);
#endif