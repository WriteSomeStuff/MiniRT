/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maximum_thread.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/15 16:14:03 by vincent       #+#    #+#                 */
/*   Updated: 2024/07/31 17:03:05 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	wait_for_threads(t_data *data)
{
	while (FOREVER)
	{
		pthread_mutex_lock(&data->mutex);
		if (data->threads_absorbed == true)
			break ;
		pthread_mutex_unlock(&data->mutex);
		usleep(1000);
	}
	pthread_mutex_unlock(&data->mutex);
}

static void	*prep_rendering(void *d)
{
	uint32_t	i;
	t_data		*data;

	i = 0;
	data = (t_data *)d;
	pthread_mutex_lock(&data->mutex);
	if (data->go == false)
	{
		pthread_mutex_unlock(&data->mutex);
		return (NULL);
	}
	pthread_mutex_unlock(&data->mutex);
	while (i < data->num_threads)
	{
		if (pthread_self() == data->threads[i])
		{
			render(data, 0, i);
			return (NULL);
		}
		i++;
	}
	return (NULL);
}

static void	join_threads(t_data *data, pthread_t *threads, uint32_t num)
{
	if (num == data->num_threads)
		data->go = true;
	else
	{
		pthread_mutex_unlock(&data->mutex);
		exit_error(data, "failed to create thread");
	}
	pthread_mutex_unlock(&data->mutex);
	while (num > 0)
	{
		num--;
		if (pthread_join(threads[num], NULL) == -1)
			exit_error(data, "thread failed to join");
	}
	pthread_mutex_lock(&data->mutex);
	data->threads_absorbed = true;
	pthread_mutex_unlock(&data->mutex);
}

static void	*create_threads(void *data)
{
	uint32_t	i;
	t_data		*d;

	d = (t_data *)data;
	pthread_detach(pthread_self());
	// pthread_mutex_lock(&d->go_lock);
	while (FOREVER)
	{
		i = 0;
		pthread_mutex_lock(&d->mutex);
		d->iterations++;
		d->threads_absorbed = false;
		while (i < d->num_threads)
		{
			if (pthread_create(&d->threads[i], NULL, &prep_rendering, d) == -1)
				join_threads(d, d->threads, i);
			i++;
		}
		join_threads(d, d->threads, i);
		pthread_mutex_lock(&d->mutex);
		if (d->go == false)
			break ;
		pthread_mutex_unlock(&d->mutex);
	}
	pthread_mutex_unlock(&d->mutex);
	// pthread_mutex_unlock(&d->go_lock);
	return (NULL);
}

void	draw(t_data *data)
{
	pthread_t	idle;


	if (pthread_create(&idle, NULL, &create_threads, data) == -1)
		exit_error(data, "thread failed to create");
}
