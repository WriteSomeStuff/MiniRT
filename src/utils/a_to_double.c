/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   a_to_double.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/03 18:52:12 by vincent       #+#    #+#                 */
/*   Updated: 2024/03/04 18:17:02 by vvan-der      ########   odam.nl         */
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

static int	check_input(t_data *data, const char *str, double *c, int i)
{
	if (ft_strlen(str) >= 15)
		exit_error(data, ": number doesn't fit in a double");
	if (str[i] == '-')
	{
		*c *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		i++;
		if (str[i] == '.')
		{
			i++;
			break ;
		}
	}
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		exit_error(data, ": non-numerical input");
	return (i);
}

double	a_to_double(t_data *data, const char *str)
{
	double	res;
	double	c;
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
		}
	}
	return (res);
}
