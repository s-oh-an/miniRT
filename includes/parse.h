#ifndef PARSE_H
# define PARSE_H

# include "scene.h"

int		is_valid_identifier(char const *str);
int		is_valid_scene();
int		is_valid_color_range(t_color *color);
int		is_valid_vector_range();
int		is_valid_ratio_range(float ratio);
int		is_valid_fov_range();
void	read_rt_file(int fd, t_scene *scene);
void	set_camera_axis(t_camera *camera);
t_vec3	translate(t_vec3 *world, t_camera *camera);
void	world_to_camera(t_scene *scene);

#endif
