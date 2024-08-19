/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschabra <cschabra@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 12:17:22 by cschabra      #+#    #+#                 */
/*   Updated: 2024/08/19 14:52:58 by cschabra      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	is_white_space(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (true);
	return (false);
}

bool	is_empty_str(char *str)
{
	while (*str != '\0')
	{
		if (is_white_space(*str) == false)
			return (false);
		str++;
	}
	return (true);
}

mlx_texture_t	*load_texture(t_data *data, char *path)
{
	mlx_texture_t	*tex;

	tex = mlx_load_png(path);
	if (tex == NULL)
		exit_error(data, ": texture failed to load");
	return (tex);
}

t_vec	create_vector(t_data *data, char *info)
{
	t_vec	vector;
	char	**vec;

	if (*info == ',')
		exit_error(data, ": invalid input");
	vec = ft_split(info, ',');
	if (vec == NULL || !vec[0] || !vec[1] || !vec[2] || vec[3])
		exit_error(data, ": split failed or invalid input");
	vector.x = a_to_float(data, vec[0]);
	vector.y = a_to_float(data, vec[1]);
	vector.z = a_to_float(data, vec[2]);
	free_2d((void ***)&vec);
	return (vector);
}
