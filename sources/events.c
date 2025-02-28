/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:43:24 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/03/01 00:17:11 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	key_press(int keycode, t_game *game)
{
	if (!game)
		return (print_error("Trying to access out of bound memory"), 0);
	if (keycode == ESC_KEY || keycode == Q_KEY)
	{
		free_game(game);
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

int	mouse_motion(int x, int y, t_game *game)
{
	static clock_t last_reset_time = 0;
	clock_t current_time = clock();
	double elapsed_time = (double)(current_time - last_reset_time) / CLOCKS_PER_SEC;
	t_point	center;

	(void)y;
	if (!game)
		return (0);
	center.x = WIN_WIDTH / 2;
	center.y = WIN_HEIGHT / 2;
	game->last_mouse_x = x;
	// Reset the mouse only if it moves outside the margin and enough time has passed
	if (fabs(x - center.x) > MOUSE_RESET_MARGIN  || fabs(y - center.y) > MOUSE_RESET_MARGIN)
	{
		if (elapsed_time >= 1.0 / MOUSE_RESET_THROTTLE)
		{
			printf("Resetting Mouse to Center (%f, %f)\n", center.x, center.y);
			game->last_mouse_x = center.x;
			mlx_mouse_move(game->mlx, game->window, center.x, center.y);
			last_reset_time = current_time;
		}
	}
	return (0);
}

int	game_loop(t_game *game)
{
	clock_t last_frame_time = clock();
	double delta_time = 0;

    clock_t current_time = clock();
    delta_time = (current_time - last_frame_time) / (double)CLOCKS_PER_SEC;
    last_frame_time = current_time;

    // Limit the frame rate
    if (delta_time < MIN_FRAME_TIME)
	{	
		// Update game state
		update_player(game);
		// Render the frame
		display(game);
	}
	return (0);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->window, 17, 0, close_window, NULL);
	mlx_hook(game->window, 2, 1L << 0, key_press, game);
	mlx_hook(game->window, 3, 1L << 1, key_release, game);
	mlx_mouse_move(game->mlx, game->window, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_hook(game->window, 6, 1L << 6, (int (*)(int, int, void *))mouse_motion, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}
