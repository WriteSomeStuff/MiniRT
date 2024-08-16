/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   a_to_float.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/03 18:52:12 by vincent       #+#    #+#                 */
/*   Updated: 2024/03/08 15:54:50 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	ft_pow_fl(double number, int power)
{
	double	x;

	x = number;
	if (power == 0)
		return ((double)1);
	while (power > 1)
	{
		x *= number;
		power--;
	}
	return (x);
}

static int	check_input(t_data *data, const char *str, float *c, int i)
{
	if (ft_strlen(str) >= 9 || str[i] == '\0')
		exit_error(data, ": invalid input number");
	if (str[i] == '-')
	{
		*c *= -1;
		i++;
	}
	if (ft_isdigit(str[i]) == false)
		exit_error(data, ": invalid input number");
	while (ft_isdigit(str[i]))
	{
		i++;
		if (str[i] == '.')
		{
			i++;
			if (str[i] == '\0' || ft_strlen(&str[i]) > 7)
				exit_error(data, ": too much input after decimal point");
			break ;
		}
	}
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		exit_error(data, ": non-numerical input");
	return (i);
}

static void	check_result(t_data *data, double result)
{
	if (result > INT_MAX || result < INT_MIN)
		exit_error(data, ": input larger than integer values");
}

float	a_to_float(t_data *data, const char *str)
{
	double	res;
	float	c;
	int		i;

	res = 0;
	c = 1;
	i = check_input(data, str, &c, 0);
	while (i > 0)
	{
		i--;
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return (res);
		if (str[i] == '.')
		{
			res /= (ft_pow_fl(10, ft_strlen(&str[i]) - 1));
			c /= (ft_pow_fl(10, ft_strlen(&str[i]) - 1));
		}
		else
		{
			res += (str[i] - '0') * c;
			c *= 10.0;
			check_result(data, res);
		}
	}
	return ((float)res);
}
