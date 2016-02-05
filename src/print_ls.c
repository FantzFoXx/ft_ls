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

static void		print_basic_item(char *s)
{
	ft_putendl(s);
}

static void		print_list_item(t_dir_item *item)
{
	(void)item;

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
	ft_putnbr(item->prop.st_size);
	ft_putchar(' ');
	ft_putnbr((item->prop.st_atimespec.tv_sec));
	ft_putchar(' ');
	ft_putstr(item->item_name);
	ft_putendl("");
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


