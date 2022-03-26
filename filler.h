/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 21:45:38 by carlnysten        #+#    #+#             */
/*   Updated: 2022/03/27 00:41:12 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

typedef struct s_info
{
	int		fd;
	int		player;
	int		nrows;
	int		ncols;
	char	**map;
}	t_info;

typedef struct s_piece
{
	int		cols;
	int		rows;
	char	**data;
}	t_piece;

void	free_string_array(char **array, int rows, int cols);
t_info	*new_info(void);
t_piece	*new_piece(void);
char	**new_string_array(int rows, int cols);
void	skip_line(void);
void	skip_opponent_info(t_info *info);

#endif
