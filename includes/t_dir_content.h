/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dir_content.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 17:24:27 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/26 14:13:20 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_DIR_CONTENT_H
# define T_DIR_CONTENT_H

#include "dirent.h"
#include "libft.h"
#include <sys/stat.h>

typedef struct	s_dir_content
{
	DIR						*cur_dir;
	struct dirent			**items;
	char					*dir_name;
	struct stat				*props;
	struct s_dir_content 	*next;
}				t_dir_content;

t_dir_content	*t_dir_new(DIR *cur_dir, char *dir_name);
t_dir_content	*get_last_item(t_dir_content *first);
void			t_dir_push(t_dir_content **first, t_dir_content *new);
void			print_name_dir(t_dir_content *first);
void			switch_items(t_dir_content *first, t_dir_content *last);
void			sort_t_dir(t_dir_content *lst);
void			t_dir_add_file(t_dir_content **first,
		struct stat file, char *dir_name);


#endif
