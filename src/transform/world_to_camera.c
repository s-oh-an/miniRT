/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_to_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:52:18 by sohan             #+#    #+#             */
/*   Updated: 2022/08/25 18:53:02 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/scene.h"
#include "../../includes/vector.h"
#include "../../includes/transform.h"
#include <math.h>

static void	set_camera_axis(t_camera *camera)
{
	camera->z = vmulti_f(vunit(camera->n_vector), -1);
	if (camera->z.x == 0 && camera->z.y == 1 && camera->z.z == 0)
		camera->x = vunit(vcross(vec3(-1, 0, 0), camera->z));
	else if (camera->z.x == 0 && camera->z.y == -1 && camera->z.z == 0)
		camera->x = vunit(vcross(vec3(1, 0, 0), camera->z));
	else
		camera->x = vunit(vcross(vec3(0, 1, 0), camera->z));
	camera->y = vunit(vcross(camera->z, camera->x));
}

static void	set_camera_viewport(t_scene *scene, t_camera *camera)
{
	scene->win.w = 1280;
	scene->win.h = 720;
	scene->win.ratio = (double)scene->win.w / (double)scene->win.h;
	camera->viewport_h = 2.0;
	camera->viewport_w = camera->viewport_h * (scene->win.ratio);
	camera->focal_len = 1.0 / tan((camera->fov / 2) * (M_PI / 180));
	camera->left_bottom = vec3(-camera->viewport_w / 2, \
						-camera->viewport_h / 2, -camera->focal_len);
}

static void	obj_transform(t_object *obj, t_camera *camera)
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;

	if (obj->type == T_SPHERE)
	{
		sp = obj->property;
		sp->coordinate = translate(&sp->coordinate, camera);
		sp->coordinate = rotate(&sp->coordinate, camera);
	}
	else if (obj->type == T_PLANE)
	{
		pl = obj->property;
		pl->coordinate = translate(&pl->coordinate, camera);
		pl->coordinate = rotate(&pl->coordinate, camera);
		pl->n_vector = rotate(&pl->n_vector, camera);
	}
	else if (obj->type == T_CYLINDER)
	{
		cy = obj->property;
		cy->coordinate = translate(&cy->coordinate, camera);
		cy->coordinate = rotate(&cy->coordinate, camera);
		cy->n_vector = rotate(&cy->n_vector, camera);
	}
}

void	world_to_camera(t_scene *scene)
{
	t_object_list	*cur;
	t_object		*obj;

	set_camera_axis(&scene->camera);
	set_camera_viewport(scene, &scene->camera);
	scene->light.coordinate = translate(&scene->light.coordinate, \
													&scene->camera);
	scene->light.coordinate = rotate(&scene->light.coordinate, &scene->camera);
	cur = scene->objects;
	while (cur)
	{
		obj = cur->content;
		obj_transform(obj, &scene->camera);
		cur = cur->next;
	}
}
