/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 21:45:38 by carlnysten        #+#    #+#             */
/*   Updated: 2022/06/22 11:17:46 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# define MAX_HEAT 100000
# define MAX_HEATSUM 4294967295

# define FALSE 0
# define TRUE 1

# define ERROR "Error."
# define ERROR_PLAYER_INFO "Bad player info."
# define ERROR_MAP_DIMENSIONS "Bad map dimensions."
# define ERROR_MAP_INFO "Bad map info."
# define ERROR_PIECE_INFO "Bad piece info."

# include "libft.h"

typedef unsigned char	t_bool;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_piece
{
	int		cols;
	int		rows;
	char	**data;
}	t_piece;

typedef struct s_buffer
{
	char	*data;
	size_t	size;
}	t_buffer;

typedef struct s_queue
{
	t_pos	*data;
	int		size;
	int		push;	
	int		pop;	
}	t_queue;

typedef struct s_info
{
	int				player;
	int				opponent;
	int				nrows;
	int				ncols;
	int				first_round;
	char			**map;
	unsigned int	**heatmap;
	t_bool			**visited;
	size_t			visited_size;
	t_bool			**searched;
	t_queue			queue;
	t_piece			*piece;
	t_buffer		buffer;
}	t_info;

int				are_valid_ids(t_info *info, int i, int j);
void			die(t_info *info, char *error_msg);
int				can_place_piece(t_pos pos,
					t_info *info, t_pos ppos, int overlap);
void			free_heatmap(unsigned int **heatmap, int rows, int cols);
void			free_string_array(char **array, int rows, int cols);
void			get_player_number(t_info *info);
void			get_map_dimensions(t_info *info);
void			get_map_info(t_info *info);
void			get_piece_info(t_info *info);
int				is_player(char c, int player);
unsigned int	**new_heatmap(int rows, int cols);
t_info			*new_info(void);
t_piece			*new_piece(void);
t_pos			*new_pos_array(int nrows, int ncols);
char			**new_string_array(int rows, int cols);
char			player_symbol_lower(int player);
char			player_symbol(int player);
void			print_heatmap(t_info *info);
void			print_map(t_info *info);
void			push_to_queue(t_info *info, int i, int j);
t_pos			pop_from_queue(t_info *info);
int				queue_has_next(t_info *info);
void			reset_visited(t_info *info);
void			reset_queue(t_info *info);
void			send_command(t_pos *pos);
void			skip_line(t_info *info);
void			solve(t_info *info);
t_bool			**boolean_array(int n_rows, int n_cols);
void			update_heatmap(t_info *info);

#endif
