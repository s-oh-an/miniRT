#ifndef UTILS_H
# define UTILS_H

#include "scene.h"
#include "my_mlx.h"

double	ft_stof(char const *str);

int		exit_minirt(t_mlx *m);
void	init_mlx(t_mlx *m, t_window w);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		press_key(int key_code, t_mlx *m);

int		to_rgb(t_color color);
void	free_array(char **array);

#endif
