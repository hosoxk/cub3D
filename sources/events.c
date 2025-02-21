/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:43:24 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/02/21 18:03:55 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	key_press(int keycode, t_game *game)
{
	printf("Keycode pressed: %d\n", keycode);
	if (keycode == ESC_KEY || keycode == Q_KEY)
	{
		free_mlx(game);
		close_window();
	}
	if (keycode == UP_ARROW || keycode == W_KEY)
		game->up_key = true;
	if (keycode == DOWN_ARROW || keycode == S_KEY)
		game->down_key = true;
	if (keycode == LEFT_ARROW || keycode == A_KEY)
		game->left_key = true;
	if (keycode == RIGHT_ARROW || keycode == D_KEY)
		game->right_key = true;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == UP_ARROW || keycode == W_KEY)
		game->up_key = false;
	if (keycode == DOWN_ARROW || keycode == S_KEY)
		game->down_key = false;
	if (keycode == LEFT_ARROW || keycode == A_KEY)
		game->left_key = false;
	if (keycode == RIGHT_ARROW || keycode == D_KEY)
		game->right_key = false;
	return (0);
}

int	game_loop(t_game *game)
{
	update_player(game);
	display(game);
	return (0);
}

// mouse changes the angle of the player
int	mouse_motion(int x, int y, t_game *game)
{
	int	delta_x;
	(void)y;

	delta_x = x - game->last_mouse_x;
	game->player.angle += delta_x * 0.005; // TODO scale for sensitivity
	// constrain the angle to [0, 2pi]
	if (game->player.angle > 2 * M_PI)
		game->player.angle -= 2 * M_PI;
	else if (game->player.angle < 0)
		game->player.angle += 2 * M_PI;
	game->last_mouse_x = x;
	mlx_mouse_move(game->mlx, game->window, 300, 300); // TODO center
	return (0);
}

void	setup_hooks(t_game *game)
{
	// closes window and exits program when red cross is used in window
	mlx_hook(game->window, 17, 0, close_window, NULL);
	// sets up key events
	mlx_hook(game->window, 2, 1L << 0, key_press, game);
	mlx_hook(game->window, 3, 1L << 1, key_release, game);
	mlx_mouse_move(game->mlx, game->window, game->mouse_x, game->mouse_y); // TODO center mouse according to window w & h
	mlx_hook(game->window, 6, 1L << 6, (int (*)(int, int, void *))mouse_motion, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}
