#ifndef MY_MLX_H
# define MY_MLX_H

# include "../lib/mlx/mlx.h" //
# include "scene.h"

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

void	init_mlx(t_mlx *m, t_window w);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		press_key(int key_code, t_mlx *m);

#endif
