/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 17:47:28 by cschabra      #+#    #+#                 */
/*   Updated: 2023/11/07 18:29:35 by cschabra      ########   odam.nl         */
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

# define WIDTH 512
# define HEIGHT 512

typedef struct s_quat
{
	int32_t	real;
	int32_t	i;
	int32_t	j;
	int32_t	k;
}	t_quat;

/* typedef struct s_window
{
	uint32_t	width;
	uint32_t	height;
}	t_window; */

typedef struct	s_data
{
	mlx_image_t	*image;
	mlx_t		*mlx;
}	t_data;

#endif
