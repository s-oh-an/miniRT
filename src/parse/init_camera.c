#include "../../includes/camera.h"
#include "../../includes/vector.h"
#include <math.h>

#include <stdio.h>

void	camera(t_camera *camera)
{
	camera->win.width = 1280;
	camera->win.height = 720;
	camera->win.ratio = (double)camera->win.width / (double)camera->win.height;
	camera->viewport_h = 2.0;
	camera->viewport_w = camera->viewport_h * (camera->win.ratio);
	camera->focal_len = 1.0 / tan((camera->fov / 2) * (M_PI / 180));	
	//camera->ver = vmulti_f(camera->x, camera->viewport_w);
	//camera->hor = vmulti_f(camera->y, camera->viewport_h);
	//o = vec3(0, 0, 0);
	//camera->left_bottom = vminus(vminus(vminus(o, vmulti_f(camera->ver, 0.5)),
	//								vmulti_f(camera->hor, 0.5)),
	//								vmulti_f(camera->z, camera->focal_len));
	camera->left_bottom = vec3(-camera->viewport_w / 2, -camera->viewport_h / 2, -camera->focal_len);
									//printf("left_bottom x: %f y: %f z: %f\n", camera->left_bottom.x, camera->left_bottom.y, camera->left_bottom.z);
	// camera->orig = vplus(camera->orig, vmulti_f(vunit(camera->n_vector), 1e-6));
}
