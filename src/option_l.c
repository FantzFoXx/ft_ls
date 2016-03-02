/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 12:49:04 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/02 17:32:54 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include "option_l.h"
#include "colors.h"
#include <unistd.h>

static t_foo	*t_foo_new(char *str)
{
	t_foo *new;

	new = (t_foo *)malloc(sizeof(t_foo));
	if (new)
	{
		//new->str = ft_strdup(str);
		new->str = str;
		new->next = NULL;
	}
	return (new);
}

static void		t_foo_push(t_foo **first, t_foo *new)
{
	t_foo *index;

	index = *first;
	if (!index)
		*first = new;
	else
	{
		while (index->next)
			index = index->next;
		index->next = new;
	}
}

static t_foo	*get_rights(mode_t mode)
{
	char	*rights;
	char	*tmp;

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
	tmp = ft_strdup(rights);
	free(rights);
	rights = ft_strjoin(tmp, ((mode & S_IRUSR) ? "r" : "-"));
	free(tmp);
	tmp = ft_strdup(rights);
	free(rights);
	rights = ft_strjoin(tmp, ((mode & S_IWUSR) ? "w" : "-"));
	free(tmp);
	tmp = ft_strdup(rights);
	free(rights);
	rights = ft_strjoin(tmp, ((mode & S_IXUSR) ? "x" : "-"));
	free(tmp);
	tmp = ft_strdup(rights);
	free(rights);
	rights = ft_strjoin(tmp, ((mode & S_IRGRP) ? "r" : "-"));
	free(tmp);
	tmp = ft_strdup(rights);
	free(rights);
	rights = ft_strjoin(tmp, ((mode & S_IWGRP) ? "w" : "-"));
	free(tmp);
	tmp = ft_strdup(rights);
	free(rights);
	rights = ft_strjoin(tmp, ((mode & S_IXGRP) ? "x" : "-"));
	free(tmp);
	tmp = ft_strdup(rights);
	free(rights);
	rights = ft_strjoin(tmp, ((mode & S_IROTH) ? "r" : "-"));
	free(tmp);
	tmp = ft_strdup(rights);
	free(rights);
	rights = ft_strjoin(tmp, ((mode & S_IWOTH) ? "w" : "-"));
	free(tmp);
	tmp = ft_strdup(rights);
	free(rights);
	rights = ft_strjoin(tmp, ((mode & S_IXOTH) ? "x" : "-"));
	free(tmp);
	return (t_foo_new(rights));
}

static t_foo	*get_date(t_dir_item *item)
{
	char	**tmp;
	t_foo	*date;
	char	**cur_time;
	time_t	today;


	date = NULL;
	today = time(0);
	cur_time = ft_strsplit(ctime(&today), ' ');
	tmp = ft_strsplit(ctime(&item->prop.st_mtime), ' ');
	t_foo_push(&date, t_foo_new(ft_strdup(tmp[1])));
	t_foo_push(&date, t_foo_new(ft_strdup(tmp[2])));
	if ((int)(today - item->prop.st_mtime) >= 15768000)
		t_foo_push(&date, t_foo_new(ft_strsub(tmp[4], 0, ft_strchr(tmp[4], '\n') - tmp[4])));
	else
		t_foo_push(&date, t_foo_new(ft_strsub(tmp[3], 0, 5)));
	ft_freetab(tmp);
	ft_freetab(cur_time);
	return (date);
}

