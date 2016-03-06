/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 12:49:04 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/06 00:23:13 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include "option_l.h"
#include "colors.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/acl.h>
#include <option_g.h>

static t_litem	*get_date(t_dir_item *item)
{
	char	**tmp;
	t_litem	*date;
	char	**cur_time;
	time_t	today;

	date = NULL;
	today = time(0);
	cur_time = ft_strsplit(ctime(&today), ' ');
	tmp = ft_strsplit(ctime(&item->prop.st_mtime), ' ');
	t_litem_push(&date, t_litem_new(ft_strdup(tmp[1])));
	t_litem_push(&date, t_litem_new(ft_strdup(tmp[2])));
	if ((today - item->prop.st_mtime) >= 15768000
			|| (today - item->prop.st_mtime) < 0)
		t_litem_push(&date, t_litem_new(ft_strsub(tmp[4], 0
						, ft_strchr(tmp[4], '\n') - tmp[4])));
	else
		t_litem_push(&date, t_litem_new(ft_strsub(tmp[3], 0, 5)));
	ft_freetab(tmp);
	ft_freetab(cur_time);
	return (date);
}

static t_litem	*print_list_item(t_dir_item *item, int *total, char *params)
{
	t_litem	*line;
	int		i;

	i = 0;
	line = NULL;
	t_litem_push(&line, get_rights(item->prop.st_mode));
	t_litem_push(&line, t_litem_new(ft_itoa(item->prop.st_nlink)));
	if (getpwuid(item->prop.st_uid) != NULL)
		t_litem_push(&line,
				t_litem_new(ft_strdup(getpwuid(item->prop.st_uid)->pw_name)));
	else
		t_litem_push(&line, t_litem_new(ft_itoa((long)(item->prop.st_uid))));
	if (getgrgid(item->prop.st_gid) != NULL)
		t_litem_push(&line,
				t_litem_new(ft_strdup(getgrgid(item->prop.st_gid)->gr_name)));
	else
		t_litem_push(&line, t_litem_new(ft_itoa((long)(item->prop.st_gid))));
	if (S_ISCHR(item->prop.st_mode) || S_ISBLK(item->prop.st_mode))
		t_litem_push(&line, t_litem_new(get_maj_min(item->prop.st_rdev)));
	else
		t_litem_push(&line, t_litem_new(ft_itoa((long)item->prop.st_size)));
	t_litem_push(&line, get_date(item));
	t_litem_push(&line, t_litem_new(get_item_name(item, params)));
	*(total) += (int)(item->prop.st_blocks);
	return (line);
}

static int		*max_size_elem(t_list *container)
{
	int		*spaces;
	t_litem	*index;
	int		i;
	size_t	cur;

	spaces = (int *)malloc(sizeof(int) * 10);
	ft_bzero(spaces, sizeof(int) * 10);
	i = 0;
	cur = 0;
	index = NULL;
	while (container)
	{
		index = container->content;
		i = 0;
		while (index)
		{
			cur = ft_strlen(index->str);
			if (spaces[i] <= (int)cur)
				spaces[i] = cur;
			index = index->next;
			i++;
		}
		container = container->next;
	}
	return (spaces);
}

static void		print_padded_item(t_list *container, int *spaces)
{
	t_litem	*index;
	int		i;

	i = 0;
	index = NULL;
	while (container)
	{
		i = 0;
		index = container->content;
		while (index)
		{
			if (i > 0 && i != 4 && i != 7 && i != 6)
				ft_putchar(' ');
			if (index->next && i != 0 && i != 2 && i != 3 && i != 5)
				ft_print_rep(' ', (spaces[i] - ft_strlen(index->str) + 1));
			ft_putstr(index->str);
			if (index->next && i != 0 && i != 1 && i != 4
					&& i != 5 && i != 6 && i != 7)
				ft_print_rep(' ', (spaces[i] - ft_strlen(index->str) + 1));
			index = index->next;
			i++;
		}
		free_ligtn(&container);
		ft_putchar('\n');
	}
}

void			print_ls_l(t_dir_item *items, char *params, int only_dirs)
{
	int		*spaces;
	int		total;
	t_list	*container;

	container = NULL;
	total = 0;
	while (items)
	{
		ft_lstpush(&container, ft_lstnew(print_list_item(items, &total, params),
					sizeof(t_litem)));
		items = items->next;
	}
	if (container && only_dirs)
	{
		ft_putstr("total ");
		ft_putnbr((total));
		ft_putchar('\n');
	}
	spaces = max_size_elem(container);
	print_padded_item(container, spaces);
	free(spaces);
}
