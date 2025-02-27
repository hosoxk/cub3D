/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:40:24 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/02/27 00:12:55 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	init_mlx(t_game *game)
{
	printf(BOLD_BLUE"Initializing MLX\n"RESET);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		perror("Error: could not initialize MLX\n");
		exit(1);
	}
	game->window = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->window)
	{
		free_mlx(game);
		print_error("Error: could not create a window");
		exit(1);
	}
}

static void	init_keys(t_game *game)
{
	game->up_key = false;
	game->down_key = false;
	game->left_key = false;
	game->right_key = false;
	game->mouse_x = WIN_WIDTH / 2;
	game->mouse_y = WIN_HEIGHT / 2;
	game->last_mouse_x = game->mouse_x;
}

// TODO turn into init_player_and_map
static void	init_player(t_game *game)
{
	game->player.pos.x = WIN_WIDTH / 2;
	game->player.pos.y = WIN_HEIGHT / 2;
	game->player.angle = 0.0;
	game->player.prev_pos.x = game->player.pos.x;
	game->player.prev_pos.y = game->player.pos.y;
	game->player.prev_angle = game->player.angle;
}

static bool	init_screen_buffer(t_game *game)
{
	// Dynamically allocate screen_buffer
	game->screen_buffer = malloc(WIN_HEIGHT * sizeof(u_int32_t *));
	if (!game->screen_buffer)
		return (print_error("Failed to allocate screen buffer"), false);
	for (int y = 0; y < WIN_HEIGHT; y++)
	{
		game->screen_buffer[y] = malloc(WIN_WIDTH * sizeof(u_int32_t));
		if (!game->screen_buffer[y])
			return (print_error("Failed to allocate screen buffer row"), false);
		ft_memset(game->screen_buffer[y], 0, WIN_WIDTH * sizeof(u_int32_t));
	}
	return (true);
}

t_game	init_game(void) //TODO
{
	printf(BOLD_BLUE"Initializing game\n"RESET);
	t_game		game;

	init_mlx(&game);
	init_screen_buffer(&game);
	init_keys(&game);
	init_player(&game);
//	game.map = init_map();
	return (game);
}
