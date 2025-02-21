/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:47:17 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/02/21 19:12:20 by yde-rudd         ###   ########.fr       */
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

static void	draw_line(t_game *game, int x1, int y1)
{
	int	x0;
	int	y0;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
//	int	current_x;
//	int	current_y;

	x0 = game->player.pos.x;
	y0 = game->player.pos.y;
	dx = abs(x1 - x0); // calculate absolute diff in x
	dy = abs(y1 - y0); // calculate absolute diff in y
	sx = (x0 < x1) ? 1 : -1; // step direction in x
	sy = (y0 < y1) ? 1 : -1; // step direction in y
	err = dx - dy; // error value
	while (1)
	{
		mlx_pixel_put(game->mlx, game->window, x0, y0, 0xFFFFFF);
		if (x0 == x1 && y0 == y1)
			break ;
		int	e2;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

static void	draw_player(t_game *game)
{
	int	end_x;
	int	end_y;
	int	line_length; // TODO can be removed after

	line_length = 50;
	// Calculate the endpoint of the line based on the player's angle
	end_x = game->player.pos.x + line_length * cos(game->player.angle);
	end_y = game->player.pos.y + line_length * sin(game->player.angle);
	mlx_pixel_put(game->mlx, game->window, game->player.pos.x,
		game->player.pos.y, 0xFF000);
	draw_line(game, end_x, end_y);
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
