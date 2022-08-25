#include "../../includes/vector.h"
#include <math.h>


t_vec	vec3(double x, double y, double z)
{
	t_vec vec;
	
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

double	vlen2(t_vec vec)
{
	long double	len;

	len = (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	if (len > 1.7976931348623157E+308)
	{
		ft_putendl_fd("Error\ninvalid location\nexiting...", 2);
		// system("leaks miniRT");
		exit(1);
	}
	return (len);
}

double	vlen(t_vec vec)
{
	double len;

	len = sqrt(vlen2(vec));
	return (len);
}

t_vec	vplus(t_vec vec1, t_vec vec2)
{
	vec1.x = vec1.x + vec2.x;
	vec1.y = vec1.y + vec2.y;
	vec1.z = vec1.z + vec2.z;
	return (vec1);
}

t_vec	vplus_f(t_vec vec1, double x, double y, double z)
{
	vec1.x = vec1.x + x;
	vec1.y = vec1.y + y;
	vec1.z = vec1.z + z;
	return (vec1);
}


