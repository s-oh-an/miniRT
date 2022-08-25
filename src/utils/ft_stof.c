#include "../../includes/utils.h"
#include "../../lib/libft/libft.h"
#include <math.h>

double	ft_stof(char const *str)
{
	long double	ret;
	int			digit;
	int			digit_decimal;
	int			sign;

	ret = 0;
	digit = 0;
	digit_decimal = 0;
	sign = 1;
	while (ft_isspace(*str) && *str)
		++str;
	sign += -2 * (*str == '-');
	if (*str == '-' || *str == '+')
		++str;
	while (ft_isdigit(*str) && *str)
	{
		ret  = (ret * 10) + *str - '0';
		++str;
		++digit;
		if (digit > 14)
		{
			ft_putendl_fd("Error\nExceeds Significant Digits Limit", 2);
			exit(1);
		}
	}
	if (*str != '\0' && *str != '.')
	{
		ft_putendl_fd("Error\nNot a Number", 2);
		exit(1);
	}
	if (*str == '.')
		++str;
	while (ft_isdigit(*str) && *str)
	{
		++digit_decimal;
		ret +=  (*str - '0') * pow(10, -digit_decimal);
		++str;
		++digit;
		if (digit > 14)
		{
			ft_putendl_fd("Error\nExceeds Significant Digits Limit", 2);
			exit(1);
		}
	}
	if (*str != '\0')
	{
		ft_putendl_fd("Error\nNot a Number", 2);
		exit(1);
	}
	return (sign * ret);
}
