#include "../../includes/utils.h"

//int	trans_trgb(t_color color)
int	to_rgb(t_color color)
{
	int	trgb;

	trgb = (int)color.x;
	trgb = trgb << 8;
	trgb = trgb | (int)color.y;
	trgb = trgb << 8;
	trgb = trgb | (int)color.z;
	return (trgb);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		++i;
	}
	free(array);
}

// int	err_exit(int err_code, char *str)
// {
// 	perror(str);

// 	exit(err_code);
// }