/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 17:47:28 by cschabra      #+#    #+#                 */
/*   Updated: 2024/03/25 11:24:55 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "get_next_line_rt.h"
# include <MLX42/MLX42.h>
# include <float.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>

# define WIDTH 1920
# define HEIGHT 1080
# define PI 3.14159265359
# define FOREVER 1

typedef float	t_vec3 __attribute__ ((vector_size(16)));

typedef enum s_token
{
	CYLINDER,
	PLANE,
	SPHERE,
	AMBIENT,
	CAMERA,
	LIGHT,
	INVALID
}	t_token;

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_input
{
	char			**info;
	t_token			token;
	struct s_input	*next;
}	t_input;

typedef union s_vec
{
	t_vec3	vec3;
	struct
	{
		float	x;
		float	y;
		float	z;
	};
	struct
	{
		float	r;
		float	g;
		float	b;
	};
}	t_vec;

typedef struct s_texture
{
	uint32_t	width;
	uint32_t	height;
	t_vec		**px;
}	t_texture;

typedef union s_magic
{
	int32_t	i;
	float	y;
}	t_magic;

typedef struct s_hit
{
	bool	hit;
	bool	inside_object;
	t_token	type;
	float	distance;
	void	*obj;
	t_vec	location;
}	t_hit;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
	t_hit	*col;
}	t_ray;

typedef struct s_ambient
{
	float		luminosity;
	t_vec		colour;
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
	float		radius;
	float		height;
	t_vec		colour;
	t_token		object;
	uint32_t	amb_colour;
}	t_cylinder;

typedef struct s_light
{
	t_vec		source;
	float		luminosity;
	t_vec		colour;
}	t_light;

typedef struct s_plane
{
	t_vec		location;
	t_vec		orientation;
	t_vec		colour;
	t_token		object;
	uint32_t	amb_colour;
}	t_plane;

typedef struct s_sphere
{
	uint32_t	amb_colour;
	t_vec		center;
	float		radius;
	t_vec		colour;
	t_token		object;
	t_texture	*tex;
}	t_sphere;

typedef struct s_window
{
	uint32_t	width;
	uint32_t	height;
	float		aspect_ratio;
}	t_window;

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
	t_texture	*textures;
	t_window	*window;
	char		*line;
	int32_t		fd;
	int32_t		cyl_count;
	int32_t		plane_count;
	int32_t		sphere_count;
	void		(*f[6])(t_data *, char **);
}	t_data;

void		draw_something(t_data *data);

/*	Colours	*/
/*	------------------------------------------------------------------	*/
uint32_t	ambient_colour(const t_vec *obj_colour, const t_vec *ambient);
t_vec		reflection_result(const t_vec *c1, const t_vec *c2, float fraction);
t_vec		combine_colours(const t_vec *c1, const t_vec *c2);
uint32_t	percentage_to_rgba(const t_vec *f);
/*	------------------------------------------------------------------	*/

/*	Hooks	*/
/*	------------------------------------------------------------------	*/
void		ft_hook(void *param);
/*	------------------------------------------------------------------	*/

/*	Initialisation	*/
/*	------------------------------------------------------------------	*/
void		check_rgb_values(t_data *data, const t_vec3 *vec);
void		init_ambient(t_data *data, char **info);
void		obj_ambiance(t_data *d, t_cylinder *c, t_plane *p, t_sphere *s);
void		init_light(t_data *data, char **info);

void		init_objects(t_data *data, t_input *input);
void		init_camera(t_data *data, char **info);
void		init_cylinder(t_data *data, char **info);
void		init_plane(t_data *data, char **info);
void		init_sphere(t_data *data, char **info);

void		read_file(t_data *data, char *location);
/*	------------------------------------------------------------------	*/

/*	Math	*/
/*	------------------------------------------------------------------	*/
void		find_closest_object(t_data *data, t_hit *col, const t_ray *ray);

float		degree_to_radian(const float degree);
float		radian_to_degree(const float radian);
float		pythagoras(const float a, const float b);
float		pytha_inverse(const float c, const float a);
bool		quadratic_equation(const t_vec *vec, float *a, float *b);

t_vec		direction_to_xy(t_data *data, float x, float y);

float		dot_product(const t_vec *a, const t_vec *b);
t_vec		cross_product(const t_vec *a, const t_vec *b);
/*	------------------------------------------------------------------	*/

/*	Utilities	*/
/*	------------------------------------------------------------------	*/
float		a_to_float(t_data *data, const char *str);

void		*rt_malloc(t_data *data, size_t size);
void		*rt_calloc(t_data *data, size_t size);

void		node_add_back(t_input **lst, t_input *new);
t_input		*new_node(t_data *data, char *line, t_token token);

t_input		*node_last(t_input *lst);
int32_t		count_objects(t_input *lst, t_token token);

uint32_t	ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void		print_vector(t_vec vector);
void		print_2d_charray(char **array);
void		rgb_to_floats(t_vec *rgb);
t_vec		create_vector(t_data *data, char *info);
void		check_split(t_data *data, char **info, int32_t num);
bool		is_white_space(char c);
void		verify_info(t_data *data, char **info);

float		vector_length(const t_vec *origin, const t_vec *vector);
t_vec		normalize_vector(const t_vec *vector);
float		q_sqrt(float num);
t_vec		scale_vector(const t_vec *vector, float scalar);
/*	------------------------------------------------------------------	*/

/*	Errors & cleanup	*/
/*	------------------------------------------------------------------	*/
void		free_and_null(void **variable);
void		free_2d(void ***input);
void		exit_error(t_data *data, char *msg);
void		exit_success(t_data *data);
void		clear_list(t_input **input);
void		clean_up(t_data *data);
/*	------------------------------------------------------------------	*/

#endif
