/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maths.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 17:28:37 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/08 18:09:14 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	length(double x, double y)
{
	return (fabs(x - y));
}

double	pythagoras(double a, double b)
{
	return (sqrt(a * a + b * b));
}

double	pythagoras_3d(t_vec a, t_vec b)
{
	double	c;

	c = pythagoras(length(a.x, b.x), length(a.y, b.y));
	return (pythagoras(c, length(a.z, b.z)));
}
