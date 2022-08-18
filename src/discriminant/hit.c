
#include "../../includes/hit.h"
#include "../../includes/vector.h"
#include <math.h>



//(1을 리턴 -> 판별식함수가 1을 리턴하는 곳이 이 함수를 사용 )
int	update_hit_sphere(t_sphere *sphere, t_ray *ray, t_ray new_hit)
{
	if ()	// - + 일떄는 + 값이 교점 
	{
		new_hit.hit.t = fminf(t[0], t[1]);

	}

}

int	update_hit_plane(t_plane *plane, t_ray *ray, float *t)
{

}

int	update_hit_cylinder(t_cylinder *cylinder, t_ray *ray, float *t)
{

}


//sphere
t_ray	make_hit(float *t, t_ray *ray, t_coordinate center)
{
	t_ray	new_hit;

	new_hit.vec = ray->vec;

	if (t[0] * t[1] < 0)
		new_hit.hit.t = t[1];
	else
		new_hit.hit.t = t[0];

	new_hit.hit.hit_point = vmulti_f(new_hit.vec, new_hit.hit.t);
	
	// color는 update_hit_ 에서 넣도록 하자 
	// new_hit.hit.hit_color = 

	new_hit.hit.hit_normal = vunit(vminus(new_hit.hit.hit_point, center));

	if (vdot(ray->vec, new_hit.hit.hit_normal) < 0)
		new_hit.hit.in_object = 0;
	else 
		new_hit.hit.in_object = 1;
	////// 내적이 0일떄는??/??

	new_hit.hit.min = 0;
	// ㅇ것도 update_hit에서 정할거
	//new_hit.hit.ray_hit = 0;
	return (new_hit);
}