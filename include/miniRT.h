/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 17:47:28 by cschabra      #+#    #+#                 */
/*   Updated: 2024/05/31 19:23:45 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "get_next_line_rt.h"
# include <pthread.h>
# include "structsRT.h"
# include "vectorsRT.h"
# include <MLX42/MLX42.h>
# include <float.h>
# include <math.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/stat.h>

# define WIDTH 720
# define HEIGHT 720
# define PI 3.1415927f
# define FOREVER 1
# define OFFSET 0.00001f
# define THRESHHOLD 0.1
# define NUM_RAYS 1000
# define MAX_BOUNCES 25

// void		test_multiple_renders(t_data *data, uint32_t x, uint32_t y);
void		render(t_data *data, uint32_t x, uint32_t y);
void		draw_collision(t_hit *col, float absorption, float reflectivity);
void		trace(t_data *data, t_ray *ray, uint32_t x, uint32_t y);
float		sum(t_vec vector);

/*	Colours	*/
/*	------------------------------------------------------------------	*/
uint32_t	ambient_colour(const t_vec obj_colour, const t_vec ambient);
t_vec		reflection_result(const t_vec c1, const t_vec c2, float fraction);
t_vec		combine_colours(const t_vec c1, const t_vec c2);
uint32_t	percentage_to_rgba(const t_vec f);
// uint32_t	pixel_colour(t_data *data, t_vec clr, float product);

t_vec		cylinder_texture(t_cylinder *cyl, t_vec *surface);
t_vec		plane_texture(t_plane *plane, t_vec loc);
t_vec		sphere_texture(t_sphere *sphere, t_vec *surface);
/*	------------------------------------------------------------------	*/

/*	Hooks	*/
/*	------------------------------------------------------------------	*/
void		rt_keys(mlx_key_data_t keydata, void *param);
void		rt_scroll(double xdelta, double ydelta, void *param);
void		rt_select(mouse_key_t btn, action_t act, modifier_key_t m, void *p);
/*	------------------------------------------------------------------	*/

/*	Initialisation	*/
/*	------------------------------------------------------------------	*/
void		check_rgb_values(t_data *data, const t_vec3 *vec);
void		init_ambient(t_data *data, char **info);
void		obj_ambiance(t_data *d, t_cylinder *c, t_plane *p, t_sphere *s);
void		init_light(t_data *data, char **info);

int16_t		object_count(t_data *data);
void		init_objects(t_data *data, t_input *input);
void		init_camera(t_data *data, char **info);
void		init_cylinder(t_data *data, char **info);
void		init_plane(t_data *data, char **info);
void		init_sphere(t_data *data, char **info);

// void		init_map(t_data *data);
void		read_file(t_data *data, char *location);
void		normalize_scene(t_data *data);
void		translate_objects(t_data *data, t_vec amount);

void		draw(t_data *data);
/*	------------------------------------------------------------------	*/

/*	Math	*/
/*	------------------------------------------------------------------	*/
void		find_closest_object(t_data *data, t_hit *col, t_ray *ray);

float		degree_to_radian(const float degree);
float		radian_to_degree(const float radian);
float		pythagoras(const float a, const float b);

// void		allocate_rays(t_data *data, int32_t width, int32_t height);
void		cast_rays(t_data *data);
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
void		print_2d_charray(char **array);
void		rgb_to_floats(t_vec *rgb);
void		check_split(t_data *data, char **info, int32_t num);
bool		is_white_space(char c);
void		verify_info(t_data *data, char **info);
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
