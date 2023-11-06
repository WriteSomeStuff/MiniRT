/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 17:47:28 by cschabra      #+#    #+#                 */
/*   Updated: 2023/11/06 18:09:26 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include <MLX42/MLX42.h>
# include <math.h>

// for open, might not be needed
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_quat
{
	int32_t	i;
	int32_t	j;
	int32_t	k;
	int32_t	real;
}	t_quat;
typedef struct	s_data
{
	mlx_image_t	*image;
	mlx_t		*mlx;
}	t_data;

#endif
