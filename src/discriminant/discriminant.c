#include "../../includes/discriminant.h"
#include "../../includes/vector.h"
#include "../../includes/hit.h"
#include <math.h>

#include <stdio.h>

// 판별식은 d, t는 레이방벡의 실수배

int	is_ray_hit_sphere(t_sphere *sphere, t_ray *ray, t_coordinate e)
{
	double	b;
	double	c;
	double	d;
	double	t[2];
	t_ray	new_hit;

	b = vdot(ray->vec, vminus(e, sphere->coordinate));
	c = vlen2(vminus(e, sphere->coordinate)) - sphere->radius2;
	d = (b * b) - c;
	if (d < 0)
		return (0);
	t[0] = -b - sqrt(d);
	t[1] = -b + sqrt(d);

	if (t[0] * t[1] > 0)
	{
		if (t[0] < 0)
			return (0);
	}
	//여기는 하나는 음이고 하나는 양이거나
	// 둘다 양일때 넘어온다. 
	new_hit = make_hit_sphere(sphere, t, ray);
	
	return (update_hit(ray, new_hit));
}

int	is_ray_hit_plane(t_plane *plane, t_ray *ray, t_coordinate e)
{
	double	c_dot_n;
	double	d_dot_n;
	double	t;
	t_ray	new_hit;
	t_vec	c;

	c = vminus(plane->coordinate, e);
	c_dot_n = vdot(plane->n_vector, c);
	d_dot_n = vdot(plane->n_vector, ray->vec);
	if (d_dot_n == 0)
		return (0);
	t = c_dot_n / d_dot_n;
	if (t < 0)
		return (0);
	new_hit = make_hit_plane(plane, t, ray);
	return (update_hit(ray, new_hit));
}

int	is_ray_hit_cylinder(t_cylinder *cylinder, t_ray *ray, t_coordinate e)
{
	double	d_dot_v;
	double	c_dot_v;
	double	c_dot_d;
	double	c_dot_c;
	double	d;
	double	a;
	double	b;
	double	c;
	double	t[2];
	t_vec	cp;
	t_vec	v;
	t_vec	ce;
	double	cp_dot_v;
	double	top_plane_t;
	double	bottom_plane_t;
	t_vec	cp_top;
	t_vec	cp_bottom;
	double	mint;

	t_ray	new_hit;

	cylinder->top = 0;
	cylinder->bottom = 0;
	//ce = vmulti_f(cylinder->coordinate, -1.0);
	ce = vminus(e, cylinder->coordinate);
	v = vmulti_f(vunit(cylinder->n_vector), -1.0);
	d_dot_v = vdot(ray->vec, v);
	c_dot_v = vdot(ce, v);
	c_dot_d = vdot(ce, ray->vec);
	c_dot_c = vdot(ce, ce);
	a = d_dot_v * d_dot_v - 1;
	b = d_dot_v * c_dot_v - c_dot_d;
	c =	cylinder->radius2 - c_dot_c + (c_dot_v * c_dot_v);
	d = (b * b) - (a * c);
	if (d < 0)
		return (0);
	t[0] = (-b - sqrt(d)) / a;
	t[1] = (-b + sqrt(d)) / a;
	if (t[0] * t[1] > 0)
	{
		if (t[0] < 0)
			return (0);
		mint = fmin(t[0], t[1]);
		cp = vplus(ce, vmulti_f(ray->vec, mint));
	}
	else
	{
		mint = fmax(t[0], t[1]);
		cp = vplus(ce, vmulti_f(ray->vec, mint));
	}
	cp_dot_v = vdot(cp, v);
	if (cp_dot_v >= 0 && cp_dot_v <= cylinder->height)
	{
		new_hit = make_hit_cylinder(cylinder, mint, ray);
		return (update_hit(ray, new_hit));
	}
	if (d_dot_v)
	{
		top_plane_t = -c_dot_v / d_dot_v;
		cp_top = vplus(ce, vmulti_f(ray->vec, top_plane_t));
		bottom_plane_t = (cylinder->height - c_dot_v) / d_dot_v;
		cp_bottom = vplus(ce, vmulti_f(ray->vec, bottom_plane_t));
		if (vlen2(cp_top) <= cylinder->radius2)
			cylinder->top = 1;
		if (vlen2(cp_bottom) - (cylinder->height * cylinder->height) <= cylinder->radius2)
			cylinder->bottom = 1;

		// if (cylinder->top && cylinder->bottom)
		// {
		// 	// if (fmin(top_plane_t, bottom_plane_t) == top_plane_t)
		// 	if (fmax(top_plane_t, bottom_plane_t) == top_plane_t)
		// 	{
		// 		mint = top_plane_t;
		// 		cylinder->bottom = 0;
		// 	}
		// 	else
		// 	{
		// 		mint = bottom_plane_t;
		// 		cylinder->top = 0;
		// 	}	
		// 	new_hit = make_hit_cylinder(cylinder, mint, ray);
		// 	return (update_hit(ray, new_hit));
		// }
		// else 
		if (cylinder->top || cylinder->bottom)
		{
			if (t[0] * t[1] < 0)
			{	
				if (fmax(top_plane_t, bottom_plane_t) == top_plane_t)
				{
					mint = top_plane_t;
					cylinder->bottom = 0;
				}
				else
				{
					mint = bottom_plane_t;
					cylinder->top = 0;
				}	
				new_hit = make_hit_cylinder(cylinder, mint, ray);
				return (update_hit(ray, new_hit));
			}
			else
			{
				if (fmin(top_plane_t, bottom_plane_t) == top_plane_t)
				{
					mint = top_plane_t;
					cylinder->bottom = 0;
				}
				else
				{
					mint = bottom_plane_t;
					cylinder->top = 0;
				}	
				new_hit = make_hit_cylinder(cylinder, mint, ray);
				return (update_hit(ray, new_hit));
			}
		}
	}
	return (0);
}


