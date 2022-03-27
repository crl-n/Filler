/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 21:45:38 by carlnysten        #+#    #+#             */
/*   Updated: 2022/03/27 12:27:28 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

typedef	struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_info
{
	int		fd;
	int		player;
	int		nrows;
	int		ncols;
	char	**map;
	double	**heat;
	char	*command;
	t_pos	*prev;
}	t_info;

typedef struct s_piece
{
	int		cols;
	int		rows;
	char	**data;
}	t_piece;

void	free_heatmap(char **heatmap, int rows, int cols);
void	free_string_array(char **array, int rows, int cols);
void	get_player_number(t_info *info);
void	get_map_dimensions(t_info *info);
void	get_map_info(t_info *info);
void	get_piece_info(t_piece *piece, t_info *info);
double	**new_heatmap(int rows, int cols);
t_info	*new_info(void);
t_piece	*new_piece(void);
t_pos	*new_pos(int x, int y);
char	**new_string_array(int rows, int cols);
char	player_symbol_lower(int player);
char	player_symbol(int player);
void	skip_line(t_info *info);
void	skip_opponent_info(t_info *info);

#endif
