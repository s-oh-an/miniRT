

#ifndef VECTOR_H
# define VECTOR_H

# include "math.h"
# include <stdio.h>


typedef struct s_vec	t_vec;
typedef struct s_vec	t_point;
typedef struct s_vec	t_color;

struct s_vec
{
	float	x;
	float	y;
	float	z;
};

t_vec	init_vec(float x, float y, float z);
t_point	init_point(float x, float y, float z);
t_color	init_color(float x, float y, float z);
void	set_vec(t_vec *vec, float x, float y, float z);
float	vec_len_squared(t_vec vec);
float	vec_len(t_vec vec);
t_vec	vec_op_plus_vec(t_vec vec1, t_vec vec2);
t_vec	vec_op_plus_element(t_vec vec1, float x, float y, float z);
t_vec	vec_op_minus_vec(t_vec vec1, t_vec vec2);
t_vec	vec_op_minus_element(t_vec vec1, float x, float y, float z);
t_vec	vec_op_multi_double(t_vec vec, float t);
float	vec_op_dotproduct(t_vec vec1, t_vec vec2);
t_vec	vec_op_crossproduct(t_vec vec1, t_vec vec2);
t_vec	vec_op_unit(t_vec vec);


#endif