/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 17:47:28 by cschabra      #+#    #+#                 */
/*   Updated: 2024/02/22 17:35:58 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "get_next_line_rt.h"
# include <MLX42/MLX42.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>

# define WIDTH 512
# define HEIGHT 512
# define PI 3.14159265359
# define FOREVER 1

typedef struct s_input
{
	char			*line;
	struct s_input	*next;
}	t_input;

typedef union s_quat
{
	double	q[4];
	struct
	{
		double	real;
		double	x;
		double	y;
		double	z;
	};
}	t_quat;

typedef union s_vec
{
	double	v[3];

	struct
	{
		double	x;
		double	y;
		double	z;
	};
}	t_vec;

typedef struct s_complex
{
	int32_t	x;
	int32_t	y;
}	t_complex;

/* typedef struct s_window
{
	uint32_t	width;
	uint32_t	height;
}	t_window; */

typedef struct s_data
{
	mlx_image_t	*image;
	mlx_t		*mlx;
	t_input		*input;
}	t_data;

void		draw_rectangle(t_data *data, uint32_t wide, uint32_t high, t_complex center);
uint32_t	ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void		draw_line(t_data *data, t_complex start, t_complex end);
void		draw_background(t_data *data);
void		draw_cube(t_data *data, t_complex center);

/*	Initialization	*/

void		read_file(t_data *data, char *location);

/*	Errors & cleanup	*/

void		clean_up(t_data *data);
void		clear_list(t_input **input);
void		exit_error(t_data *data, char *msg);
void		*ft_malloc(t_data *data, int32_t size);

#endif
