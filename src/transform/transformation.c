#include "../../includes/scene.h"
#include "../../includes/parse.h"
#include "../../includes/vector.h"

t_vec	rotate(t_vec *world, t_camera *camera)
{
	t_vec	new;

	new.x = vdot(*world, camera->x);
	new.y = vdot(*world, camera->y);
	new.z = vdot(*world, camera->z);
	return (new);
}

t_vec	translate(t_vec *world, t_camera *camera)
{
	t_vec	new;

	new = vminus(*world, camera->orig);
	return (new);
}
