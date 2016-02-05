/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 15:17:19 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/05 14:20:30 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_ls.h"
#include <time.h>
#include <pwd.h>
#include <grp.h>

static void		print_basic_item(char *s)
{
	ft_putendl(s);
}

static void		print_list_item(t_dir_item *item)
{
	char	**date;
	DIR		*cur_dir;
	int		i;
	i = 0;
	date = NULL;
	ft_putchar((S_ISDIR(item->prop.st_mode) ? 'd' : '-'));
	ft_putchar(((item->prop.st_mode & S_IRUSR) ? 'r' : '-'));
	ft_putchar(((item->prop.st_mode & S_IWUSR) ? 'w' : '-'));
	ft_putchar(((item->prop.st_mode & S_IXUSR) ? 'x' : '-'));
	ft_putchar(((item->prop.st_mode & S_IRGRP) ? 'r' : '-'));
	ft_putchar(((item->prop.st_mode & S_IWGRP) ? 'w' : '-'));
	ft_putchar(((item->prop.st_mode & S_IXGRP) ? 'x' : '-'));
	ft_putchar(((item->prop.st_mode & S_IROTH) ? 'r' : '-'));
	ft_putchar(((item->prop.st_mode & S_IWOTH) ? 'w' : '-'));
	ft_putchar(((item->prop.st_mode & S_IXOTH) ? 'x' : '-'));
	ft_putchar(' ');
	cur_dir = opendir(ft_strjoin(item->path, item->item_name));
	if (cur_dir)
		while (readdir(cur_dir))
			i++;
	else
		i = 1;
	ft_putnbr(i);
	ft_putchar(' ');
	ft_putstr(getpwuid(item->prop.st_uid)->pw_name);
	ft_putchar(' ');
	ft_putstr(getgrgid(item->prop.st_gid)->gr_name);
	ft_putchar(' ');
	ft_putnbr(item->prop.st_size);
	ft_putchar(' ');
	date = ft_strsplit(ctime(&item->prop.st_mtimespec.tv_sec), ' ');
	ft_putstr(date[1]);
	ft_putchar(' ');
	ft_putstr(date[2]);
	ft_putchar(' ');
	i = -1;
	while (++i < 5)
		ft_putchar(date[3][i]);
	ft_putchar(' ');
	ft_putstr(item->item_name);
	ft_putendl("");
	if (cur_dir)
		closedir(cur_dir);
}

static void		print_all_items(t_dir_item *items, char *params)
{
	int i;

	i = 0;
	if (ft_strchr(params, 'l'))
		i = 1;
	while (items)
	{
		if (i)
			print_list_item(items);
		else
			print_basic_item(items->item_name);
		items = items->next;
	}
}

static void		print_items(t_dir_item *items, char *params)
{
	int i;

	i = 0;
	if (ft_strchr(params, 'l'))
		i = 1;
	while (items)
	{
		if (items->item_name[0] != '.')
		{
			if (i)
				print_list_item(items);
			else
				print_basic_item(items->item_name);
		}
		items = items->next;
	}
}

void			print_ls(t_dir_item *items, char *params)
{
	if (ft_strchr(params, 'a'))
		print_all_items(items, params);
	else
		print_items(items, params);
}


