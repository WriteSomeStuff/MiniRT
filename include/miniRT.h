/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: soepgroente <soepgroente@student.42.fr>      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/05 17:47:28 by cschabra      #+#    #+#                 */
/*   Updated: 2024/08/16 13:15:09 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "get_next_line_rt.h"
# include "structsRT.h"
# include "vectorsRT.h"
# include "MLX42/MLX42.h"
# include <pthread.h>
# include <math.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/stat.h>

# define WIDTH 1920
# define HEIGHT 1080
# define PI 3.1415927f
# define FOREVER 1
# define OFFSET 0.001f
# define THRESHHOLD 0.1
# define NUM_RAYS 10
# define MAX_BOUNCES 25
# define MAX_FLOAT 3.40282347e+38F

float			prn(uint32_t *id);
bool			is_empty_str(char *str);
mlx_texture_t	*load_texture(t_data *data, char *path);
float			max(float a, float b);
void			wait_for_threads(t_data *data);
void			render(t_data *data, int32_t x, int32_t y);
void			redraw(t_data *data);
void			rt_close(void *param);

void			cone(t_hit *col, t_vec incoming);

void			draw_collision(t_hit *col, t_vec incoming);
void			trace(t_data *data, t_ray *ray, int32_t x, int32_t y);
float			sum(t_vec vector);
void			update(t_ray *ray, t_token type, void *obj, float distance);
float			hit_flat_surface(float *distance, t_ray *ray, t_vec point, \
	t_vec orientation);
bool			analyze_intersection(float *a, float *b);

void			intersect_cones(t_hit *col, t_ray *ray, const t_cone *c);
void			intersect_cylinders(t_hit *col, t_ray *ray, \
	const t_cylinder *c);
void			intersect_discs(t_hit *col, t_ray *ray, const t_disc *d);
void			intersect_planes(t_hit *col, t_ray *ray, const t_plane *p);
void			intersect_spheres(t_hit *col, t_ray *ray, const t_sphere *s);

/*	Colours	*/
/*	------------------------------------------------------------------	*/
void			gamma_adjust(t_vec *colour);
t_vec			reflection_result(const t_vec c1, const t_vec c2, \
	float fraction);
t_vec			combine_colours(const t_vec c1, const t_vec c2);
uint32_t		percentage_to_rgba(const t_vec f);
void			rgb_to_floats(t_vec *rgb);

t_vec			cone_tex(void *coneptr, t_hit *col);
t_vec			cylinder_tex(void *cylptr, t_hit *col);
t_vec			disc_tex(void *discptr, t_hit *col);

t_vec			get_object_colour(t_hit *col);
/*	------------------------------------------------------------------	*/

/*	Hooks	*/
/*	------------------------------------------------------------------	*/
void			rt_keys(mlx_key_data_t keydata, void *param);
void			rt_scroll(double xdelta, double ydelta, void *param);
void			rt_select(mouse_key_t btn, action_t act, modifier_key_t m, \
	void *p);
/*	------------------------------------------------------------------	*/

/*	Initialisation	*/
/*	------------------------------------------------------------------	*/
void			check_rgb_values(t_data *data, const t_vec3 *vec);
void			init_ambient(t_data *data, char **info);
void			init_light(t_data *data, char **info);

int16_t			object_count(t_data *data);
void			init_objects(t_data *data, t_input *input);
void			init_camera(t_data *data, char **info);
void			init_cone(t_data *data, char **info);
void			init_cylinder(t_data *data, char **info);
void			init_disc(t_data *data, char **info);
void			init_plane(t_data *data, char **info);
void			init_sphere(t_data *data, char **info);

void			read_file(t_data *data, char *location);

void			rotate_cones(t_cone *c, t_quat rotation);
void			rotate_cylinders(t_cylinder *c, t_quat rotation);
void			rotate_discs(t_disc *d, t_quat rotation);
void			rotate_planes(t_plane *p, t_quat rotation);
void			rotate_spheres(t_sphere *s, t_quat rotation);

void			normalize_scene(t_data *data);
void			translate_objects(t_data *data, t_vec amount);

void			translate_cones(t_cone *c, t_vec t);
void			translate_cylinders(t_cylinder *c, t_vec t);
void			translate_discs(t_disc *d, t_vec t);

void			draw(t_data *data);
/*	------------------------------------------------------------------	*/

/*	Math	*/
/*	------------------------------------------------------------------	*/
void			find_closest_object(t_data *data, t_hit *col, t_ray *ray, \
	uint32_t id);

float			degree_to_radian(const float degree);
float			radian_to_degree(const float radian);
float			pythagoras(const float a, const float b);

void			cast_rays(t_data *data);
/*	------------------------------------------------------------------	*/

/*	Utilities	*/
/*	------------------------------------------------------------------	*/
float			a_to_float(t_data *data, const char *str);

void			*rt_malloc(t_data *data, size_t size);
void			*rt_calloc(t_data *data, size_t size);

void			node_add_back(t_input **lst, t_input *new);
t_input			*new_node(t_data *data, char *line, t_token token);

t_input			*node_last(t_input *lst);
int32_t			count_objects(t_input *lst, t_token token);

uint32_t		ft_pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void			print_2d_charray(char **array);
void			check_split(t_data *data, char **info, int32_t num);
void			verify_info(t_data *data, char **info);
/*	------------------------------------------------------------------	*/

/*	Errors & cleanup	*/
/*	------------------------------------------------------------------	*/
void			free_and_null(void **variable);
void			free_2d(void ***input);
void			exit_error(t_data *data, char *msg);
void			exit_success(t_data *data);
void			clear_list(t_input **input);
void			clean_up(t_data *data);
/*	------------------------------------------------------------------	*/

#endif
