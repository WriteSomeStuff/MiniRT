/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/23 13:53:09 by vincent       #+#    #+#                 */
/*   Updated: 2024/08/08 17:43:04 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	rt_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	pthread_mutex_lock(&data->mutex);
	data->go = false;
	pthread_mutex_unlock(&data->mutex);
	wait_for_threads(data);
	exit_success(data);
}

void	rt_scroll(double xdelta, double ydelta, void *param)
{
	t_data	*data;

	(void)xdelta;
	data = (t_data *)param;
	if (ydelta < 0)
		ydelta = 10;
	else
		ydelta = -10;
	if (ydelta + data->cam->fov < 0)
		data->cam->fov = 0;
	else if (ydelta + data->cam->fov > 180)
		data->cam->fov = 180;
	else
		data->cam->fov += ydelta;
	data->cam->fov_correction = tan(degree_to_radian(data->cam->fov) / 2);
	redraw(data);
}
