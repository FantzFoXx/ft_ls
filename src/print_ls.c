/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 15:17:19 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/01 15:36:08 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_ls.h"

static void			print_name_dir(char *name)
{
	ft_putstr(name);
	ft_putendl(": ");
}

void				print_all_items(t_dir_content *first)
{
	int i;

	i = 0;
	if (first && !first->is_dir)
		while (first && !first->is_dir)
		{
			ft_putendl(first->dir_name);
			first = first->next;
			i++;
		}
	if (i)
		ft_putchar('\n');
	while (first)
	{
		if (i > 0)
			print_name_dir(first->dir_name);
		i = 0;
		while (first->items[i])
			ft_putendl(first->items[i++]->d_name);
		first = first->next;
		if (first)
			ft_putchar('\n');
	}
}

void				print_items(t_dir_content *first)
{
	int i;

	i = 0;
	if (first && !first->is_dir)
		while (first && !first->is_dir)
		{
			ft_putendl(first->dir_name);
			first = first->next;
			i++;
		}
	if (i)
		ft_putchar('\n');
	while (first)
	{
		if (i > 0)
			print_name_dir(first->dir_name);
		i = -1;
		while (first->items[++i])
			if (first->items[i]->d_name[0] != '.')
				ft_putendl(first->items[i]->d_name);
		first = first->next;
		if (first)
			ft_putchar('\n');
	}
}

void				print_cur_dir(t_dir_content *first)
{
	int i;

	i = -1;
	if (first)
	{
		print_name_dir(first->dir_name);
		while (first->items[++i])
		{
			//ft_trace("Pass", first->dir_name);
			ft_putendl(first->items[i]->d_name);
		}
	}
}
