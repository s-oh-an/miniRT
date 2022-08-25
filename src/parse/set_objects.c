/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:46:39 by sohan             #+#    #+#             */
/*   Updated: 2022/08/25 19:07:18 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/scene.h"
#include "../../includes/parse.h"
#include "../../includes/utils.h"

void	set_sphere(t_scene *scene, char const **data)
{
	t_sphere		sp;
	t_object		*obj;
	t_object_list	*tmp;

	if (get_field_count(data) != 4)
		error_exit("Error\nWrong Argument Field Count");
	obj = ft_calloc(1, sizeof(t_object));
	obj->property = ft_calloc(1, sizeof(t_sphere));
	if (!obj || !obj->property)
		error_exit("Error\nError While malloc");
	obj->type = T_SPHERE;
	set_vec3(&sp.coordinate, data[1]);
	sp.diameter = ft_stof(data[2]);
	if (!is_valid_property(sp.diameter))
		error_exit("Error\nInvalid Diameter Value");
	sp.radius2 = (sp.diameter / 2) * (sp.diameter / 2);
	set_vec3(&sp.color, data[3]);
	if (!is_valid_color_range(&scene->ambient.color))
		error_exit("Error\nInvalid Color Range");
	*(t_sphere *)obj->property = sp;
	tmp = ft_lstnew(obj);
	if (!tmp)
		error_exit("Error\nError While malloc");
	ft_lstadd_back(&scene->objects, tmp);
}

void	set_plane(t_scene *scene, char const **data)
{
	t_plane			pl;
	t_object		*obj;
	t_object_list	*tmp;

	if (get_field_count(data) != 4)
		error_exit("Error\nWrong Argument Field Count");
	obj = ft_calloc(1, sizeof(t_object));
	obj->property = ft_calloc(1, sizeof(t_plane));
	if (!obj || !obj->property)
		error_exit("Error\nError While malloc");
	obj->type = T_PLANE;
	set_vec3(&pl.coordinate, data[1]);
	set_vec3(&pl.n_vector, data[2]);
	if (!is_valid_vector_range(&scene->camera.n_vector))
		error_exit("Error\nInvalid Normal Vector Range");
	set_vec3(&pl.color, data[3]);
	if (!is_valid_color_range(&scene->ambient.color))
		error_exit("Error\nInvalid Color Range");
	*(t_plane *)obj->property = pl;
	tmp = ft_lstnew(obj);
	if (!tmp)
		error_exit("Error\nError While malloc");
	ft_lstadd_back(&scene->objects, tmp);
}

static void	set_cylinder_property(t_cylinder *cy, char const **data)
{
	cy->diameter = ft_stof(data[3]);
	cy->height = ft_stof(data[4]);
	if (!is_valid_property(cy->diameter) || !is_valid_property(cy->height))
		error_exit("Error\nInvalid Property Value");
	cy->radius2 = (cy->diameter / 2) * (cy->diameter / 2);
}

void	set_cylinder(t_scene *scene, char const **data)
{
	t_cylinder		cy;
	t_object		*obj;
	t_object_list	*tmp;

	if (get_field_count(data) != 6)
		error_exit("Error\nWrong Argument Field Count");
	obj = ft_calloc(1, sizeof(t_object));
	obj->property = ft_calloc(1, sizeof(t_cylinder));
	if (!obj || !obj->property)
		error_exit("Error\nError While malloc");
	obj->type = T_CYLINDER;
	set_vec3(&cy.coordinate, data[1]);
	set_vec3(&cy.n_vector, data[2]);
	if (!is_valid_vector_range(&scene->camera.n_vector))
		error_exit("Error\nInvalid Normal Vector Range");
	set_cylinder_property(&cy, data);
	set_vec3(&cy.color, data[5]);
	if (!is_valid_color_range(&scene->ambient.color))
		error_exit("Error\nInvalid Color Range");
	*(t_cylinder *)obj->property = cy;
	tmp = ft_lstnew(obj);
	if (!tmp)
		error_exit("Error\nError While malloc");
	ft_lstadd_back(&scene->objects, tmp);
}
