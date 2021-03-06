/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dir_content.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 17:24:27 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/06 00:38:44 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_DIR_CONTENT_H
# define T_DIR_CONTENT_H

# include "dirent.h"
# include "libft.h"
# include <sys/stat.h>

typedef struct	s_dir_item
{
	char				*path;
	char				*item_name;
	struct dirent		*item;
	struct stat			prop;
	struct s_dir_item	*next;
}				t_dir_item;

typedef struct	s_dir_content
{
	DIR						*cur_dir;
	t_dir_item				*items;
	char					*dir_name;
	int						is_lfile;
	struct stat				dir_prop;
	struct s_dir_content	*next;
}				t_dir_content;

t_dir_content	*t_dir_new(DIR *cur_dir, char *dir_name, int is_lfile);
void			t_dir_free_all(t_dir_content **cur);
void			close_dirs(t_dir_content *first);

t_dir_item		*t_item_new(char *d_name, char *path);
t_dir_item		*t_item_sort(t_dir_item **item, t_dir_item *new, char *params);
void			t_item_rev_sort(t_dir_item *first, t_dir_item *new_next
					, t_dir_item **new_first);
t_dir_item		*t_item_place(t_dir_item **first, t_dir_item *new);
t_dir_item		*t_item_time_place(t_dir_item **first, t_dir_item *new);
void			t_item_free_all(t_dir_item **cur);
t_dir_content	*t_dir_place(t_dir_content **first, t_dir_content *new);
t_dir_content	*t_dir_rev_place(t_dir_content **first, t_dir_content *new);
t_dir_item		*t_file_new(char *d_name);
#endif
