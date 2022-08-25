/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:41:56 by sohan             #+#    #+#             */
/*   Updated: 2022/08/25 19:13:01 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/scene.h"
#include "../../includes/ray.h"
#include "../../includes/hit.h"
#include "../../includes/vector.h"

int	update_hit(t_ray *old, t_hit new)
{
	if (old->hit.t > new.t)
		old->hit = new;
	return (1);
}

t_hit	make_hit_sphere(t_sphere *sphere, double *t, t_ray *ray)
{
	t_hit	hit;

	if (t[0] * t[1] < -E)
		hit.t = t[1];
	else
		hit.t = t[0];
	hit.point = vmulti_f(ray->direction, hit.t);
	hit.color = sphere->color;
	hit.normal = vunit(vminus(hit.point, sphere->coordinate));
	if ((vdot(ray->direction, hit.normal) < E))
		hit.in_object = 0;
	else
	{
		hit.in_object = 1;
		hit.normal = vmulti_f(hit.normal, -1);
	}
	return (hit);
}

t_hit	make_hit_plane(t_plane *plane, double t, t_ray *ray)
{
	t_hit	hit;

	hit.t = t;
	hit.point = vmulti_f(ray->direction, hit.t);
	hit.color = plane->color;
	hit.normal = vunit(plane->n_vector);
	if (vdot(ray->direction, hit.normal) < E)
		hit.in_object = 0;
	else
	{
		hit.in_object = 1;
		hit.normal = vmulti_f(hit.normal, -1);
	}
	return (hit);
}

t_hit	make_hit_cylinder_cover(t_cylinder *cylinder, double t, t_ray *ray)
{
	t_hit	hit;
	t_vec	r_n_vector;

	hit.t = t;
	hit.point = vmulti_f(ray->direction, hit.t);
	hit.color = cylinder->color;
	r_n_vector = vunit(vmulti_f(cylinder->n_vector, -1.0));
	if (cylinder->top)
		hit.normal = vunit(cylinder->n_vector);
	else
		hit.normal = r_n_vector;
	if (vdot(ray->direction, hit.normal) < E)
		hit.in_object = 0;
	else
	{
		hit.in_object = 1;
		hit.normal = vmulti_f(hit.normal, -1);
	}
	return (hit);
}

t_hit	make_hit_cylinder(t_cylinder *cylinder, double t, t_ray *ray)
{
	t_hit	hit;
	t_vec	r_n_vector;
	t_vec	cp;
	t_vec	ccp;

	hit.t = t;
	hit.point = vmulti_f(ray->direction, hit.t);
	hit.color = cylinder->color;
	r_n_vector = vmulti_f(vunit(cylinder->n_vector), -1);
	cp = vminus(hit.point, cylinder->coordinate);
	ccp = vmulti_f(r_n_vector, vdot(r_n_vector, cp));
	hit.normal = vunit(vminus(cp, ccp));
	if (vdot(ray->direction, hit.normal) < E)
		hit.in_object = 0;
	else
	{	
		hit.in_object = 1;
		hit.normal = vmulti_f(hit.normal, -1);
	}
	return (hit);
}
