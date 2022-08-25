#include "../../includes/discriminant.h"
#include "../../includes/vector.h"
#include "../../includes/hit.h"
#include <math.h>

int	is_ray_hit_sphere(t_sphere *sphere, t_ray *ray)
{
	double	b;
	double	c;
	double	d;
	double	t[2];
	t_hit	new;

	b = vdot(ray->direction, vminus(ray->origin, sphere->coordinate));
	c = vlen2(vminus(ray->origin, sphere->coordinate)) - sphere->radius2;
	d = (b * b) - c;
	if (d < -E)
		return (0);
	t[0] = -b - sqrt(d);
	t[1] = -b + sqrt(d);
	if (t[0] * t[1] > E)
	{
		if (t[0] < -E)
			return (0);
	}
	new = make_hit_sphere(sphere, t, ray);
	return (update_hit(ray, new));
}

int	is_ray_hit_plane(t_plane *plane, t_ray *ray)
{
	double	c_dot_n;
	double	d_dot_n;
	double	t;
	t_hit	new;
	t_vec	c;

	c = vminus(plane->coordinate, ray->origin);
	c_dot_n = vdot(plane->n_vector, c);
	d_dot_n = vdot(plane->n_vector, ray->direction);
	if (d_dot_n > -E && d_dot_n < E)
		return (0);
	t = c_dot_n / d_dot_n;
	if (t < -E)
		return (0);
	new = make_hit_plane(plane, t, ray);
	return (update_hit(ray, new));
}
