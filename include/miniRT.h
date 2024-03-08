/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 17:47:28 by cschabra      #+#    #+#                 */
/*   Updated: 2024/03/08 18:04:06 by vvan-der      ########   odam.nl         */
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

typedef enum s_token
{
	AMBIENT,
	CAMERA,
	CYLINDER,
	LIGHT,
	PLANE,
	SPHERE,
	INVALID
}	t_token;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_input
{
	char			**info;
	t_token			token;
	struct s_input	*next;
}	t_input;

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

typedef struct s_ambient
{
	double		luminosity;
	uint32_t	colour;
}	t_ambient;

typedef struct s_camera
{
	t_vec		viewpoint;
	t_vec		orientation;
	uint32_t	fov;
}	t_camera;

typedef struct s_cylinder
{
	t_vec		center;
	t_vec		orientation;
	double		radius;
	double		height;
	uint32_t	colour;
}	t_cylinder;

typedef struct s_light
{
	t_vec		source;
	double		luminosity;
	uint32_t	colour;
}	t_light;

typedef struct s_plane
{
	t_vec		location;
	t_vec		orientation;
	uint32_t	colour;
}	t_plane;

typedef struct s_sphere
{
	t_vec		center;
	double		radius;
	uint32_t	colour;
}	t_sphere;

typedef struct s_data
{
	mlx_image_t	*image;
	mlx_t		*mlx;
	t_input		*input;
	t_ambient	*ambient;
	t_camera	*cam;
	t_cylinder	*cyls;
	t_light		*light;
	t_plane		*planes;
	t_sphere	*spheres;
	char		*line;
	int32_t		fd;
	void		(*f[6])(t_data *, char **);
}	t_data;

uint32_t	ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
// void		draw_line(t_data *data, t_complex start, t_complex end);

/*	Initialisation	*/

void		check_rgb_values(t_data *data, t_vec vec);
void		init_ambient(t_data *data, char **info);
void		init_light(t_data *data, char **info);

void		init_objects(t_data *data, t_input *input);
void		init_camera(t_data *data, char **info);
void		init_cylinder(t_data *data, char **info);
void		init_plane(t_data *data, char **info);
void		init_sphere(t_data *data, char **info);

/*	Errors & cleanup	*/

void		free_and_null(void **variable);
void		free_2d(void ***input);
void		exit_error(t_data *data, char *msg);
void		clear_list(t_input **input);
void		clean_up(t_data *data);

/*	Initialisation	*/

void		read_file(t_data *data, char *location);

/*	List functions	*/

void		node_add_back(t_input **lst, t_input *new);
t_input		*new_node(t_data *data, char *line, t_token token);

t_input		*node_last(t_input *lst);
int32_t		count_objects(t_input *lst, t_token token);

/*	Math	*/

double		pythagoras(double a, double b);
double		pythagoras_3d(t_vec a, t_vec b);

/*	Utilities	*/

double		a_to_double(t_data *data, const char *str);

void		*rt_malloc(t_data *data, size_t size);
void		*rt_calloc(t_data *data, size_t size);

void		print_vector(t_vec vector);
void		print_colour(uint32_t colour);
void		print_2d_charray(char **array);
t_vec		create_vector(t_data *data, char *info);
void		check_split(t_data *data, char **info, int32_t num);
bool		is_white_space(char c);
void		verify_info(t_data *data, char **info);

#endif

// void	draw_rectangle(t_data *data, uint32_t wide, uint32_t high, \
//	t_complex center);
// void	draw_cube(t_data *data, t_complex center);
// void	draw_background(t_data *data);

// typedef union s_quat
// {
// 	double	q[4];
// 	struct
// 	{
// 		double	real;
// 		double	x;
// 		double	y;
// 		double	z;
// 	};
// }	t_quat;

// typedef struct s_complex
// {
// 	int32_t	x;
// 	int32_t	y;
// }	t_complex;

/* typedef struct s_window
{
	uint32_t	width;
	uint32_t	height;
}	t_window; */
