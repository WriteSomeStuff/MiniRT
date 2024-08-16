/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectorsRT.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/09 11:39:12 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/08/16 15:04:56 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORSRT_H
# define VECTORSRT_H

# include "miniRT.h"
# include "structsRT.h"

/*	3D vectors	*/
/*	------------------------------------------------------------------	*/
float		prn(uint32_t *id);
t_vec		vec(float x, float y, float z);
t_vec		inverted(t_vec vector);
float		dot(const t_vec a, const t_vec b);
t_vec		cross(const t_vec a, const t_vec b);
float		angle(const t_vec a, const t_vec b);
bool		quadratic_equation(const t_vec *vec, float *low, float *high);
float		vector_length(const t_vec origin, const t_vec vector);
t_vec		normalize_vector(const t_vec vector);
float		inv_sqrt(float num);
t_vec		norm_vec(t_vec vec);
void		set_vector(t_vec *vector, const t_vec *location1, \
	const t_vec *location2);
t_vec		create_vector(t_data *data, char *info);
t_vec		lerp(t_vec vec1, t_vec vec2, float fraction);
bool		is_glossy(t_data *data, uint32_t id, float glossiness);
/*	------------------------------------------------------------------	*/

/*	Quaternions	*/
/*	------------------------------------------------------------------	*/
t_quat		quat(float real, t_vec vec);
t_vec		random_vector(t_data *data, uint32_t id, t_vec surface_normal);
void		rotate(t_vec *point, t_quat rotation);
t_vec		reflect(const t_vec incoming, const t_vec normal);
/*	------------------------------------------------------------------	*/

#endif
