/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colours.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 16:13:06 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/19 18:13:49 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_colour(t_colour c)
{
	printf("r: %d, g: %d, b: %d a: %d\n", c.r, c.g, c.b, c.a);
}

uint32_t	reflection_result(t_colour colour1, t_colour colour2, float fraction)
{
	t_colour	result;

	result.r = colour1.r * (colour2.r / 255) * fraction;
	result.g = colour1.g * (colour2.g / 255) * fraction;
	result.b = colour1.b * (colour2.b / 255) * fraction;
	result.a = 0xff;
	return (result.rgba);
}

uint32_t	combine_colours(t_colour colour1, t_colour colour2)
{
	t_colour	result;

	result.r = colour1.r + (255 - colour1.r) * colour2.r / 255;
	result.g = colour1.g + (255 - colour1.g) * colour2.g / 255;
	result.b = colour1.b + (255 - colour1.b) * colour2.b / 255;
	result.a = 0xff;
	return (result.rgba);
}
