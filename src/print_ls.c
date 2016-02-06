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

static char		*get_rights(mode_t mode)
{
	char *rights;

	rights = ft_strdup((S_ISDIR(mode) ? "d" : "-"));
	rights = ft_strjoin(rights, ((mode & S_IRUSR) ? "r" : "-"));
	rights = ft_strjoin(rights, ((mode & S_IWUSR) ? "w" : "-"));
	rights = ft_strjoin(rights, ((mode & S_IXUSR) ? "x" : "-"));
	rights = ft_strjoin(rights, ((mode & S_IRGRP) ? "r" : "-"));
	rights = ft_strjoin(rights, ((mode & S_IWGRP) ? "w" : "-"));
	rights = ft_strjoin(rights, ((mode & S_IXGRP) ? "x" : "-"));
	rights = ft_strjoin(rights, ((mode & S_IROTH) ? "r" : "-"));
	rights = ft_strjoin(rights, ((mode & S_IWOTH) ? "w" : "-"));
	rights = ft_strjoin(rights, ((mode & S_IXOTH) ? "x" : "-"));
	return (rights);

}

static void		print_list_item(t_dir_item *item)
{
	char	*rights;
	char	**date;
	DIR		*cur_dir;
	int		i;
	i = 0;
	rights = get_rights(item->prop.st_mode);
	ft_putstr(rights);
	ft_putstr("  ");
	cur_dir = opendir(ft_strjoin(item->path, item->item_name));
	if (cur_dir)
		while (readdir(cur_dir))
			i++;
	else
		i = 1;
	ft_putnbr(i);
	ft_putstr("  ");
	ft_putstr(getpwuid(item->prop.st_uid)->pw_name);
	ft_putstr("  ");
	ft_putstr(getgrgid(item->prop.st_gid)->gr_name);
	ft_putstr("  ");
	ft_putnbr(item->prop.st_size);
	ft_putstr("  ");
	date = ft_strsplit(ctime(&item->prop.st_mtimespec.tv_sec), ' ');
	ft_putstr(date[1]);
	ft_putstr("  ");
	ft_putstr(date[2]);
	ft_putstr("  ");
	i = -1;
	while (++i < 5)
		ft_putchar(date[3][i]);
	ft_putchar(' ');
	ft_putstr(item->item_name);
	ft_putendl("");
	if (cur_dir)
		closedir(cur_dir);
}

void			print_ls(t_dir_item *items, char *params)
{
	int i;

	i = 0;
	if (ft_strchr(params, 'l'))
		i = 1;
	while (items)
	{
		if ((items->item_name[0] == '.' && ft_strchr(params, 'a'))
				|| items->item_name[0] != '.')
		{
			if (i)
				print_list_item(items);
			else
				print_basic_item(items->item_name);
		}
		items = items->next;
	}
}
