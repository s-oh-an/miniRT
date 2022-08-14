#include "../../includes/scene.h"
#include "../../includes/vector.h"
#include "../../includes/transform.h"

static void	set_camera_axis(t_camera *camera)
{
	camera->z = vmulti_f(vunit(camera->n_vector), -1);
	camera->x = vcross(vec3(0, 1, 0), camera->z);
	camera->y = vcross(camera->x, camera->z);
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
	scene->light.coordinate = translate(&scene->light.coordinate, &scene->camera);
	scene->light.coordinate = rotate(&scene->light.coordinate, &scene->camera);
	cur = scene->objects;
	while (cur)
	{
		obj = cur->content;
		obj_transform(obj, &scene->camera);
		cur = cur->next;
	}
	scene->camera.orig = translate(&scene->camera.orig, &scene->camera);
	scene->camera.orig = rotate(&scene->camera.orig, &scene->camera);
	scene->camera.n_vector = rotate(&scene->camera.n_vector, &scene->camera);
}
