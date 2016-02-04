/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dir_content.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 17:24:27 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/04 14:55:03 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_DIR_CONTENT_H
# define T_DIR_CONTENT_H

#include "dirent.h"
#include "libft.h"
#include <sys/stat.h>

typedef struct	s_dir_item
{
	char			*item_name;
	__uint8_t		item_type;
	struct dirent	*item;
	struct stat		prop;
	struct s_dir_item *next;
}				t_dir_item;

typedef struct	s_dir_content
{
	DIR						*cur_dir;
	t_dir_item				*items;
	char					*dir_name;
	int						is_dir;
	struct s_dir_content 	*next;
}				t_dir_content;

t_dir_content	*t_dir_new(DIR *cur_dir, char *dir_name);
t_dir_content	*get_last_item(t_dir_content *first);
void			t_dir_push(t_dir_content **first, t_dir_content *new);
void			t_dir_free_all(t_dir_content **cur);
void			close_dirs(t_dir_content *first);

t_dir_item		*t_item_new(struct dirent *item, char *path);
int				t_item_place(t_dir_item **first, t_dir_item *new);
int				t_item_rev_place(t_dir_item **first, t_dir_item *new);
void			t_item_push(t_dir_item **first, t_dir_item *new);

#endif
