#include "../../includes/hit.h"
#include "../../includes/vector.h"
#include <math.h>

int	update_hit(t_ray *ray, t_ray new)
{
	if (ray->hit.t > new.hit.t)
	{
		*ray = new;
		return (1);
	}
	return (0);
}

t_ray	make_hit_sphere(t_sphere *sphere, double *t, t_ray *ray)
{
	t_ray	new;

	new.direction = ray->direction;
	new.origin = ray->origin;
	if (t[0] * t[1] < -E)
		new.hit.t = t[1];
	else
		new.hit.t = t[0];
	new.hit.point = vmulti_f(new.direction, new.hit.t);
	new.hit.color = sphere->color;
	new.hit.normal = vunit(vminus(new.hit.point, sphere->coordinate));
	if ((vdot(ray->direction, new.hit.normal) < E))
		new.hit.in_object = 0;
	else
	{
		new.hit.in_object = 1;
		new.hit.normal = vmulti_f(new.hit.normal, -1);
	}
	new.hit.ray_hit = 1;
	return (new);
}

t_ray	make_hit_plane(t_plane *plane, double t, t_ray *ray)
{
	t_ray	new;

	new.direction = ray->direction;
	new.origin = ray->origin;
	new.hit.t = t;
	new.hit.point = vmulti_f(new.direction, new.hit.t);
	new.hit.color = plane->color;
	new.hit.normal = vunit(plane->n_vector);
	if (vdot(ray->direction, new.hit.normal) < E)
		new.hit.in_object = 0;
	else
	{
		new.hit.in_object = 1;
		new.hit.normal = vmulti_f(new.hit.normal, -1);
	}
	new.hit.ray_hit = 1;
	return (new);
}

t_ray	make_hit_cylinder_topbottom(t_cylinder *cylinder, double t, t_ray *ray)
{
	t_ray	new;
	t_vec	r_n_vector;

	new.direction = ray->direction;
	new.origin = ray->origin;
	new.hit.t = t;
	new.hit.point = vmulti_f(new.direction, new.hit.t);	
	new.hit.color = cylinder->color;
	r_n_vector = vunit(vmulti_f(cylinder->n_vector, -1.0));
	if (cylinder->top)
		new.hit.normal = vunit(cylinder->n_vector);
	else 
		new.hit.normal = r_n_vector;
	if (vdot(ray->direction, new.hit.normal) < E)
		new.hit.in_object = 0;
	else 
	{	
		new.hit.in_object = 1;
		new.hit.normal = vmulti_f(new.hit.normal, -1);
	}
	new.hit.ray_hit = 1;
	return (new);
}

t_ray	make_hit_cylinder(t_cylinder *cylinder, double t, t_ray *ray)
{
	t_ray	new;
	t_vec	r_n_vector;
	t_vec	cp;
	t_vec	ccp;

	new.direction = ray->direction;
	new.origin = ray->origin;
	new.hit.t = t;
	new.hit.point = vmulti_f(new.direction, new.hit.t);	
	new.hit.color = cylinder->color;
	r_n_vector = vmulti_f(vunit(cylinder->n_vector), -1);
	cp = vminus(new.hit.point, cylinder->coordinate);
	ccp = vmulti_f(r_n_vector, vdot(r_n_vector, cp));
	new.hit.normal = vunit(vminus(cp, ccp));
	if (vdot(ray->direction, new.hit.normal) < E)
		new.hit.in_object = 0;
	else 
	{	
		new.hit.in_object = 1;
		new.hit.normal = vmulti_f(new.hit.normal, -1);
	}
	new.hit.ray_hit = 1;
	return (new);
}