char		*get_item_name(t_dir_item *item, char *params)
{
	static int	option_g = -1;
	char		*filename;
	char		*tmp;
	char		buf[1024];
	ssize_t		read;

	tmp = NULL;
	filename = NULL;
	read = 0;
	if (option_g == -1)
		option_g = (ft_strchr(params, 'G')) ? 1 : 0;
	if (option_g)
		if (S_ISDIR(item->prop.st_mode))
			if ((S_IWOTH & item->prop.st_mode))
			{
				filename = ft_strjoin(DARK_BLACK, HLIGHT_YELLOW);
				tmp = ft_strjoin(filename, item->item_name);
				free(filename);
				filename = ft_strjoin(tmp, DEFAULT_COLOR);
				free(tmp);
			}
			else
			{
				tmp = ft_strjoin(CYAN, item->item_name);
				filename = ft_strjoin(tmp, DEFAULT_COLOR);
				free(tmp);
			}
		else if (S_ISCHR(item->prop.st_mode))
		{
			filename = ft_strjoin(DARK_BLUE, HLIGHT_YELLOW);
			tmp = ft_strjoin(filename, item->item_name);
			free(filename);
			filename = ft_strjoin(tmp, DEFAULT_COLOR);
			free(tmp);
		}
		else if (is_archive_file(item->item_name))
		{
			tmp = ft_strjoin(GREEN, item->item_name);
			filename = ft_strjoin(tmp, DEFAULT_COLOR);
			free(tmp);
		}
		else if (S_ISBLK(item->prop.st_mode))
		{
			filename = ft_strjoin(DARK_BLUE, HLIGHT_CYAN);
			tmp = ft_strjoin(filename, item->item_name);
			free(filename);
			filename = ft_strjoin(tmp, DEFAULT_COLOR);
			free(tmp);
		}
		else if (S_ISFIFO(item->prop.st_mode))
		{
			tmp = ft_strjoin(DARK_YELLOW, item->item_name);
			filename = ft_strjoin(tmp, DEFAULT_COLOR);
			free(tmp);
		}
		else if (S_ISLNK(item->prop.st_mode))
		{
			tmp = ft_strjoin(DARK_PURPLE, item->item_name);
			filename = ft_strjoin(tmp, DEFAULT_COLOR);
			free(tmp);

		}
		else if (is_exec_file(item->prop.st_mode))
		{
			tmp = ft_strjoin(DARK_RED, item->item_name);
			filename = ft_strjoin(tmp, DEFAULT_COLOR);
			free(tmp);
		}
		else
			filename = ft_strdup(item->item_name);
	else
		filename = ft_strdup(item->item_name);
	if (ft_strchr(params, 'l') && S_ISLNK(item->prop.st_mode))
	{
		tmp = ft_strjoin(filename, " -> ");
		free(filename);
		filename = ft_strjoin(item->path, item->item_name);
		read = readlink(filename, buf, sizeof(buf));
		buf[read] = 0;
		free(filename);
		filename = ft_strjoin(tmp, buf);
		free(tmp);
	}
	return (filename);
}

static t_foo	*print_list_item(t_dir_item *item, int *total, char *params)
{
	t_foo	*line;
	int		i;

	i = 0;
	line = NULL;
	(void)params;
	t_foo_push(&line, get_rights(item->prop.st_mode));
	t_foo_push(&line, t_foo_new(ft_itoa(item->prop.st_nlink)));
	t_foo_push(&line, t_foo_new(ft_strdup(getpwuid(item->prop.st_uid)->pw_name)));
	t_foo_push(&line, t_foo_new(ft_strdup(getgrgid(item->prop.st_gid)->gr_name)));
	t_foo_push(&line, t_foo_new(ft_itoa((long)item->prop.st_size)));
	t_foo_push(&line, get_date(item));
	t_foo_push(&line, t_foo_new(get_item_name(item, params)));
	*(total) += (int)(item->prop.st_blocks);
	return (line);
}

static int		*max_size_elem(t_list *container)
{
	int		*spaces;
	t_foo	*index;
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
	//ft_putnbr((total % 512));
	ft_putnbr((total));
	ft_putchar('\n');
}

static void			free_ligtn(t_list **container)
{
	t_list	*bak;
	t_foo	*index;
	t_foo	*index_next;

	index = NULL;
	index_next = NULL;
	bak = (*container)->next;
	index = (*container)->content;
	while (index)
	{
		index_next = index->next;
		free(index->str);
		index = index_next;
	}
	*container = bak;
}

void			print_ls_l(t_dir_item *items, char *params, int only_dirs)
{
	int		*spaces;
	int		total;
	int		a;
	t_list	*container;
	t_foo	*index;

	container = NULL;
	total = 0;
	a = 0;
	while (items)
	{
		ft_lstpush(&container,
				ft_lstnew(print_list_item(items, &total, params), sizeof(t_foo)));
		items = items->next;
	}
	if (container && only_dirs)
		print_total(total);
	spaces = max_size_elem(container);
	index = NULL;
	while (container)
	{
		a = 0;
		index = container->content;
		while (index)
		{
			if (a > 0 && a != 4 && a != 6 && a != 7 && a != 6)
				ft_putchar(' ');
			if (index->next && a != 0 && a != 2 && a != 3 && a != 5 )
				ft_print_rep(' ', (spaces[a] - ft_strlen(index->str) + 1));
			ft_putstr(index->str);
			if (index->next && a != 0 && a != 1 && a != 4 && a != 5 && a != 6 && a != 7)
				ft_print_rep(' ', (spaces[a] - ft_strlen(index->str) + 1));
			/*if (a > 0 && a != 4 && a != 6 && a != 8 && a != 6)
				ft_putchar(' ');
			if (index->next && a != 0 && a != 2 && a != 3 && a != 5 && a != 7)
				ft_print_rep(' ', (spaces[a] - ft_strlen(index->str) + 1));
			ft_putstr(index->str);
			if (index->next && a != 0 && a != 1 && a != 4 && a != 5 && a != 6)
				ft_print_rep(' ', (spaces[a] - ft_strlen(index->str) + 1));
			*/
			index = index->next;
			a++;
		}
		free_ligtn(&container);
		//container = container->next;
		ft_putchar('\n');
	}
}
