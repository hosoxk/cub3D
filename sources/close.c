/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yde-rudd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:50:34 by yde-rudd          #+#    #+#             */
/*   Updated: 2025/02/21 16:53:17 by yde-rudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	close_window(void)
{
	exit(0);
	return (0);
}

void	print_error(char *str)
{
	printf(BOLD_RED"%s\n"RESET, str);
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
