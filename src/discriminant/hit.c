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

	new.vec = ray->vec;
	if (t[0] * t[1] < -E)
		new.hit.t = t[1];
	else
		new.hit.t = t[0];
	new.hit.hit_point = vmulti_f(new.vec, new.hit.t);
	new.hit.hit_color = sphere->color;
	new.hit.hit_normal = vunit(vminus(new.hit.hit_point, sphere->coordinate));
	if ((vdot(ray->vec, new.hit.hit_normal) < E))
		new.hit.in_object = 0;
	else
	{
		new.hit.in_object = 1;
		new.hit.hit_normal = vmulti_f(new.hit.hit_normal, -1);
	}
	new.hit.ray_hit = 1;
	return (new);
}

t_ray	make_hit_plane(t_plane *plane, double t, t_ray *ray)
{
	t_ray	new;

	new.vec = ray->vec;
	new.hit.t = t;
	new.hit.hit_point = vmulti_f(new.vec, new.hit.t);
	new.hit.hit_color = plane->color;
	new.hit.hit_normal = vunit(plane->n_vector);
	if (vdot(ray->vec, new.hit.hit_normal) < E)
		new.hit.in_object = 0;
	else
	{
		new.hit.in_object = 1;
		new.hit.hit_normal = vmulti_f(new.hit.hit_normal, -1);
	}
	new.hit.ray_hit = 1;
	return (new);
}

t_ray	make_hit_cylinder_topbottom(t_cylinder *cylinder, double t, t_ray *ray)
{
	t_ray	new;
	t_vec	r_n_vector;

	new.vec = ray->vec;
	new.hit.t = t;
	new.hit.hit_point = vmulti_f(new.vec, new.hit.t);	
	new.hit.hit_color = cylinder->color;
	r_n_vector = vunit(vmulti_f(cylinder->n_vector, -1.0));
	if (cylinder->top)
		new.hit.hit_normal = vunit(cylinder->n_vector);
	else 
		new.hit.hit_normal = r_n_vector;
	if (vdot(ray->vec, new.hit.hit_normal) < E)
		new.hit.in_object = 0;
	else 
	{	
		new.hit.in_object = 1;
		new.hit.hit_normal = vmulti_f(new.hit.hit_normal, -1);
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

	new.vec = ray->vec;
	new.hit.t = t;
	new.hit.hit_point = vmulti_f(new.vec, new.hit.t);	
	new.hit.hit_color = cylinder->color;
	r_n_vector = vmulti_f(vunit(cylinder->n_vector), -1);
	cp = vminus(new.hit.hit_point, cylinder->coordinate);
	ccp = vmulti_f(r_n_vector, vdot(r_n_vector, cp));
	new.hit.hit_normal = vunit(vminus(cp, ccp));
	if (vdot(ray->vec, new.hit.hit_normal) < E)
		new.hit.in_object = 0;
	else 
	{	
		new.hit.in_object = 1;
		new.hit.hit_normal = vmulti_f(new.hit.hit_normal, -1);
	}
	new.hit.ray_hit = 1;
	return (new);
}
