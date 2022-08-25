#ifndef MY_MLX_H
# define MY_MLX_H

# include "../lib/mlx/mlx.h"

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
}	t_mlx;

#endif
