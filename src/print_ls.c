/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 15:17:19 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/26 15:37:06 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_ls.h"

static void			print_name_dir(char *name)
{
	ft_putstr(name);
	ft_putendl(": ");
}

void				print_items(t_dir_content *first)
{
	int i;

	i = 0;
	if (first && !first->cur_dir)
		while (first && !first->cur_dir)
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
