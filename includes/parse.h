#ifndef PARSE_H
# define PARSE_H

# include "scene.h"

void	read_rt_file(int fd, t_scene *scene);

void	set_sphere(t_scene *scene, char const **data);
void	set_plane(t_scene *scene, char const **data);
void	set_cylinder(t_scene *scene, char const **data);
void	set_ambient(t_scene *scene, char const **data, int *identifier_flag);
void	set_camera(t_scene *scene, char const **data, int *identifier_flag);
void	set_light(t_scene *scene, char const **data, int *identifier_flag);

#endif
