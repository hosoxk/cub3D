/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:03:42 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/02/21 18:00:23 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include "../sources/libft/libft.h"
# include "../sources/minilibx-linux/mlx.h"

// *** COLOR CODES ***
# define BOLD_MAGENTA "\033[35m"
# define BOLD_RED "\033[31m"
# define BOLD_BLUE "\033[1;94m"
# define BOLD_GREEN "\033[32m"
# define RESET "\033[0m"

// *** GAME INFORMATION ***
# define WIN_HEIGHT 521
# define WIN_WIDTH 1024
# define SIZE_P_MINIMAP 20
# define MOVE_SPEED 0.003
# define MOUSE_SENSITIVITY 0.0004
# define MOUSE_RESET_MARGIN 15

// *** KEYCODES ***
# define ESC_KEY 65307
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define DOWN_ARROW 65364
# define UP_ARROW 65362
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define Q_KEY 113

// *** STRUCTS ***
typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_player
{
	t_point		pos;
	double		angle;
}	t_player;

typedef struct s_map
{
	char		**data;
	int			width;
	int			height;
}	t_map;

typedef struct s_game
{
	t_player	player;
	t_map		map;
	void		*mlx;
	void		*window;
	bool		up_key;
	bool		down_key;
	bool		left_key;
	bool		right_key;
	int			mouse_x;
	int			mouse_y;
	int			last_mouse_x;
}	t_game;

// *** INITIALIZING ***
t_game	init_game(void);

// *** SETUP EVENTS ***
void	setup_hooks(t_game *game);
int		display(t_game *game);
int		update_player(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		mouse_motion(int x, int y, t_game *game);

// *** FREEING ***
void	free_mlx(t_game *game);
int		close_window(void);

// *** UTILS ***
void	print_error(char *str);

#endif
