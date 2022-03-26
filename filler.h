/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 21:45:38 by carlnysten        #+#    #+#             */
/*   Updated: 2022/03/26 22:59:31 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

typedef struct s_info
{
	int	fd;
	int	player;
	int	nrows;
	int	ncols;
}	t_info;

typedef struct s_piece
{
	int		cols;
	int		rows;
	char	**data;
}	t_piece;

t_info	*new_info(void);
t_piece	*new_piece(void);

#endif
