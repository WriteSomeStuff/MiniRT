/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/28 16:25:10 by cschabra      #+#    #+#                 */
/*   Updated: 2024/02/28 17:51:13 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	check_split(t_data *data, char **info, int32_t num)
{
	int32_t	i;

	i = 0;
	while (i < num)
	{
		if (info[i] == NULL)
			exit_error(data, ": invalid input");
		i++;
	}
	if (info[i] != NULL)
		exit_error(data, ": invalid input");
}

bool	is_white_space(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (true);
	return (false);
}

void	verify_info(t_data *data, char **info)
{
	int32_t	x;
	int32_t	y;

	x = 0;
	while (info[x] != NULL)
	{
		y = 0;
		while (info[x][y] != '\0')
		{
			if (info[x][y] == '-' && ft_isdigit(info[x][y + 1]) == false)
				exit_error(data, ": no digit after \"-\" sign");
			while (ft_isdigit(info[x][y]) == true)
				y++;
			if (info[x][y] == '\0')
				break ;
			else if (info[x][y] == '.' || info[x][y] == ',')
				y++;
			else
				exit_error(data, ": invalid character in input");
		}
		x++;
	}
}