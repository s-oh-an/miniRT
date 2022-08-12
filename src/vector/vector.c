

# include "../../includes/vector.h"

t_coordinate	init_vec(float x, float y, float z)
{
	t_coordinate vec;
	
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_coordinate	init_point(float x, float y, float z)
{
	t_coordinate point;
	
	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

t_color	init_color(float x, float y, float z)
{
	t_color color;
	
	color.x = x;
	color.y = y;
	color.z = z;
	return (color);
}

void	set_vec(t_coordinate *vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

// 벡터 길이 제곱
float	vec_len_squared(t_coordinate vec)
{
	float	len;

	len = (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return (len);
}

float	vec_len(t_coordinate vec)
{
	float len;

	len = sqrt(vec_len_squared(vec));
	return (len);
}

// 벡터 덧셈
t_coordinate	vec_op_plus_vec(t_coordinate vec1, t_coordinate vec2)
{
	vec1.x = vec1.x + vec2.x;
	vec1.y = vec1.y + vec2.y;
	vec1.z = vec1.z + vec2.z;
	return (vec1);
}

t_coordinate	vec_op_plus_element(t_coordinate vec1, float x, float y, float z)
{
	vec1.x = vec1.x + x;
	vec1.y = vec1.y + y;
	vec1.z = vec1.z + z;
	return (vec1);
}

// 벡터 뺼셈
t_coordinate	vec_op_minus_vec(t_coordinate vec1, t_coordinate vec2)
{
	vec1.x = vec1.x - vec2.x;
	vec1.y = vec1.y - vec2.y;
	vec1.z = vec1.z - vec2.z;
	return (vec1);
}

t_coordinate	vec_op_minus_element(t_coordinate vec1, float x, float y, float z)
{
	vec1.x = vec1.x - x;
	vec1.y = vec1.y - y;
	vec1.z = vec1.z - z;
	return (vec1);
}

// 벡터 곱셈
t_coordinate	vec_op_multi_float(t_coordinate vec, float t)
{
	vec.x = vec.x * t;
	vec.y = vec.y * t;
	vec.z = vec.z * t;
	return (vec);	
}

// // 벡터 축 값끼리 곱연산
// t_vec3      vmult_(t_vec3 vec, t_vec3 vec2)
// {
//     vec.x *= vec2.x;
//     vec.y *= vec2.y;
//     vec.z *= vec2.z;
//     return (vec);
// }

// 벡터 스칼라 나누기
t_vec	vdivide(t_vec vec, float t)
{
	vec.x = vec.x * (1 / t);
	vec.y = vec.y * (1 / t);
	vec.z = vec.z * (1 / t);

	return (vec);
}

// 벡터 product
float	vec_op_dotproduct(t_coordinate vec1, t_coordinate vec2)
{
	float	res;

	res = (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
	return (res);
}

t_coordinate	vec_op_crossproduct(t_coordinate vec1, t_coordinate vec2)
{
	t_coordinate	res;

	res.x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
	res.y = (vec1.x * vec2.z) - (vec1.z * vec2.x);
	res.z = (vec1.x * vec2.y) - (vec1.y * vec2.x);
	return (res);
}

// 벡터 표준화 
t_coordinate	vec_op_unit(t_coordinate vec)
{
	t_coordinate	unit;
	float	len;

	len = vec_len(vec);
	if (len == 0)
	{
		printf("length of vector is 0");
		return (vec); // -> 교과서는 exit으로 처리 ㄴ
	}
	unit.x = vec.x / len;
	unit.y = vec.y / len;
	unit.z = vec.z / len;
	return (unit);
}

// 벡터 원소 비교하는 건데 이것도 왜 하는지는 아직 모르겠음 
// // 두 벡터의 원소를 비교하여 작은 값들만 반환
// t_vec3  vmin(t_vec3 vec1, t_vec3 vec2)
// {
//     if (vec1.x > vec2.x)
//         vec1.x = vec2.x;
//     if (vec1.y > vec2.y)
//         vec1.y = vec2.y;
//     if (vec1.z > vec2.z)
//         vec1.z = vec2.z;
//     return (vec1);
// }
