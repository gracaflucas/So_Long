/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 18:53:20 by lufiguei          #+#    #+#             */
/*   Updated: 2024/09/07 18:53:21 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h> // open
# include <math.h>
# include <stdio.h> // perror
# include <stdlib.h> // malloc, free, exit
# include <string.h> // strerror
# include <unistd.h> // close, read, write
# include <X11/keysym.h>
# include <X11/X.h> // keypress macros
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

# define WALL "./textures/xpm/bush.xpm"
# define FLOOR "./textures/xpm/grass.xpm"
# define EXIT_0 "./textures/xpm/dekutree1.xpm"
# define COL "./textures/xpm/banana.xpm"
# define PLAYER "./textures/xpm/still.xpm"
# define PXL 32

typedef struct s_image
{
	void	*img_ptr;
	int		line_len;
	int		height;
	int		width;
}	t_image;

typedef struct s_images
{
	t_image	player_img;
	t_image	wall_img;
	t_image	floor_img;
	t_image	exit_img;
	t_image	col_img;
}	t_images;

typedef struct s_data
{
	void		*window;
	void		*init;
	char		**map;
	int			width;
	int			height;
	int			px;
	int			py;
	int			moves;
	int			player;
	int			collectable;
	int			bag;
	int			exit;
	int			exit_reached;
	t_images	images;
}	t_data;

int		valid_map(char *str, t_data *game);

int		llen_calc(t_data *game);

void	init_struct(t_data *game);

int		free_map(char **map);

int		readmap(char *argv, t_data *game);

void	render_map(t_data *game);

void	destroy_images(t_data *game);

void	init_game(t_data *game);

int		update_map(t_data *game, int x, int y);

int		close_window(t_data *game);

int		char_cmp(t_data *game);

int		is_double_newline(char *buffer);

#endif
