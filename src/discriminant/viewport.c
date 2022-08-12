
# include "../../includes/discriminant.h"

//카메라 생성자




// 캔버스 생성자 
t_window	window(int width, int height)
{
	t_window	window;

	window.width = width;
	window.height = height;
	window.ratio = width / height; // float을 어디에 붙여서 형변환해야하는지 
	return (window);
}

t_camera	camera(t_coordinate point_w, float fov, t_window window)
{
	t_camera	camera;

	camera.coordinate = point_w;
	camera.n_vector = vec_op_unit(point_w);
	camera.fov = fov;
	camera.viewport_h = 2.0 * tan((fov / 2) * (PI / 180));
	camera.viewport_w = camera.viewport_h * window.ratio;
	camera.hori_vec = init_vec(camera.viewport_w, 0, 0);
	camera.vert_vec = init_vec(camera.viewport_h, 0, 0);
	camera.focal_len = 1.0;
	// point_w - (OQ + QM + MB) = point_w - (OB)
	camera.left_bottom = vec_op_minus_vec(point_w, vec_op_plus_element(vec_op_plus_vec(vdivide(camera.hori_vec, 2.0),vdivide(camera.hori_vec, 2.0)), 0, 0, 1));
	return (camera);
}


// t_ray	**set_view_pixel_point(t_ray **ray, int size, float len)
// {
// 	int	h;
// 	int	v;

// 	len = len / 2;
// 	h = 0;
// 	while (h < size)
// 	{
// 		v = 0;
// 		while (v < size)
// 		{
// 			ray[h][v].dir_pixel.point = init_vec(-len + 0.5 + v, -len + 0.5 + h, -1);
// 			ray[h][v].unit_vec = vec_op_unit(ray[h][v].dir_pixel.point);
// 			v++;
// 		}
// 		h++;
// 	}
// 	return (ray);
// }

// // fov를 받아서 viewport의 높이너비를 구하고 크기가 1인 pixel의 개수를 구해서 
// // 개수만큼 ray(ray한개당pixel을 하나 가짐)배열을 할당받고 
// t_ray	**arr_view_pixel(int size, float len)
// {
// 	int		i;
// 	t_ray	**ray;

// 	ray = (t_ray **)malloc(sizeof(t_ray *) * size);
// 	if (!ray)
// 		return (NULL);
// 	i = 0;
// 	while (i < size)
// 	{
// 		ray[i] = (t_ray *)malloc(sizeof(t_ray) * size);
// 		if (!ray[i])
// 			return (NULL);
// 		i++;
// 	}
// 	i = 0;
// 	ray = set_view_pixel_point(ray, size, len);
// 	return (ray);
// }

// //pixel의 좌표와 ray의 단위벡터를 구한다. 
// t_ray	**find_view_pixel(float fov) // 외부사용함수 
// {
// 	t_ray	**ray;
// 	float	len_viewp;
// 	int		size;

// 	len_viewp = 2 * tan((fov / 2) * (PI / 180));
// 	size = (int)(len_viewp - 1);
// 	ray = arr_view_pixel(size, len_viewp);
// 	return (ray);
// }
