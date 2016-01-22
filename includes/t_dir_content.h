/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dir_content.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 17:24:27 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/22 13:08:43 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_DIR_CONTENT_H
# define T_DIR_CONTENT_H

#include "dirent.h"
#include "libft.h"

typedef struct	s_dir_content
{
	DIR						*cur_dir;
	struct dirent			**items;
	char					*dir_name;
	struct s_dir_content 	*next;
}				t_dir_content;

t_dir_content	*t_dir_new(DIR *cur_dir);
void			t_dir_push(t_dir_content **first, t_dir_content *new);

#endif
