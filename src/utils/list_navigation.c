/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_navigation.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/05 16:17:28 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/03/05 16:23:25 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_input	*node_last(t_input *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int32_t	count_objects(t_input *lst, t_token token)
{
	int32_t	count;

	count = 0;
	while (lst != NULL)
	{
		if (lst->token == token)
			count++;
		lst = lst->next;
	}
	return (count);
}
