
#include "../../includes/hit.h"
#include "../../includes/vector.h"
#include <math.h>



//(1을 리턴 -> 판별식함수가 1을 리턴하는 곳이 이 함수를 사용 )
int	update_hit(t_ray *ray, t_ray new)
{
	if (ray->hit.t > new.hit.t)	// - + 일떄는 + 값이 교점 
	{
		*ray = new;
	}
	return (1);
}


//sphere
t_ray	make_hit_sphere(t_sphere *sphere, float *t, t_ray *ray)
{
	t_ray	new;

	new.vec = ray->vec;

	if (t[0] * t[1] < 0)
		new.hit.t = t[1];
	else
		new.hit.t = t[0];

	new.hit.hit_point = vmulti_f(new.vec, new.hit.t);
	new.hit.hit_color = sphere->color;
	new.hit.hit_normal = vunit(vminus(new.hit.hit_point, sphere->coordinate));
	if (vdot(ray->vec, new.hit.hit_normal) <= 0)
		new.hit.in_object = 0;
	else 
		new.hit.in_object = 1;
	////// 내적이 0일떄는??/??
	// 1. 접할 때 -> 밖, 0

	new.hit.min = 0;

	// ㅇ것도 update_hit에서 정할거
	new.hit.ray_hit = 1;
	return (new);
}

t_ray	make_hit_plane(t_plane *plane, float t, t_ray *ray)
{
	t_ray	new;

	new.vec = ray->vec;

	new.hit.t = t;

	new.hit.hit_point = vmulti_f(new.vec, new.hit.t);
	
	new.hit.hit_color = plane->color;

	new.hit.hit_normal = vunit(plane->n_vector);

	if (vdot(ray->vec, new.hit.hit_normal) <= 0)
		new.hit.in_object = 0;
	else 
		new.hit.in_object = 1;
	////// 내적이 0일떄는??/??
	// 1. 접할 때 -> 밖, 0

	new.hit.min = 0;

	// ㅇ것도 update_hit에서 정할거
	//new.hit.ray_hit = 0;
	return (new);
}

t_ray	make_hit_cylinder(t_cylinder *cylinder, float *t, t_ray *ray)
{
	t_ray	new;
	t_vec	r_n_vector;

	new.vec = ray->vec;
	if (t[0] * t[1] < 0)
		new.hit.t = t[1];
	else
		new.hit.t = t[0];
	new.hit.hit_point = vmulti_f(new.vec, new.hit.t);	
	new.hit.hit_color = cylinder->color;
	r_n_vector = vmulti_f(cylinder->n_vector, -1.0);

	// t_vec cp = vminus(new.hit.hit_point, cylinder->coordinate);
	// float dot = vdot(cp, r_n_vector);
	// t_vec dot_multi_rnvector = vmulti_f(r_n_vector, dot);
	// t_vec final = vminus(cp, dot_multi_rnvector);
	new.hit.hit_normal = vunit(vminus(vminus(new.hit.hit_point, cylinder->coordinate), 
									vmulti_f(r_n_vector, vdot(vminus(new.hit.hit_point, 
									cylinder->coordinate), r_n_vector))));

	if (vdot(ray->vec, new.hit.hit_normal) <= 0)
		new.hit.in_object = 0;
	else 
		new.hit.in_object = 1;
	////// 내적이 0일떄는??/??
	// 1. 접할 때 -> 밖, 0
	new.hit.min = 0;
	// ㅇ것도 update_hit에서 정할거
	new.hit.ray_hit = 1;

	return (new);
}