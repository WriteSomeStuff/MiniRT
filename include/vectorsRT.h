/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectorsRT.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/09 11:39:12 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/04/15 11:05:57 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORSRT_H
# define VECTORSRT_H

# include "miniRT.h"
# include "structsRT.h"
# include <MLX42/MLX42.h>

/*	3D vectors	*/
/*	------------------------------------------------------------------	*/
float		dot(const t_vec *a, const t_vec *b);
t_vec		cross_product(const t_vec *a, const t_vec *b);

float		angle(const t_vec *a, const t_vec *b);
bool		quadratic_equation(const t_vec *vec, float *result);

float		vector_length(const t_vec *origin, const t_vec *vector);
t_vec		normalize_vector(const t_vec *vector);
float		q_sqrt(float num);
t_vec		scale_vector(const t_vec *vector, float scalar);
void		set_vector(t_vec *vector, const t_vec *location1, const t_vec *location2);

void		print_vector(t_vec vector);
t_vec		create_vector(t_data *data, char *info);
/*	------------------------------------------------------------------	*/

/*	Quaternions	*/
/*	------------------------------------------------------------------	*/
void		print_quat(t_quat quat);
t_vec		quat_to_vector(t_quat quat);
t_quat		vector_to_quat(t_vec vector);

void		rotate_point(t_vec *point, t_quat *rotation);
/*	------------------------------------------------------------------	*/

#endif
