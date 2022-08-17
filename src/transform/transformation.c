#include "../../includes/scene.h"
#include "../../includes/parse.h"
#include "../../includes/vector.h"

t_vec	rotate(t_vec *world, t_camera *camera)
{
	t_vec	new;
	t_vec	new_x;
	t_vec	new_y;
	t_vec	new_z;

	new_x = vec3(camera->x.x, camera->y.x, camera->z.x);
	new_y = vec3(camera->x.y, camera->y.y, camera->z.y);
	new_z = vec3(camera->x.z, camera->y.z, camera->z.z);
	new.x = vdot(*world, new_x);
	new.y = vdot(*world, new_y);
	new.z = vdot(*world, new_z);
	return (new);
}

t_vec	translate(t_vec *world, t_camera *camera)
{
	t_vec	new;
	
	new = vminus(*world, camera->orig);
	return (new);
}
