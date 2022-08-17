#include "../../includes/parse.h"
#include "../../includes/utils.h"
#include "../../lib/libft/libft.h"
#include "../../includes/vector.h"
#include <math.h>

int	is_duplicate_identifier(int identifier_flag)
{
	if (identifier_flag != 0)
		return (1);
	return (0);
}

int	is_valid_ratio_range(float ratio)
{
	if (ratio < 0.0 || ratio > 1.0)
		return (0);
	return (1);
}

int	is_valid_color_range(t_color *color)
{
	if (color->x < 0.0 || color->x > 255.0 || color->y < 0.0 ||
		color->y > 255.0 || color->z < 0.0 || color->z > 255.0)
		return (0);
	return (1);
}

int	is_valid_vector_range(t_normal_vector *vec)
{
	if (vec->x < -1.0 || vec->x > 1.0 || vec->y < -1.0 || vec->y > 1.0 ||
		vec->z < -1.0 || vec->z > 1.0)
		return (0);
	return (1);
}

int	is_valid_property(float value)
{
	if (value < 0.0)
		return (0);
	return (1);
}

int	get_field_count(char const **data)
{
	int	i;

	i = 0;
	while (data[i])
		++i;
	return (i);
}

void	set_light_ratio(float *ratio, char const *str)
{
	*ratio = ft_stof(str);
	if (!is_valid_ratio_range(*ratio))
	{
		ft_putendl_fd("Error\nInvalid Lightning Ratio", 2);
		exit(1);
	}
}

void	set_vec3(struct s_vec3 *vec, char const *str)
{
	char	**xyz;
	int		i;

	i = 0;
	xyz = ft_split(str, ',');
	if (!xyz)
	{
		ft_putendl_fd("Error\nError While malloc", 2);
		exit(1);
	}
	while (xyz[i])
		++i;
	if (i != 3)
	{
		ft_putendl_fd("Error\nInvalid vec", 2);
		exit(1);
	}
	vec->x = ft_stof(xyz[0]);
	vec->y = ft_stof(xyz[1]);
	vec->z = ft_stof(xyz[2]);
	free_array(xyz);
}

void	set_ambient(t_scene *scene, char const **data, int *identifier_flag)
{
	if (is_duplicate_identifier(*identifier_flag & 1))
	{
		ft_putendl_fd("Error\nDuplicate Identifier", 2);
		exit(1);
	}
	if (get_field_count(data) != 3)
	{
		ft_putendl_fd("Error\nNot enough Field Arguments", 2);
		exit(1);
	}
	*identifier_flag |= 1;
	set_light_ratio(&scene->ambient.ratio, data[1]);
	set_vec3(&scene->ambient.color, data[2]);
	if (!is_valid_color_range(&scene->ambient.color))
	{
		ft_putendl_fd("Error\nInvalid Color Range", 2);
		exit(1);
	}
}

void	set_camera(t_scene *scene, char const **data, int *identifier_flag)
{
	if (get_field_count(data) != 4)
	{
		ft_putendl_fd("Error\nNot enough Field Arguments", 2);
		exit(1);
	}
	if (is_duplicate_identifier(*identifier_flag & 2))
	{
		ft_putendl_fd("Error\nDuplicate Identifier", 2);
		exit(1);
	}
	*identifier_flag |= 2;
	set_vec3(&scene->camera.orig, data[1]);
	set_vec3(&scene->camera.n_vector, data[2]);
	if (!is_valid_vector_range(&scene->camera.n_vector))
	{
		ft_putendl_fd("Error\nInvalid Normal Vector Range", 2);
		exit(1);
	}
	scene->camera.fov = ft_stof(data[3]);
	if (scene->camera.fov < 0 || scene->camera.fov > 180)
	{	
		ft_putendl_fd("Error\nInvalid FOV", 2);
		exit(1);
	}
	// scene->camera.win.width = 1280;
	// scene->camera.win.height = 720;
	// scene->camera.win.ratio = 16.0 / 9.0;
	// scene->camera.viewport_h = 2.0;
	// scene->camera.viewport_w = scene->camera.viewport_h * (16 /9);
	// scene->camera.focal_len = 1.0 / tan((scene->camera.fov / 2) * (M_PI / 180));
	// scene->camera.left_bottom = vec3(-(scene->camera.viewport_w / 2), -1, -(scene->camera.focal_len));
}

void	set_light(t_scene *scene, char const **data, int *identifier_flag)
{
	if (get_field_count(data) != 4)
	{
		ft_putendl_fd("Error\nNot enough Field Arguments", 2);
		exit(1);
	}
	if (is_duplicate_identifier(*identifier_flag & 4))
	{
		ft_putendl_fd("Error\nDuplicate Identifier", 2);
		exit(1);
	}
	*identifier_flag |= 4;
	set_vec3(&scene->light.coordinate, data[1]);
	set_light_ratio(&scene->light.ratio, data[2]);
}

void	set_sphere(t_scene *scene, char const **data)
{
	t_sphere		sp;
	t_object		*obj;
	t_object_list	*tmp;

	if (get_field_count(data) != 4)
	{
		ft_putendl_fd("Error\nNot enough Field Arguments", 2);
		exit(1);
	}
	obj = ft_calloc(1, sizeof(t_object));
	obj->property = ft_calloc(1, sizeof(t_sphere));
	if (!obj || !obj->property)
	{
		ft_putendl_fd("Error\nError While malloc", 2);
		exit(1);
	}
	obj->type = T_SPHERE;
	set_vec3(&sp.coordinate, data[1]);
	sp.diameter = ft_stof(data[2]);
	if (!is_valid_property(sp.diameter))
	{
		ft_putendl_fd("Error\nInvalid Diameter Value", 2);
		exit(1);
	}
	sp.radius2 = (sp.diameter / 2) * (sp.diameter / 2);
	set_vec3(&sp.color, data[3]);
	if (!is_valid_color_range(&scene->ambient.color))
	{
		ft_putendl_fd("Error\nInvalid Color Range", 2);
		exit(1);
	}
	*(t_sphere*)obj->property = sp;
	tmp = ft_lstnew(obj);
	if (!tmp)
	{
		ft_putendl_fd("Error\nError While malloc", 2);
		exit(1);
	}
	ft_lstadd_back(&scene->objects, tmp);
}

