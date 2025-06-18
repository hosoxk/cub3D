/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:47:17 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/03/08 01:36:01 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO	ERRORS; "Error\n" followed by explicit error message !!!!!!!!!!!!!!
// TODO can add a lot of t_point structs

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
	if (argc != 2 || !argv[1])
		return (print_error("Correct usage: <./executable> <map.cub>"), false);
	if (!is_cub_file(argv[1]))
		return (print_error("Error: file must be a .cub extension"), false);
	return (true);
}

static void	draw_pixel(t_game *game, int x, int y, u_int32_t color)
{
	if (x >= WIN_WIDTH || y >= WIN_HEIGHT ||
			x <= 0 || y <= 0) // TODO ;radius hardcoded
		return ;
	if (game->screen_buffer[y][x] != color)
	{
		mlx_pixel_put(game->mlx, game->window, x, y, color);
		game->screen_buffer[y][x] = color;
	}
}

static void	draw_player(t_game *game)
{
	int	radius;
	int	x;
	int	y;

	radius = 5; // TODO eventually size according to screen
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if ((x * x + y * y) <= (radius * radius))
			{
				draw_pixel(game, game->player.pos.x + x, game->player.pos.y + y, 0xFF000);
			}
			x++;
		}
		y++;
	}
}

static bool	is_valid_move(t_point point)
{
	if ((point.x > 0 && point.x < WIN_WIDTH - 1) && (point.y > 0 && point.y < WIN_HEIGHT - 1))
		return (true);
	return (false);
}

static void	clear_prev_player(t_game *game)
{
	int	radius;
	int	x;
	int	y;

	radius = 5; // TODO eventually size according to screen
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if ((x * x + y * y) <= (radius * radius))
			{
				draw_pixel(game, game->player.pos.x + x, game->player.pos.y + y, 0x000000);
			}
			x++;
		}
		y++;
	}
}

// TODO turn into bool
int	update_player(t_game *game)
{
	double	cos_angle;
	double	sin_angle;
	t_point	proposed;

	proposed.x = game->player.pos.x;
	proposed.y = game->player.pos.y;
	cos_angle = cos(game->player.angle);
	sin_angle = sin(game->player.angle);
	if (game->up_key)
	{
		proposed.x += MOVE_SPEED * cos_angle;
		proposed.y += MOVE_SPEED * sin_angle;
	}
	if (game->down_key)
	{
		proposed.x -= MOVE_SPEED * cos_angle;
		proposed.y -= MOVE_SPEED * sin_angle;
	}
	if (game->left_key)
	{
		proposed.x += MOVE_SPEED * sin_angle;
		proposed.y -= MOVE_SPEED * cos_angle;
	}
	if (game->right_key)
	{
		proposed.x -= MOVE_SPEED * sin_angle;
		proposed.y += MOVE_SPEED * cos_angle;
	}
	// clamp players pos within screen boundaries
	if (is_valid_move(proposed))
	{
		clear_prev_player(game);
		game->player.prev_pos.x = game->player.pos.x;
		game->player.prev_pos.y = game->player.pos.y;
		game->player.pos.x = proposed.x;
		game->player.pos.y = proposed.y;
	}
	// Update player angle
	if (game->last_mouse_x != WIN_WIDTH / 2)
	{
		int delta_x = game->last_mouse_x - (WIN_WIDTH / 2);
        
		game->player.angle += delta_x * MOUSE_SENSITIVITY;
		while (game->player.angle > 2 * M_PI)
			game->player.angle -= 2 * M_PI;
		while (game->player.angle < 0)
			game->player.angle += 2 * M_PI;
		game->last_mouse_x = WIN_WIDTH / 2;
	}
	game->player.prev_angle = game->player.angle;
	return (0);
}

int	display(t_game *game)
{
	draw_player(game);
//	draw_screen(); // TODO
//	draw_minimap(); // TODO
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!check_input(argc, argv))
		return (1);
	game = init_game();
	if (!parse_cub_file(argv[1], &game.map))
		return (free_game(&game), 1);
	print_map_data(&game.map);
	// *** SET UP EVENTS ***
	setup_hooks(&game);
	// *** GAME LOOP ***
	game.is_running = true;
	mlx_loop(game.mlx);
	free_game(&game);
	return (0);
}
