/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:47:17 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/02/21 17:27:08 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static bool	is_cub_file(const char *filename)
{
	const char	*dot;

	dot = ft_strrchr(filename, '.');
	if (dot && (ft_strcmp(dot, ".cub") == 0))
		return (true);
	else
		return (false);
}

static bool	check_input(int argc, char **argv)
{
	(void)argv;
	if (argc != 2 || !is_cub_file(argv[1]))
		return (print_error("Correct usage: <./executable> <map.cub>"), false);
	return (true);
}

static void	draw_player(t_game *game)
{
	mlx_pixel_put(game->mlx, game->window, game->player.pos.x,
		game->player.pos.y, 0xFF000);
}

int	update_player(t_game *game)
{
	if (game->up_key)
		game->player.pos.y -= MOVE_SPEED;
	if (game->down_key)
		game->player.pos.y += MOVE_SPEED;
	if (game->left_key)
		game->player.pos.x -= MOVE_SPEED;
	if (game->right_key)
		game->player.pos.x += MOVE_SPEED;
	printf("Player position updated;\nx: %f\ny: %f\n", game->player.pos.x, game->player.pos.y);
	return (0);
}

int	display(t_game *game)
{
	mlx_clear_window(game->mlx, game->window);
	draw_player(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!check_input(argc, argv))
		return (1);
	game = init_game();	//TODO
	printf("Player position;\nx: %f\ny: %f\n", game.player.pos.x, game.player.pos.y);
	// *** SET UP EVENTS ***
	setup_hooks(&game);
//	display(&game);
	// *** GAME LOOP ***
	mlx_loop(game.mlx);
	free_mlx(&game);
	return (0);
}
