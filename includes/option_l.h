/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_l.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 12:49:31 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/26 14:46:35 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_L_H
# define OPTION_L_H

#include "t_dir_content.h"

typedef struct	s_litem
{
	char			*str;
	struct s_litem	*next;
}				t_litem;

void		print_ls_l(t_dir_item *items, char *params, int only_dirs);

void		t_litem_push(t_litem **first, t_litem *new);
t_litem		*t_litem_new(char *str);
#endif
