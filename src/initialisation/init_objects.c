/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_objects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 16:08:04 by cschabra      #+#    #+#                 */
/*   Updated: 2024/03/04 18:52:18 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_camera(t_data *data, char **info)
{
	t_camera	*cam;

	check_split(data, info, 3);
	print_2d_charray(info);
	verify_info(data, info);
	cam = rt_malloc(data, sizeof(t_camera));
	cam->viewpoint = create_vector(data, info[0]);
	cam->orientation = create_vector(data, info[1]);
	cam->fov = ft_atoi(info[2]);
	print_vector(cam->viewpoint);
	print_vector(cam->orientation);
}

void	init_cylinder(t_data *data, char **info)
{
	check_split(data, info, 5);
	verify_info(data, info);
/* 	while (info[i] != NULL)
	{
		if (ft_strchr(info[i], ',') != NULL)
			create_vector(info[i]);
		i++;
	} */
}

void	init_plane(t_data *data, char **info)
{
	check_split(data, info, 3);
	verify_info(data, info);
	/* while (info[i] != NULL)
	{
		if (ft_strchr(info[i], ',') != NULL)
			create_vector(info[i]);
		i++;
	} */
}

void	init_sphere(t_data *data, char **info)
{
	check_split(data, info, 3);
	verify_info(data, info);
/* 	while (info[i] != NULL)
	{
		if (ft_strchr(info[i], ',') != NULL)
			create_vector(info[i]);
		i++;
	} */
}
