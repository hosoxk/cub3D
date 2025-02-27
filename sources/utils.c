#include "../includes/cub3D.h"

void	free_mlx(t_game	*game)
{
	printf(BOLD_BLUE"Freeing MLX\n"RESET);
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
}

void	free_game(t_game *game)
{
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		free(game->screen_buffer[y]);
		y++;
	}
	free(game->screen_buffer);
	free_mlx(game);
}
