/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohan <sohan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:48:53 by sohan             #+#    #+#             */
/*   Updated: 2022/08/25 18:48:54 by sohan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"
#include "../../lib/libft/libft.h"
#include <math.h>

int	is_expo(char const **str, long double *ret)
{
	int	digit;

	digit = 0;
	while (ft_isdigit(**str) && **str)
	{
		*ret = (*ret * 10) + **str - '0';
		++*str;
		++digit;
		if (digit > 14)
			error_exit("Error\nExceeds Significant Digits Limit");
	}
	return (digit);
}

void	is_frac(char const **str, long double *ret, int digit)
{
	int	digit_decimal;

	digit_decimal = 0;
	while (ft_isdigit(**str) && **str)
	{
		++digit_decimal;
		*ret += (**str - '0') * pow(10, -digit_decimal);
		++*str;
		++digit;
		if (digit > 14)
			error_exit("Error\nExceeds Significant Digits Limit");
	}
}

double	ft_stof(char const *str)
{
	long double	ret;
	int			digit;
	int			sign;

	ret = 0;
	sign = 1;
	while (ft_isspace(*str) && *str)
		++str;
	sign += -2 * (*str == '-');
	if (*str == '-' || *str == '+')
		++str;
	digit = is_expo(&str, &ret);
	if (*str != '\0' && *str != '.')
		error_exit("Error\nNot a Number");
	if (*str == '.')
		++str;
	is_frac(&str, &ret, digit);
	if (*str != '\0')
		error_exit("Error\nNot a Number");
	return (sign * ret);
}
