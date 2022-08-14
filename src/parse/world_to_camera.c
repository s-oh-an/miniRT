#include "../../includes/scene.h"
#include "../../includes/parse.h"
#include "../../includes/vector.h"

void	set_camera_axis(t_camera *camera)
{
	t_vec3	y_axis;
	
	camera->n = vec_op_unit(camera->n_vector);
	camera->n.x *= -1;
	camera->n.y *= -1;
	camera->n.z *= -1;
	y_axis.x = 0;
	y_axis.y = 1;
	y_axis.z = 0;
	camera->u = vec_op_crossproduct(y_axis, camera->n);
	camera->v = vec_op_crossproduct(camera->u, camera->n);
}

t_vec3	rotate(t_vec3 *world, t_camera *camera)
{
	t_vec3	new;
	
	//new.x = world->x * camera->u.x + world->y * camera->u.y + world->z * camera->u.z - vec_op_dotproduct(camera->orig, camera->u);
	//new.y = world->x * camera->v.x + world->y * camera->v.y + world->z * camera->v.z - vec_op_dotproduct(camera->orig, camera->v);
	//new.z = world->x * camera->n.x + world->y * camera->n.y + world->z * camera->n.z - vec_op_dotproduct(camera->orig, camera->n);
	new.x = vec_op_dotproduct(*world, camera->u);
	new.y = vec_op_dotproduct(*world, camera->v);
	new.z = vec_op_dotproduct(*world, camera->n);
	return (new);
}

t_vec3	translate(t_vec3 *world, t_camera *camera)
{
	t_vec3	new;
	
	new = vec_op_minus_vec(*world, camera->orig);
	return (new);
}

void	obj_transform(t_object *obj, t_camera *camera)
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
