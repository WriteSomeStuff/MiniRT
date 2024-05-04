/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectorsRT.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/09 11:39:12 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/05/04 14:18:24 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORSRT_H
# define VECTORSRT_H

# include "miniRT.h"
# include "structsRT.h"
# include <MLX42/MLX42.h>

/*	3D vectors	*/
/*	------------------------------------------------------------------	*/
t_vec		vec(float x, float y, float z);
float		dot(const t_vec a, const t_vec b);
t_vec		cross(const t_vec a, const t_vec b);

float		angle(const t_vec a, const t_vec b);
bool		quadratic_equation(const t_vec *vec, float *low, float *high);

float		vector_length(const t_vec origin, const t_vec vector);
t_vec		normalize_vector(const t_vec vector);
float		inv_sqrt(float num);
t_vec		norm_vec(t_vec vec);
void		set_vector(t_vec *vector, const t_vec *location1, const t_vec *location2);

void		print_vector(t_vec vector);
t_vec		create_vector(t_data *data, char *info);
/*	------------------------------------------------------------------	*/

/*	Quaternions	*/
/*	------------------------------------------------------------------	*/
void		print_quat(t_quat quat);
t_quat		quat(float real, float x, float y, float z);

void		rotate(t_vec *point, t_quat rotation);

t_vec		reflect(const t_vec incoming, const t_vec normal);
/*	------------------------------------------------------------------	*/

#endif
