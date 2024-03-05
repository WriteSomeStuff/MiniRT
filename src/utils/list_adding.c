/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_adding.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/05 16:17:25 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/05 16:19:39 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	node_add_back(t_input **lst, t_input *new)
{
	t_input	*t;

	t = node_last(*lst);
	if (t == NULL)
		*lst = new;
	else
		t->next = new;
}

t_input	*new_node(t_data *data, char *line, t_token token)
{
	t_input	*node;

	if (token == INVALID)
		exit_error(data, ": invalid input");
	node = rt_calloc(data, sizeof(t_input));
	node->info = ft_split(&line[2], ' ');
	if (node->info == NULL)
		exit_error(data, ": split failed");
	node->token = token;
	return (node);
}
