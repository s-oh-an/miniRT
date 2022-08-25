#include "../../includes/scene.h"
#include "../../includes/parse.h"
#include "../../includes/utils.h"

void	set_ambient(t_scene *scene, char const **data, int *identifier_flag)
{
	if (is_duplicate_identifier(*identifier_flag & 1))
		error_exit("Error\nDuplicate Identifier");
	if (get_field_count(data) != 3)
		error_exit("Error\nWrong Argument Field Count");
	*identifier_flag |= 1;
	set_light_ratio(&scene->ambient.ratio, data[1]);
	set_vec3(&scene->ambient.color, data[2]);
	if (!is_valid_color_range(&scene->ambient.color))
		error_exit("Error\nInvalid Color Range");
}

void	set_camera(t_scene *scene, char const **data, int *identifier_flag)
{
	if (get_field_count(data) != 4)
		error_exit("Error\nWrong Argument Field Count");
	if (is_duplicate_identifier(*identifier_flag & 2))
		error_exit("Error\nDuplicate Identifier");
	*identifier_flag |= 2;
	set_vec3(&scene->camera.orig, data[1]);
	set_vec3(&scene->camera.n_vector, data[2]);
	if (!is_valid_vector_range(&scene->camera.n_vector))
		error_exit("Error\nInvalid Normal Vector Range");
	scene->camera.fov = ft_stof(data[3]);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
		error_exit("Error\nInvalid FOV");
}

void	set_light(t_scene *scene, char const **data, int *identifier_flag)
{
	if (get_field_count(data) != 4)
		error_exit("Error\nWrong Argument Field Count");
	if (is_duplicate_identifier(*identifier_flag & 4))
		error_exit("Error\nDuplicate Identifier");
	*identifier_flag |= 4;
	set_vec3(&scene->light.coordinate, data[1]);
	set_light_ratio(&scene->light.ratio, data[2]);
}


