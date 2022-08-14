#ifndef VECTOR_H
# define VECTOR_H

# include "scene.h"

t_vec	vec3(float x, float y, float z);
t_vec	init_point(float x, float y, float z);
t_color	init_color(float x, float y, float z);
void	set_vec(t_vec *vec, float x, float y, float z);
float	vlen2(t_vec vec);
float	vlen(t_vec vec);
t_vec	vplus(t_vec vec1, t_vec vec2);
t_vec	vplus_f(t_vec vec1, float x, float y, float z);
t_vec	vminus(t_vec vec1, t_vec vec2);
t_vec	vminus_f(t_vec vec1, float x, float y, float z);
t_vec	vmulti_f(t_vec vec, float t);
float	vdot(t_vec vec1, t_vec vec2);
t_vec	vcross(t_vec vec1, t_vec vec2);
t_vec	vunit(t_vec vec);
t_vec	vdiv(t_vec vec, float t);

#endif
