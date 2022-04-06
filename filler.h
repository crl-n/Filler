/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 21:45:38 by carlnysten        #+#    #+#             */
/*   Updated: 2022/04/06 14:13:46 by cnysten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# define MAX_HEAT 1000.0

typedef enum e_dir
{
	n,
	ne,
	e,
	se,
	s,
	sw,
	w,
	nw,
} t_dir;

typedef	struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_info
{
	int				fd;
	int				player;
	int				opponent;
	int				nrows;
	int				ncols;
	char			**map;
	unsigned int	**heatmap;
	t_pos			*cmd;
	t_pos			*center;
	t_pos			*prev;
}	t_info;

typedef struct s_piece
{
	int		cols;
	int		rows;
	char	**data;
}	t_piece;

int				can_place_piece(int x, int y, t_info *info, t_piece *piece);
t_pos			*find_in_map(t_info *info, char c);
void			free_heatmap(unsigned int **heatmap, int rows, int cols);
void			free_string_array(char **array, int rows, int cols);
void			get_player_number(t_info *info);
void			get_map_dimensions(t_info *info);
void			get_map_info(t_info *info);
void			get_piece_info(t_piece *piece, t_info *info);
int				is_player(char c, int player);
unsigned int	**new_heatmap(int rows, int cols);
t_info			*new_info(void);
t_piece			*new_piece(void);
t_pos			*new_pos(int x, int y);
char			**new_string_array(int rows, int cols);
char			player_symbol_lower(int player);
char			player_symbol(int player);
void			send_command(t_info *info);
void			skip_line(t_info *info);
void			skip_opponent_info(t_info *info);
void			think(t_info *info, t_piece *piece);
void			update_heatmap(t_info *info);
void			print_heatmap(t_info *info);

#endif
