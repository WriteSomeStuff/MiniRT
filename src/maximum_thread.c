/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   maximum_thread.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/15 16:14:03 by vincent       #+#    #+#                 */
/*   Updated: 2024/05/15 17:52:49 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	*start_thread(void *d)
{
	uint32_t	i;
	t_data		*data;
	
	i = 0;
	data = (t_data *)d;
	pthread_mutex_lock(&data->mutex);
	if (data->go == false)
		return (NULL);
	pthread_mutex_unlock(&data->mutex);
	while (i < THREADS)
	{
		if (pthread_self()->__sig == data->threads[i]->__sig)
		{
			draw_something(data, 0, i);
			return (NULL);
		}
		i++;
	}
	return (NULL);
}

static void	join_threads(t_data *data, pthread_t *threads, int num)
{
	if (num == THREADS)
		data->go = true;
	pthread_mutex_unlock(&data->mutex);
	while (num >= 0)
	{
		if (pthread_join(threads[num], NULL) == -1)
			exit_error(data, "thread failed to join");
		num--;
	}
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)time.tv_sec * 1000000 + time.tv_usec);
}

void	init_threads(t_data *data)
{
	int			i;
	long		start, end;
	pthread_t	*threads;

	i = 0;
	start = get_time();
	if (pthread_mutex_init(&data->mutex, NULL) == -1)
		exit_error(data, "mutex failed to initialize");
	threads = rt_calloc(data, THREADS * sizeof(pthread_t));
	data->threads = threads;
	pthread_mutex_lock(&data->mutex);
	while (i < THREADS)
	{
		if (pthread_create(&threads[i], NULL, &start_thread, data) == -1)
		{
			join_threads(data, threads, i + 1);
			exit_error(data, "failed to create thread");
		}
		i++;
	}
	join_threads(data, threads, i);
	pthread_mutex_destroy(&data->mutex);
	free_and_null((void **)&data->threads);
	end = get_time();
	printf("runtime: %ld ms\n", (end - start) / 1000);
}
