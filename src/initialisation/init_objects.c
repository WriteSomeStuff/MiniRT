/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_objects.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 16:08:04 by cschabra      #+#    #+#                 */
/*   Updated: 2024/02/28 17:49:18 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_camera(t_data *data, char **info)
{
	t_camera	*cam;

	check_split(data, info, 3);
	verify_info(data, info);
	cam = rt_malloc(data, sizeof(t_camera));
	cam->viewpoint = create_vector(info[0]);
	cam->orientation = create_vector(info[1]);
	cam->fov = ft_atoi(info[2]);
}

void	init_cylinder(t_data *data, char **info)
{
	check_split(data, info, 5);
	verify_info(data, info);
	while (info[i] != NULL)
	{
		if (ft_strchr(info[i], ',') != NULL)
			create_vector(info[i]);
		i++;
	}
}

void	init_plane(t_data *data, char **info)
{
	check_split(data, info, 3);
	verify_info(data, info);
	while (info[i] != NULL)
	{
		if (ft_strchr(info[i], ',') != NULL)
			create_vector(info[i]);
		i++;
	}
}

void	init_sphere(t_data *data, char **info)
{
	check_split(data, info, 3);
	verify_info(data, info);
	while (info[i] != NULL)
	{
		if (ft_strchr(info[i], ',') != NULL)
			create_vector(info[i]);
		i++;
	}
}
