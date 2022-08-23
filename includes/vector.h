#ifndef VECTOR_H
# define VECTOR_H

# include "scene.h"

t_vec	vec3(double x, double y, double z);
t_vec	init_point(double x, double y, double z);
t_color	init_color(double x, double y, double z);
void	set_vec(t_vec *vec, double x, double y, double z);
double	vlen2(t_vec vec);
double	vlen(t_vec vec);
t_vec	vplus(t_vec vec1, t_vec vec2);
t_vec	vplus_f(t_vec vec1, double x, double y, double z);
t_vec	vminus(t_vec vec1, t_vec vec2);
t_vec	vminus_f(t_vec vec1, double x, double y, double z);
t_vec	vmulti_f(t_vec vec, double t);
t_vec	vmulti(t_vec vec1, t_vec vec2);
double	vdot(t_vec vec1, t_vec vec2);
t_vec	vcross(t_vec vec1, t_vec vec2);
t_vec	vunit(t_vec vec);
t_vec	vdiv(t_vec vec, double t);
t_vec	vmin(t_vec vec1, t_vec vec2);
t_vec	vmax(t_vec vec1, t_vec vec2);
int	small_than_eps(double d);

#endif
