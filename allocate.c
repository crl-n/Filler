/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlnysten <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 22:56:59 by carlnysten        #+#    #+#             */
/*   Updated: 2022/03/26 22:59:24 by carlnysten       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "libft.h"
#include <stdlib.h>

t_info	*new_info(void)
{
	t_info	*info;

	info = (t_info *) malloc(sizeof (t_info));
	if (!info)
		return (NULL);
	ft_bzero(info, sizeof (t_info));
	return (info);
}

t_piece	*new_piece(void)
{
	t_piece	*piece;

	piece = (t_piece *) malloc(sizeof (t_piece));
	if (!piece)
		return (NULL);
	ft_bzero(piece, sizeof (t_piece));
	return (piece);
}
