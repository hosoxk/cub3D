/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:43:24 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/02/21 17:15:33 by yde-rudd         ###   ########.fr       */
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

void	setup_hooks(t_game *game)
{
	// closes window and exits program when red cross is used in window
	mlx_hook(game->window, 17, 0, close_window, NULL);
	// sets up key events
	mlx_hook(game->window, 2, 1L << 0, key_press, game);
	mlx_hook(game->window, 3, 1L << 1, key_release, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}
