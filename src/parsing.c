/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/22 15:52:29 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/22 17:29:59 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_input	*node_last(t_input *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

static void	node_add_back(t_input **lst, t_input *new)
{
	t_input	*t;

	t = node_last(*lst);
	if (t == NULL)
		*lst = new;
	else
		t->next = new;
}

static t_input	*new_node(t_data *data, char *line)
{
	t_input	*node;

	node = ft_malloc(data, sizeof(t_input));
	node->line = line;
	node->next = NULL;
	return (node);
}

void	read_file(t_data *data, char *location)
{
	int32_t	fd;
	t_input	*input;
	char	*next_line;

	input = NULL;
	fd = open(location, O_RDONLY);
	if (fd == -1)
		exit_error(data, ": could not open file");
	while (FOREVER)
	{
		next_line = get_next_line_rt(data, fd);
		if (next_line == NULL)
			break ;
		node_add_back(&input, new_node(data, next_line));
	}
	data->input = input;
	close(fd);
}
