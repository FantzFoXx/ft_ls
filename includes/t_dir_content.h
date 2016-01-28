/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dir_content.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 17:24:27 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/28 11:38:36 by udelorme         ###   ########.fr       */
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
void			sort_t_dir(t_dir_content *lst);
void			sort_t_dir_elems(t_dir_content *lst);
void			switch_items(struct dirent **d1, struct dirent **d2);
void			switch_props(struct stat *s1, struct stat *s2);
void			switch_dirs(t_dir_content *first, t_dir_content *last);
void			t_dir_add_file(t_dir_content **first,
		struct stat file, char *dir_name);

void			t_dir_free_all(t_dir_content **cur);


#endif
