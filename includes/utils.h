#ifndef UTILS_H
# define UTILS_H

# include "scene.h"
# include "my_mlx.h"

double	ft_stof(char const *str);
int		exit_minirt(t_mlx *m);
void	init_mlx(t_mlx *m, t_window w);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		press_key(int key_code, t_mlx *m);

int		to_rgb(t_color color);
void	free_array(char **array);
void	error_exit(char const *msg);
void	perror_exit(void);

int		is_duplicate_identifier(int identifier_flag);
int		is_valid_ratio_range(double ratio);
int		is_valid_color_range(t_color *color);
int		is_valid_vector_range(t_normal_vector *vec);
int		is_valid_property(double value);

void	set_vec3(struct s_vec3 *vec, char const *str);
void	set_light_ratio(double *ratio, char const *str);
int		get_field_count(char const **data);
int		is_rt_file(char const *str);

#endif
