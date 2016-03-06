/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_l.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 12:49:31 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/05 21:27:12 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_L_H
# define OPTION_L_H

# include "t_dir_content.h"

typedef struct	s_litem
{
	char			*str;
	struct s_litem	*next;
}				t_litem;

void			print_ls_l(t_dir_item *items, char *params, int only_dirs);
void			t_litem_push(t_litem **first, t_litem *new);
void			free_ligtn(t_list **container);

char			*get_right_file_type(mode_t mode);
char			*add_mode_to_right(char *rights, char *add);
char			*get_maj_min(dev_t st_rdev);

t_litem			*get_rights(mode_t mode);
t_litem			*t_litem_new(char *str);

#endif
