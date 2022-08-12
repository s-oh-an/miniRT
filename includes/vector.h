

#ifndef VECTOR_H
# define VECTOR_H

# include <stdio.h>
# include <math.h>
# include "scene.h"

# define PI 3.141592

t_coordinate	init_vec(float x, float y, float z);
t_coordinate	init_point(float x, float y, float z);
t_color			init_color(float x, float y, float z);
void			set_vec(t_coordinate *vec, float x, float y, float z);
float			vec_len_squared(t_coordinate vec);
float			vec_len(t_coordinate vec);
t_coordinate	vec_op_plus_vec(t_coordinate vec1, t_coordinate vec2);
t_coordinate	vec_op_plus_element(t_coordinate vec1, float x, float y, float z);
t_coordinate	vec_op_minus_vec(t_coordinate vec1, t_coordinate vec2);
t_coordinate	vec_op_minus_element(t_coordinate vec1, float x, float y, float z);
t_coordinate	vec_op_multi_double(t_coordinate vec, float t);
float			vec_op_dotproduct(t_coordinate vec1, t_coordinate vec2);
t_coordinate	vec_op_crossproduct(t_coordinate vec1, t_coordinate vec2);
t_coordinate	vec_op_unit(t_coordinate vec);
t_vec			vdivide(t_vec vec, float t);


#endif