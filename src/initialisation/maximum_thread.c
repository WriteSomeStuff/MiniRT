/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maximum_thread.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/15 16:14:03 by vincent       #+#    #+#                 */
/*   Updated: 2024/07/01 17:41:25 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	wait_for_threads(t_data *data)
{
	while (FOREVER)
	{
		pthread_mutex_lock(&data->mutex);
		// printf("absorbed: %u/%u\n", data->threads_absorbed, data->num_threads);
		if (data->threads_absorbed == data->num_threads)
		{
			break ;
		}
		pthread_mutex_unlock(&data->mutex);
		usleep(1000);
	}
	pthread_mutex_unlock(&data->mutex);
}

static void	*prepare_rendering(void *d)
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
	pthread_mutex_unlock(&data->mutex);
	while (num > 0)
	{
		num--;
		if (pthread_join(threads[num], NULL) == -1)
			exit_error(data, "thread failed to join");
	}
}
/* 
static long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)time.tv_sec * 1000000 + time.tv_usec);
} */

static void	*create_threads(void *d)
{
	uint32_t	i;
	t_data		*data;

	data = (t_data *)d;
	pthread_detach(pthread_self());
	while (FOREVER)
	{
		i = 0;
		data->threads_absorbed = 0;
		if (data->iterations > 0 && data->iterations % 10 == 0)
		printf("Samples: %d\n", data->iterations * NUM_RAYS);
		pthread_mutex_lock(&data->mutex);
		data->iterations++;
		while (i < data->num_threads)
		{
			if (pthread_create(&data->threads[i], NULL, &prepare_rendering, data) == -1)
			{
				join_threads(data, data->threads, i);
				exit_error(data, "failed to create thread");
			}
			i++;
		}
		join_threads(data, data->threads, i);
		pthread_mutex_lock(&data->mutex);
		if (data->go == false)
			break ;
		pthread_mutex_unlock(&data->mutex);
	}
	pthread_mutex_unlock(&data->mutex);
	return (NULL);
}

void	draw(t_data *data)
{
	pthread_t	idle;

	if (pthread_create(&idle, NULL, &create_threads, data) == -1)
		exit_error(data, "thread failed to create");
}
