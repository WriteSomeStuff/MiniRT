/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structsRT.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/27 16:56:26 by vincent       #+#    #+#                 */
/*   Updated: 2024/07/30 11:44:03 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTSRT_H
# define STRUCTSRT_H

# include "miniRT.h"
# include <MLX42/MLX42.h>

typedef float				t_vec3 __attribute__ ((vector_size(16)));
typedef float				t_vec4 __attribute__ ((vector_size(16)));
typedef union u_vec			t_vec;
typedef union u_quat		t_quat;
typedef union u_magic		t_magic;
typedef struct s_input		t_input;
typedef struct s_texture	t_texture;
typedef struct s_hit		t_hit;
typedef struct s_ray		t_ray;
typedef struct s_camera		t_camera;
typedef struct s_cylinder	t_cylinder;
typedef struct s_disc		t_disc;
typedef struct s_plane		t_plane;
typedef struct s_pixel		t_pixel;
typedef struct s_sphere		t_sphere;
typedef struct s_window		t_window;
typedef struct s_data		t_data;

typedef enum s_token
{
	CYLINDER,
	DISC,
	PLANE,
	SPHERE,
	LIGHT,
	AMBIENT,
	CAMERA,
	INVALID
}	t_token;

union u_vec
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

union u_quat
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

union u_magic
{
	int32_t	i;
	float	y;
};

struct s_input
{
	char			**info;
	t_token			token;
	struct s_input	*next;
};

struct s_texture
{
	uint32_t	width;
	uint32_t	height;
	uint8_t		*pixels;
};

struct s_hit
{
	bool	hit;
	bool	inside_obj;
	bool	caps;
	bool	glossy_bounce;
	t_token	type;
	int16_t	obj_num;
	float	distance;
	float	glossiness;
	float	specular;
	void	*obj;
	t_vec	location;
	t_vec	colour;
	t_vec	objclr;
	t_vec	surface_norm;
};

struct s_ray
{
	t_vec	origin;
	t_vec	direction;
	t_hit	*col;
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
	t_vec			rev_norm;
	float			glossiness;
	float			specular;
	float			radius;
	float			height;
	t_vec			colour;
	t_token			object;
	uint16_t		instance;
	mlx_texture_t	*tex;
};

struct s_disc
{
	t_vec			center;
	t_vec			orientation;
	t_vec			rev_norm;
	float			glossiness;
	float			specular;
	float			radius;
	float			hole_radius;
	t_vec			colour;
	t_token			object;
	uint16_t		instance;
};

struct s_plane
{
	t_vec			location;
	t_vec			orientation;
	t_vec			rev_norm;
	t_vec			colour;
	float			glossiness;
	float			specular;
	t_token			object;
	uint16_t		instance;
	mlx_texture_t	*tex;
};

struct s_pixel
{
	t_vec			ray_direction;
	t_vec			ambient;
	t_vec			obj_clr;
	t_vec			samples;
	t_vec			pix_clr;
	t_vec			location;
	t_vec			incoming;
	t_vec			surface_norm;
	float			glossiness;
	float			specular;
	int16_t			obj_num;
};

struct s_sphere
{
	t_vec			center;
	float			radius;
	float			glossiness;
	float			specular;
	t_vec			colour;
	t_token			object;
	uint16_t		instance;
	mlx_texture_t	*tex;
};

struct s_window
{
	int32_t		width;
	int32_t		height;
	float		aspect_ratio;
	bool		sizechanged;
};

struct s_data
{
	char			*line;
	mlx_t			*mlx;
	mlx_image_t		*counter;
	mlx_image_t		*highlight;
	mlx_image_t		*scene;
	pthread_t		*threads;
	uint32_t		iterations;
	uint32_t		num_threads;
	uint32_t		threads_absorbed;
	uint32_t		seed[16];
	bool			go;
	t_input			*input;
	t_vec			ambient;
	t_camera		*cam;
	t_cylinder		*cyls;
	t_disc			*discs;
	t_plane			*planes;
	t_sphere		*spheres;
	t_window		*window;
	t_pixel			**pix;
	t_vec			**directions;
	int16_t			selected;
	int32_t			fd;
	int32_t			cyl_count;
	int32_t			disc_count;
	int32_t			plane_count;
	int32_t			sphere_count;
	pthread_mutex_t	mutex;
	void			(*f[INVALID])(t_data *, char **);
};

#endif
