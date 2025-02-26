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

static void	draw_pixel(t_game *game, int x, int y, u_int32_t color)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		if (game->screen_buffer[x][y] != color)
		{
			mlx_pixel_put(game->mlx, game->window, x, y, color);
			game->screen_buffer[x][y] = color;
		}
	}
}

// *** Bresenhams line drawing algorithm
static void	draw_line(t_game *game, t_point start, t_point end, u_int32_t color)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;

	dx = fabs(end.x - start.x); // calculate absolute diff in x
	dy = fabs(end.y - start.y); // calculate absolute diff in y
	sx = (start.x < end.x) ? 1 : -1; // step direction in x
	sy = (start.y < end.y) ? 1 : -1; // step direction in y
	err = dx - dy; // error value
	x = start.x;
	y = start.y;
	while (1)
	{
		draw_pixel(game, x, y, color);
		if (x == end.x && y == end.y)
			break ;
		int	e2;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y += sy;
		}
	}
}

static void	draw_player(t_game *game)
{
	int	line_length; // TODO can be removed after

	line_length = 50;
	// Calculate the endpoint of the line based on the player's angle
    int end_x = game->player.pos.x + line_length * cos(game->player.angle);
    int end_y = game->player.pos.y + line_length * sin(game->player.angle);

    // Convert positions to integers for rendering
    int player_x = (int)round(game->player.pos.x);
    int player_y = (int)round(game->player.pos.y);
    int rounded_end_x = (int)round(end_x);
    int rounded_end_y = (int)round(end_y);
	// draw the player
	draw_pixel(game, player_x, player_y, 0xFF000);
	// draw the angle representation
	  t_point end = {rounded_end_x, rounded_end_y};
	draw_line(game, game->player.pos, end, 0xFFFFFF);
}

int	update_player(t_game *game)
{
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(game->player.angle);
	sin_angle = sin(game->player.angle);
	if (game->up_key)
	{
		game->player.pos.x += MOVE_SPEED * cos_angle;
		game->player.pos.y += MOVE_SPEED * sin_angle;
	}
	if (game->down_key)
	{
		game->player.pos.x -= MOVE_SPEED * cos_angle;
		game->player.pos.y -= MOVE_SPEED * sin_angle;
	}
	if (game->left_key)
	{
		game->player.pos.x += MOVE_SPEED * sin_angle;
		game->player.pos.y -= MOVE_SPEED * cos_angle;
	}
	if (game->right_key)
	{
		game->player.pos.x -= MOVE_SPEED * sin_angle;
		game->player.pos.y += MOVE_SPEED * cos_angle;
	}
//	printf("Player position updated;\nx: %f\ny: %f\n", game->player.pos.x, game->player.pos.y);
	return (0);
}

static void	clear_prev_player_and_line(t_game *game)
{
	    // Clear the previous player position (set it back to background color)
    int prev_player_x = (int)round(game->player.prev_pos.x);
    int prev_player_y = (int)round(game->player.prev_pos.y);
    draw_pixel(game, prev_player_x, prev_player_y, 0x000000); // Background color

    // Clear the previous line
    int prev_end_x = game->player.prev_pos.x + 50 * cos(game->player.prev_angle);
    int prev_end_y = game->player.prev_pos.y + 50 * sin(game->player.prev_angle);
	t_point end = {(int)round(prev_end_x), (int)round(prev_end_y)};
    draw_line(game, game->player.prev_pos, end, 0x000000);

    // Update the previous player position and angle
    game->player.prev_pos.x = game->player.pos.x;
    game->player.prev_pos.y = game->player.pos.y;
    game->player.prev_angle = game->player.angle;
}

int	display(t_game *game)
{
//	mlx_clear_window(game->mlx, game->window);
	clear_prev_player_and_line(game);
//	draw_minimap(); // TODO
	draw_player(game);
	//printf(BOLD_RED"Players angle: %f\n"RESET, game->player.angle);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!check_input(argc, argv))
		return (1);
	game = init_game();	//TODO
	// *** SET UP EVENTS ***
	setup_hooks(&game);
	// *** GAME LOOP ***
	mlx_loop(game.mlx);
	free_mlx(&game);
	return (0);
}
