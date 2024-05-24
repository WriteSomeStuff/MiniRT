/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colours.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 16:13:06 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/24 16:39:25 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint32_t	ambient_colour(const t_vec obj_colour, const t_vec ambient)
{
	return (percentage_to_rgba(reflection_result(obj_colour, ambient, 1)));
}

t_vec	reflection_result(const t_vec c1, const t_vec c2, float fraction)
{
	t_vec	result;

	result.r = c1.r * c2.r * fraction;
	result.g = c1.g * c2.g * fraction;
	result.b = c1.b * c2.b * fraction;
	return (result);
}

t_vec	combine_colours(const t_vec c1, const t_vec c2)
{
	t_vec	result;

	result.r = c1.r + (1 - c1.r) * c2.r;
	result.g = c1.g + (1 - c1.g) * c2.g;
	result.b = c1.b + (1 - c1.b) * c2.b;
	return (result);
}

uint32_t	percentage_to_rgba(const t_vec f)
{
	return (ft_pixel(f.r * 255, f.g * 255, f.b * 255, 0xff));
}

void	rgb_to_floats(t_vec *rgb)
{
	rgb->r /= 255;
	rgb->g /= 255;
	rgb->b /= 255;
}
