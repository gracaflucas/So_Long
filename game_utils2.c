/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:06:13 by lufiguei          #+#    #+#             */
/*   Updated: 2024/10/12 16:06:24 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	char_cmp(t_data *game)
{
	int		i;
	int		j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
			if (game->map[i][j] != 'P' && game->map[i][j] != 'E'
				&& game->map[i][j] != 'C' && game->map[i][j] != '0'
				&& game->map[i][j] != '1')
				return (2);
	}
	return (0);
}

int	is_double_newline(char *buffer)
{
	int	i;

	i = -1;
	while (buffer[++i])
		if (buffer[i] == '\n')
			if (buffer[i + 1] != '\0' && buffer[i + 1] == '\n')
				return (2);
	return (0);
}
