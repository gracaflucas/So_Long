/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:34:05 by lufiguei          #+#    #+#             */
/*   Updated: 2024/10/02 13:34:16 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	load_images(t_data *game)
{
	destroy_images(game);
	game->images.exit_img.img_ptr = mlx_xpm_file_to_image(game->init, EXIT_0,
			&game->images.exit_img.width, &game->images.exit_img.height);
	game->images.floor_img.img_ptr = mlx_xpm_file_to_image(game->init, FLOOR,
			&game->images.floor_img.width, &game->images.floor_img.height);
	game->images.wall_img.img_ptr = mlx_xpm_file_to_image(game->init, WALL,
			&game->images.wall_img.width, &game->images.wall_img.height);
	game->images.player_img.img_ptr = mlx_xpm_file_to_image(game->init, PLAYER,
			&game->images.player_img.width, &game->images.player_img.height);
	game->images.col_img.img_ptr = mlx_xpm_file_to_image(game->init, COL,
			&game->images.col_img.width, &game->images.col_img.height);
	if (!game->images.exit_img.img_ptr || !game->images.col_img.img_ptr
		|| !game->images.floor_img.img_ptr || !game->images.wall_img.img_ptr
		|| !game->images.player_img.img_ptr)
	{
		destroy_images(game);
		return ;
	}
}

static void	render_image(t_data *game, t_image *image, int x, int y)
{
	if (image->img_ptr)
		mlx_put_image_to_window(game->init, game->window,
			image->img_ptr, x * PXL, y * PXL);
}

void	render_map(t_data *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == 'E')
				render_image(game, &game->images.exit_img, j, i);
			else if (game->map[i][j] == '0')
				render_image(game, &game->images.floor_img, j, i);
			else if (game->map[i][j] == '1')
				render_image(game, &game->images.wall_img, j, i);
			else if (game->map[i][j] == 'P')
				render_image(game, &game->images.player_img, j, i);
			else if (game->map[i][j] == 'C')
				render_image(game, &game->images.col_img, j, i);
		}
	}
}

int	update_map(t_data *game, int x, int y)
{
	int			old_x;
	int			old_y;
	static int	was_exit;

	old_x = game->px;
	old_y = game->py;
	if (game->map[x][y] == 'E' && game->collectable == 0)
		return (ft_printf("Moves: %d\n", game->moves + 1), close_window(game));
	if (game->map[x][y] == 'C')
	{
		game->map[x][y] = '0';
		game->collectable -= 1;
	}
	game->px = x;
	game->py = y;
	if (was_exit == 1)
		game->map[old_x][old_y] = 'E';
	else
		game->map[old_x][old_y] = '0';
	if (game->map[x][y] == 'E')
		was_exit = 1;
	else
		was_exit = 0;
	game->map[x][y] = 'P';
	return (1);
}

void	init_game(t_data *game)
{
	load_images(game);
	render_map(game);
}
