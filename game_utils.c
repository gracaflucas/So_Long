/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 18:32:52 by lufiguei          #+#    #+#             */
/*   Updated: 2024/09/28 18:32:55 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	img_init(t_image *image);

int	llen_calc(t_data *game)
{
	int	i;
	int	line_len;

	if (game->map == NULL || game->map[0] == NULL)
		return (2);
	i = 0;
	line_len = ft_strlen(game->map[i]);
	while (game->map[i] != NULL)
	{
		if ((int)ft_strlen(game->map[i]) != line_len)
			return (2);
		i++;
	}
	game->height = i;
	game->width = line_len;
	return (0);
}

void	init_struct(t_data *game)
{
	if (game == NULL)
		return ;
	game->window = NULL;
	game->init = NULL;
	game->map = NULL;
	game->width = 0;
	game->height = 0;
	game->px = 0;
	game->py = 0;
	game->moves = 0;
	game->player = 0;
	game->collectable = 0;
	game->bag = 0;
	game->exit = 0;
	game->exit_reached = 0;
	img_init(&game->images.col_img);
	img_init(&game->images.player_img);
	img_init(&game->images.wall_img);
	img_init(&game->images.exit_img);
	img_init(&game->images.floor_img);
}

static void	img_init(t_image *image)
{
	image->height = 0;
	image->img_ptr = NULL;
	image->line_len = 0;
	image->width = 0;
}

int	free_map(char **map)
{
	size_t	i;

	if (map == NULL)
		return (1);
	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
	return (0);
}

void	destroy_images(t_data *game)
{
	if (game->images.col_img.img_ptr)
		mlx_destroy_image(game->init, game->images.col_img.img_ptr);
	if (game->images.player_img.img_ptr)
		mlx_destroy_image(game->init, game->images.player_img.img_ptr);
	if (game->images.wall_img.img_ptr)
		mlx_destroy_image(game->init, game->images.wall_img.img_ptr);
	if (game->images.exit_img.img_ptr)
		mlx_destroy_image(game->init, game->images.exit_img.img_ptr);
	if (game->images.floor_img.img_ptr)
		mlx_destroy_image(game->init, game->images.floor_img.img_ptr);
	game->images.col_img.img_ptr = NULL;
	game->images.player_img.img_ptr = NULL;
	game->images.wall_img.img_ptr = NULL;
	game->images.floor_img.img_ptr = NULL;
	game->images.exit_img.img_ptr = NULL;
}