void	set_plane(t_scene *scene, char const **data)
{
	t_plane			pl;
	t_object		*obj;
	t_object_list	*tmp;

	if (get_field_count(data) != 4)
	{
		ft_putendl_fd("Error\nNot enough Field Arguments", 2);
		exit(1);
	}
	obj = ft_calloc(1, sizeof(t_object));
	obj->property = ft_calloc(1, sizeof(t_plane));
	if (!obj || !obj->property)
	{
		ft_putendl_fd("Error\nError While malloc", 2);
		exit(1);
	}
	obj->type = T_PLANE;
	set_vec3(&pl.coordinate, data[1]);
	set_vec3(&pl.n_vector, data[2]);
	if (!is_valid_vector_range(&scene->camera.n_vector))
	{
		ft_putendl_fd("Error\nInvalid Normal Vector Range", 2);
		exit(1);
	}
	set_vec3(&pl.color, data[3]);
	if (!is_valid_color_range(&scene->ambient.color))
	{
		ft_putendl_fd("Error\nInvalid Color Range", 2);
		exit(1);
	}
	*(t_plane*)obj->property = pl;
	tmp = ft_lstnew(obj);
	if (!tmp)
	{
		ft_putendl_fd("Error\nError While malloc", 2);
		exit(1);
	}
	ft_lstadd_back(&scene->objects, tmp);
}

void	set_cylinder(t_scene *scene, char const **data)
{
	t_cylinder		cy;
	t_object		*obj;
	t_object_list	*tmp;

	if (get_field_count(data) != 6)
	{
		ft_putendl_fd("Error\nNot enough Field Arguments", 2);
		exit(1);
	}
	obj = ft_calloc(1, sizeof(t_object));
	obj->property = ft_calloc(1, sizeof(t_cylinder));
	if (!obj || !obj->property)
	{
		ft_putendl_fd("Error\nError While malloc", 2);
		exit(1);
	}
	obj->type = T_CYLINDER;
	set_vec3(&cy.coordinate, data[1]);
	set_vec3(&cy.n_vector, data[2]);
	if (!is_valid_vector_range(&scene->camera.n_vector))
	{
		ft_putendl_fd("Error\nInvalid Normal Vector Range", 2);
		exit(1);
	}
	cy.diameter = ft_stof(data[3]);
	cy.height = ft_stof(data[4]);
	if (!is_valid_property(cy.diameter) || !is_valid_property(cy.height))
	{
		ft_putendl_fd("Error\nInvalid Property Value", 2);
		exit(1);
	}
	cy.radius2 = (cy.diameter / 2) * (cy.diameter / 2);
	set_vec3(&cy.color, data[5]);
	if (!is_valid_color_range(&scene->ambient.color))
	{
		ft_putendl_fd("Error\nInvalid Color Range", 2);
		exit(1);
	}
	*(t_cylinder*)obj->property = cy;
	tmp = ft_lstnew(obj);
	if (!tmp)
	{
		ft_putendl_fd("Error\nError While malloc", 2);
		exit(1);
	}
	ft_lstadd_back(&scene->objects, tmp);
}

int	is_valid_scene(int identifier_flag, t_object_list *list)
{
	if (!list || identifier_flag != 7)
		return (0);
	return (1);
}

void	read_rt_file(int fd, t_scene *scene)
{
	char	*line;
	char	**data;
	int		ret;
	int		identifier_flag;
	
	ret = 1;
	identifier_flag = 0;
	line = NULL;
	scene->objects = NULL;
	while (ret)
	{
		if (line)
			free(line);
		ret = get_next_line(fd, &line);
		if (!*line)
			continue ;
		data = ft_split_space(line);
		if (!ft_strncmp(data[0], "A", ft_strlen(data[0])))
			set_ambient(scene, (char const **)data, &identifier_flag);
		else if (!ft_strncmp(data[0], "C", ft_strlen(data[0])))
			set_camera(scene, (char const **)data, &identifier_flag);
		else if (!ft_strncmp(data[0], "L", ft_strlen(data[0])))
			set_light(scene, (char const **)data, &identifier_flag);
		else if (!ft_strncmp(data[0], "sp", ft_strlen(data[0])))
			set_sphere(scene, (char const **)data);
		else if (!ft_strncmp(data[0], "pl", ft_strlen(data[0])))
			set_plane(scene, (char const **)data);
		else if (!ft_strncmp(data[0], "cy", ft_strlen(data[0])))
			set_cylinder(scene, (char const **)data);
		else
		{
			ft_putendl_fd("Error\nInvalid Identifier", 2);
			exit(1);
		}
		free_array(data);
	}
	if (line)
		free(line);
	if (!is_valid_scene(identifier_flag, scene->objects))
	{
		ft_putendl_fd("Error\nNot enough Scene Arguments", 2);
		exit(1);
	}
}

int	is_rt_file(char const *str)
{
	char	*file;

	file = ft_strchr(str, '.');
	if (!file || ft_strncmp(file, ".rt", ft_strlen(file)) != 0)
		return (0);
	return (1);
}
