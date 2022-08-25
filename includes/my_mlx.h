#ifndef MY_MLX_H
# define MY_MLX_H

# include "../lib/mlx/mlx.h"
# include "scene.h"

# define KEY_RIGHT 124
# define KEY_LEFT 123

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_data	data;
	t_scene	scene;
}	t_mlx;

#endif
