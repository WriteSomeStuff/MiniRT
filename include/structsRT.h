/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structsRT.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/27 16:56:26 by vincent       #+#    #+#                 */
/*   Updated: 2024/04/15 11:17:02 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTSRT_H
# define STRUCTSRT_H

# include "miniRT.h"
# include <MLX42/MLX42.h>

typedef float	t_vec3 __attribute__ ((vector_size(16)));
typedef float	t_vec4 __attribute__ ((vector_size(16)));

typedef enum s_token		t_token;
typedef struct s_point		t_point;
typedef struct s_input		t_input;
typedef union s_vec			t_vec;
typedef union s_quat		t_quat;
typedef struct s_texture	t_texture;
typedef union s_magic		t_magic;
typedef struct s_hit		t_hit;
typedef struct s_ray		t_ray;
typedef struct s_ambient	t_ambient;
typedef struct s_camera		t_camera;
typedef struct s_cylinder	t_cylinder;
typedef struct s_light		t_light;
typedef struct s_plane		t_plane;
typedef struct s_sphere		t_sphere;
typedef struct s_window		t_window;
typedef struct s_data		t_data;

enum s_token
{
	CYLINDER,
	PLANE,
	SPHERE,
	AMBIENT,
	CAMERA,
	LIGHT,
	INVALID
};

struct s_point
{
	float	x;
	float	y;
};

struct s_input
{
	char			**info;
	t_token			token;
	struct s_input	*next;
};

union s_vec
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
	struct
	{
		float	i;
		float	j;
		float	k;
	};
};

union s_quat
{
	t_vec4	vec4;
	struct
	{
		float	real;
		float	i;
		float	j;
		float	k;
	};
	struct
	{
		float	scalar;
		float	x;
		float	y;
		float	z;
	};
};

struct s_texture
{
	uint32_t	width;
	uint32_t	height;
	uint8_t		*pixels;
};

union s_magic
{
	int32_t	i;
	float	y;
};

struct s_hit
{
	bool	hit;
	t_token	type;
	float	distance;
	void	*obj;
	t_vec	location;
	t_vec	surface_norm;
};

struct s_ray
{
	t_vec	origin;
	t_vec	direction;
	t_hit	*col;
};

struct s_ambient
{
	float		luminosity;
	t_vec		colour;
};

struct s_camera
{
	t_vec		viewpoint;
	t_vec		orientation;
	float		fov;
	float		fov_correction;
};

struct s_cylinder
{
	t_vec			center;
	t_vec			base;
	t_vec			top;
	t_vec			orientation;
	float			radius;
	float			height;
	t_vec			colour;
	t_token			object;
	uint32_t		amb_colour;
	uint16_t		instance;
	mlx_texture_t	*tex;
};

struct s_light
{
	t_vec		source;
	float		luminosity;
	t_vec		colour;
};

struct s_plane
{
	t_vec			location;
	t_vec			orientation;
	t_vec			rev_norm;
	t_vec			colour;
	t_token			object;
	uint32_t		amb_colour;
	uint16_t		instance;
	mlx_texture_t	*tex;
};

struct s_sphere
{
	uint32_t		amb_colour;
	t_vec			center;
	float			radius;
	t_vec			colour;
	t_token			object;
	uint16_t		instance;
	mlx_texture_t	*tex;
};

struct s_window
{
	uint32_t	width;
	uint32_t	height;
	float		aspect_ratio;
};

struct s_data
{
	mlx_image_t		*image;
	mlx_t			*mlx;
	t_input			*input;
	t_ambient		*ambient;
	t_camera		*cam;
	t_cylinder		*cyls;
	t_light			*light;
	t_plane			*planes;
	t_sphere		*spheres;
	t_window		*window;
	char			*line;
	int16_t			**map;
	int32_t			fd;
	int32_t			cyl_count;
	int32_t			plane_count;
	int32_t			sphere_count;
	void			(*f[6])(t_data *, char **);
};

#endif
