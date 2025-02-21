/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:40:24 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/02/21 18:08:51 by yde-rudd         ###   ########.fr       */
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

static void	init_player(t_game *game)
{
	game->player.pos.x = 300;
	game->player.pos.y = 300;
	game->player.angle = 0;
}

t_game	init_game(void) //TODO
{
	printf(BOLD_BLUE"Initializing game\n"RESET);
	t_game		game;

	init_keys(&game);
	init_player(&game);
//	game.map = read_map();
	init_mlx(&game);
	return (game);
}
