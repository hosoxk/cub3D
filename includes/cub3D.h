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

# define WIN_HEIGHT 521
# define WIN_WIDTH 1024
# define SIZE_P_MINIMAP 20
# define ESC_KEY 65307
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define DOWN_ARROW 65364
# define UP_ARROW 65362
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define Q_KEY 113

typedef struct	s_point
{
	int		x;
	int		y;
}	t_point;

typedef struct	s_player
{
	t_point		pos;
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
