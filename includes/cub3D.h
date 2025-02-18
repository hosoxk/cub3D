#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include "../sources/libft/libft.h"
# include "../sources/minilibx-linux/mlx.h"

# define BOLD_MAGENTA "\033[35m"
# define BOLD_RED "\033[31m"
# define BOLD_BLUE "\033[1;94m"
# define BOLD_GREEN "\033[32m"
# define RESET "\033[0m"

typedef struct	s_point
{
	int		x;
	int		y;
}	t_point;

typedef struct	s_player
{
	t_point		position;
}	t_player;

typedef struct	s_map
{
	char		**data;
	int			width;
	int			height;
}	t_map;

typedef struct	s_game
{
	t_player	player;
	t_map		map;
	void		*mlx;
	void		*window;
}	t_game;

#endif
