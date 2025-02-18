#include "../includes/cub3D.h"

static void	print_error(char *str)
{
	printf(BOLD_RED"%s\n"RESET, str);
}

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

void	free_mlx(t_game	*game)
{
	printf(BOLD_BLUE"Freeing MLX\n"RESET);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	mlx_destroy_display(game->mlx);
	if (game->mlx)
		free(game->mlx);
}

static void	init_mlx(t_game *game)
{
	printf(BOLD_BLUE"Initializing MLX\n"RESET);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		perror("Error: could not initialize MLX\n");
		exit(1);
	}
	game->window = mlx_new_window(game->mlx, 1024, 512, "cub3D"); //TODO //to be fixed
	if (!game->window)
	{
		free_mlx(game);
		print_error("Error: could not create a window");
		exit(1);
	}
}

static void	draw_player(t_game game)
{
	mlx_pixel_put(game.mlx, game.window, game.player.pos.x, game.player.pos.y, 0xFFFFF);
}

static int	close_window(void)
{
	exit(0);
	return (0);
}

t_game	init_game(void) //TODO
{
	printf(BOLD_BLUE"Initializing game\n"RESET);
	t_game		game;
//	t_player	player;

	game.player.pos.x = 300;
	game.player.pos.y = 300;

//	game.map = read_map();
	init_mlx(&game);
	return (game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (!check_input(argc, argv))
		return (1);
	game = init_game();	//TODO
	mlx_hook(game.window, 17, 0, close_window, NULL);
	mlx_loop(game.mlx);
	draw_player(game);
	free_mlx(&game);
	return (0);
}
