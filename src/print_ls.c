/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 15:17:19 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/02 18:53:02 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_ls.h"
#include "option_l.h"

static void		print_basic_item(t_dir_item *items, char *params)
{
	char	*s;

	s = get_item_name(items, params);
	ft_putendl(s);
	free(s);
}

void			print_ls(t_dir_item *items, char *params, int only_dirs)
{
	int a;

	a = 0;
	if (ft_strchr(params, 'l'))
		print_ls_l(items, params, only_dirs);
	else
	{
		if (ft_strchr(params, 'a'))
			a = 1;
		while (items)
		{
			print_basic_item(items, params);
			items = items->next;
		}
	}
	if (!only_dirs)
		ft_putchar('\n');
}

void	print_dir_name(char *dir_name)
{
	//ft_putchar('\n');
	ft_putstr(dir_name);
	ft_putendl(":");
	free(dir_name);
}

void	rec_print_dir_name(char *dir_name)
{
	ft_putchar('\n');
	ft_putstr(dir_name);
	ft_putendl(":");
	free(dir_name);
}
