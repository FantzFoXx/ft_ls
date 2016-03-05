/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 12:49:04 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/05 17:15:57 by udelorme         ###   ########.fr       */
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

static char		*add_mode_to_right(char *rights, char *add)
{
	char	*tmp;

	tmp = ft_strdup(rights);
	free(rights);
	rights = ft_strjoin(tmp, add);
	free(tmp);
	return (rights);
}

static char		*get_right_file_type(mode_t mode)
{
	char *rights;

	rights = NULL;
	if (S_ISDIR(mode))
		rights = ft_strdup("d");
	else if (S_ISCHR(mode))
		rights = ft_strdup("c");
	else if (S_ISFIFO(mode))
		rights = ft_strdup("p");
	else if (S_ISLNK(mode))
		rights = ft_strdup("l");
	else if (S_ISSOCK(mode))
		rights = ft_strdup("s");
	else if (S_ISBLK(mode))
		rights = ft_strdup("b");
	else if (S_ISREG(mode))
		rights = ft_strdup("-");
	return (rights);
}

static t_litem	*get_rights(mode_t mode)
{
	char	*rights;

	rights = get_right_file_type(mode);
	rights = add_mode_to_right(rights, ((mode & S_IRUSR) ? "r" : "-"));
	rights = add_mode_to_right(rights, ((mode & S_IWUSR) ? "w" : "-"));
	rights = add_mode_to_right(rights, ((mode & S_IXUSR) ? "x" : "-"));
	rights = add_mode_to_right(rights, ((mode & S_IRGRP) ? "r" : "-"));
	rights = add_mode_to_right(rights, ((mode & S_IWGRP) ? "w" : "-"));
	rights = add_mode_to_right(rights, ((mode & S_IXGRP) ? "x" : "-"));
	rights = add_mode_to_right(rights, ((mode & S_IROTH) ? "r" : "-"));
	rights = add_mode_to_right(rights, ((mode & S_IWOTH) ? "w" : "-"));
	rights = add_mode_to_right(rights, ((mode & S_IXOTH) ? "x" : "-"));
	return (t_litem_new(rights));
}

/*
   static void		get_acl(t_dir_item *item)
   {
   char *path;
   acl_t ret;
   acl_type_t type;

   path = ft_strjoin(item->path, item->item_name);
   ret = acl_get_file(path, type);
   printf("%d\n", ret);
   free(path);
   }
   */

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
	if ((int)(today - item->prop.st_mtime) >= 15768000)
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
	t_litem_push(&line,
			t_litem_new(ft_strdup(getpwuid(item->prop.st_uid)->pw_name)));
	t_litem_push(&line,
			t_litem_new(ft_strdup(getgrgid(item->prop.st_gid)->gr_name)));
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

static void		print_total(int total)
{
	ft_putstr("total ");
	ft_putnbr((total));
	ft_putchar('\n');
}

static void		free_ligtn(t_list **container)
{
	t_list	*bak;
	t_litem	*index;
	t_litem	*index_next;

	index = NULL;
	index_next = NULL;
	bak = (*container)->next;
	index = (*container)->content;
	while (index)
	{
		index_next = index->next;
		free(index->str);
		free(index);
		index = index_next;
	}
	free(*container);
	*container = bak;
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
		print_total(total);
	spaces = max_size_elem(container);
	print_padded_item(container, spaces);
	free(spaces);
}
