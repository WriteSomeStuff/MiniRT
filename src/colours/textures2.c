/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/16 13:02:22 by cschabra      #+#    #+#                 */
/*   Updated: 2024/08/16 13:03:28 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	cone_tex(void *coneptr, t_hit *col)
{
	(void)col;
	return (((t_cone *)coneptr)->colour);
}

t_vec	cylinder_tex(void *cylptr, t_hit *col)
{
	(void)col;
	return (((t_cylinder *)cylptr)->colour);
}

t_vec	disc_tex(void *discptr, t_hit *col)
{
	(void)col;
	return (((t_disc *)discptr)->colour);
}
