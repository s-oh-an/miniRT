/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   discriminant_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:47:05 by sohan             #+#    #+#             */
/*   Updated: 2022/08/25 19:14:23 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/scene.h"
#include "../../includes/ray.h"
#include "../../includes/discriminant.h"
#include "../../includes/vector.h"
#include "../../includes/hit.h"
#include <math.h>

static void	calc_t_of_cover(t_cylinder *cy, t_ray *ray)
{
	t_vec	cp_top;
	t_vec	cp_bottom;

	cy->top = 0;
	cy->bottom = 0;
	cy->tcc.top_t = -cy->tcc.c_dot_v / cy->tcc.d_dot_v;
	cp_top = vplus(cy->tcc.ce, vmulti_f(ray->direction, cy->tcc.top_t));
	cy->tcc.bottom_t = (cy->height - cy->tcc.c_dot_v) / cy->tcc.d_dot_v;
	cp_bottom = vplus(cy->tcc.ce, vmulti_f(ray->direction, cy->tcc.bottom_t));
	if (vlen2(cp_top) < cy->radius2 + E)
		cy->top = 1;
	if ((vlen2(cp_bottom) - (cy->height * cy->height)
			< cy->radius2 + E))
		cy->bottom = 1;
}

int	is_ray_hit_cylinder_cover(t_cylinder *cylinder, t_ray *ray)
{
	double		mint;
	t_hit		new;

	if (cylinder->tcc.d_dot_v < -E || cylinder->tcc.d_dot_v > E)
	{
		calc_t_of_cover(cylinder, ray);
		if (cylinder->tcc.top_t < -E && cylinder->tcc.bottom_t < -E)
			return (0);
		if (cylinder->top && cylinder->bottom)
		{
			if (cylinder->tcc.top_t * cylinder->tcc.bottom_t < -E)
				mint = fmax(cylinder->tcc.top_t, cylinder->tcc.bottom_t);
			else
				mint = fmin(cylinder->tcc.top_t, cylinder->tcc.bottom_t);
		}
		else if (cylinder->top && cylinder->tcc.top_t > -E)
			mint = cylinder->tcc.top_t;
		else if (cylinder->bottom && cylinder->tcc.bottom_t > -E)
			mint = cylinder->tcc.bottom_t;
		else
			return (0);
		new = make_hit_cylinder_cover(cylinder, mint, ray);
		return (update_hit(ray, new));
	}
	return (0);
}

static int	discriminant_cylinder_side(t_cylinder *cy, t_ray *ray)
{
	double	d;
	double	a;
	double	b;
	double	c;

	a = cy->tcc.d_dot_v * cy->tcc.d_dot_v - 1;
	b = cy->tcc.d_dot_v * cy->tcc.c_dot_v - vdot(cy->tcc.ce, ray->direction);
	c = cy->radius2 - vlen2(cy->tcc.ce) + (cy->tcc.c_dot_v * cy->tcc.c_dot_v);
	d = (b * b) - (a * c);
	if (d < -E)
		return (0);
	cy->tcc.t[0] = (-b - sqrt(d)) / a;
	cy->tcc.t[1] = (-b + sqrt(d)) / a;
	return (1);
}

static void	init_calc_cylinder(t_cylinder *cylinder, t_ray *ray)
{
	cylinder->tcc.ce = vminus(ray->origin, cylinder->coordinate);
	cylinder->tcc.v = vmulti_f(vunit(cylinder->n_vector), -1.0);
	cylinder->tcc.d_dot_v = vdot(ray->direction, cylinder->tcc.v);
	cylinder->tcc.c_dot_v = vdot(cylinder->tcc.ce, cylinder->tcc.v);
}

int	is_ray_hit_cylinder(t_cylinder *cylinder, t_ray *ray)
{
	t_vec	cp;
	double	cp_dot_v;
	double	mint;
	t_hit	new;

	init_calc_cylinder(cylinder, ray);
	if (!discriminant_cylinder_side(cylinder, ray))
		return (0);
	if (cylinder->tcc.t[0] * cylinder->tcc.t[1] > E)
	{
		if (cylinder->tcc.t[0] < -E)
			return (0);
		mint = fmin(cylinder->tcc.t[0], cylinder->tcc.t[1]);
	}
	else
		mint = fmax(cylinder->tcc.t[0], cylinder->tcc.t[1]);
	cp = vplus(cylinder->tcc.ce, vmulti_f(ray->direction, mint));
	cp_dot_v = vdot(cp, cylinder->tcc.v);
	if (cp_dot_v > -E && cp_dot_v < cylinder->height + E)
	{
		new = make_hit_cylinder(cylinder, mint, ray);
		return (update_hit(ray, new));
	}
	return (0);
}
