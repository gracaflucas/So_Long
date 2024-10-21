/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:20:45 by lufiguei          #+#    #+#             */
/*   Updated: 2024/09/07 19:20:47 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	extention(char *str)
{
	int	len;

	if (str == NULL)
		return (2);
	len = ft_strlen(str);
	if (len < 4)
		return (2);
	if (str[len - 1] != 'r' || str[len - 2] != 'e'
		|| str[len - 3] != 'b' || str[len - 4] != '.')
		return (2);
	return (0);
}

static int	valid_walls(t_data *game)
{
	int	i;

	i = -1;
	while (++i < game->height - 1)
		if (game->map[i][0] == '0')
			return (2);
	i = -1;
	while (++i < game->height - 1)
		if (game->map[i][game->width - 1] == '0')
			return (2);
	i = -1;
	while (++i < game->width - 1)
		if (game->map[0][i] == '0')
			return (2);
	i = -1;
	while (++i < game->width)
		if (game->map[game->height - 1][i] == '0')
			return (2);
	return (0);
}

static int	is_pec(t_data *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
		{
			if (game->map[i][j] == 'P')
			{
				game->px = i;
				game->py = j;
				game->player += 1;
			}
			else if (game->map[i][j] == 'C')
				game->collectable += 1;
			else if (game->map[i][j] == 'E')
				game->exit += 1;
		}
	}
	if (game->collectable == 0 || game->player != 1 || game->exit != 1)
		return (2);
	return (0);
}

static int	flood_fill(t_data *game, int x, int y)
{
	if (x < 0 || x >= game->height || y < 0 || y >= game->width)
		return (2);
	if (game->map[x][y] == '1' || game->map[x][y] == '.')
		return (2);
	if (game->map[x][y] == 'C')
		game->bag += 1;
	if (game->map[x][y] == 'E')
		game->exit_reached = 1;
	if (game->bag == game->collectable && game->exit_reached == 1)
		return (0);
	game->map[x][y] = '.';
	if ((flood_fill(game, x - 1, y) == 0)
		|| (flood_fill(game, x + 1, y) == 0)
		|| (flood_fill(game, x, y - 1) == 0)
		|| (flood_fill(game, x, y + 1) == 0))
		return (0);
	return (2);
}

int	valid_map(char *str, t_data *game)
{
	if (extention(str) == 2)
		return (ft_printf("Error\nnot a valid extension.\n"));
	if (llen_calc(game) == 2)
		return (ft_printf("Error\nnon-rectangular map.\n"));
	if (valid_walls(game) == 2)
		return (ft_printf("Error\ninvalid walls.\n"));
	if (is_pec(game) == 2)
		return (ft_printf("Error\nmissing Player, Collectable or Exit.\n"));
	if (char_cmp(game) == 2)
		return (ft_printf("Error\nunknown character inside map.\n"));
	if (flood_fill(game, game->px, game->py) == 2)
		return (ft_printf("Error\nnon-winnable map.\n"));
	free_map(game->map);
	readmap(str, game);
	return (0);
}
