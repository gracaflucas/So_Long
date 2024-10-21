/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 18:53:13 by lufiguei          #+#    #+#             */
/*   Updated: 2024/09/07 18:53:14 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	loadmap(int fd, char **buffer);
static int	key_hook(int keysym, t_data *game);

int	main(int argc, char **argv)
{
	t_data	game;

	if (argc != 2)
		return (ft_printf("Error\nWrong Command Line Argument.\n"));
	init_struct(&game);
	readmap(argv[1], &game);
	if (valid_map(argv[1], &game) == 0)
	{
		game.init = mlx_init();
		if (game.init == NULL)
			return (ft_printf("Error\nInitialization failed.\n"));
		game.window = mlx_new_window(game.init,
				game.width * PXL, game.height * PXL, "So_long");
		if (game.window == NULL)
		{
			mlx_destroy_display(game.init);
			free(game.init);
			return (ft_printf("Error\nWindow creation failed.\n"));
		}
		init_game(&game);
		mlx_key_hook(game.window, &key_hook, &game);
		mlx_hook(game.window, DestroyNotify, 0, close_window, &game);
		mlx_loop(game.init);
	}
	return (free_map(game.map));
}

static int	key_hook(int keysym, t_data *game)
{
	if (keysym == XK_Escape)
		close_window(game);
	if (keysym == XK_A || keysym == XK_a || keysym == XK_Left)
		if (game->py > 0 && game->map[game->px][game->py - 1] != '1')
			game->moves += update_map(game, game->px, game->py - 1);
	if (keysym == XK_D || keysym == XK_d || keysym == XK_Right)
		if (game->py < game->width - 1
			&& game->map[game->px][game->py + 1] != '1')
			game->moves += update_map(game, game->px, game->py + 1);
	if (keysym == XK_W || keysym == XK_w || keysym == XK_Up)
		if (game->px > 0 && game->map[game->px - 1][game->py] != '1')
			game->moves += update_map(game, game->px - 1, game->py);
	if (keysym == XK_S || keysym == XK_s || keysym == XK_Down)
		if (game->px < game->height - 1
			&& game->map[game->px + 1][game->py] != '1')
			game->moves += update_map(game, game->px + 1, game->py);
	ft_printf("Moves: %d\n", game->moves);
	mlx_clear_window(game->init, game->window);
	render_map(game);
	return (0);
}

int	close_window(t_data *game)
{
	destroy_images(game);
	mlx_destroy_window(game->init, game->window);
	mlx_destroy_display(game->init);
	free_map(game->map);
	free(game->init);
	game->init = NULL;
	exit(0);
}

int	readmap(char *argv, t_data *game)
{
	int		fd;
	char	*buffer;

	buffer = ft_strdup("");
	if (buffer == NULL)
		return (ft_printf("Error\nMemory allocation failed.\n"));
	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		free(buffer);
		return (ft_printf("Error\nCouldnt open file.\n"));
	}
	if (loadmap(fd, &buffer))
	{
		close(fd);
		return (ft_printf("Error\nLoading map failed.\n"));
	}
	close(fd);
	if (is_double_newline(buffer) == 2)
		return (free(buffer), ft_printf("Error\nmap contains empty line.\n"));
	game->map = ft_split(buffer, '\n');
	free(buffer);
	if (game->map == NULL)
		return (ft_printf("Error\nMap Split failed.\n"));
	return (0);
}

static int	loadmap(int fd, char **buffer)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		tmp = *buffer;
		*buffer = ft_strjoin(*buffer, line);
		free(tmp);
		free(line);
		if (*buffer == NULL)
		{
			close (fd);
			return (ft_printf("Error\nMemory allocation failed.\n"));
		}
	}
	return (0);
}
