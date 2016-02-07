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
#include "option_l.h"

static void		print_basic_item(char *s)
{
	ft_putendl(s);
}

void			print_ls(t_dir_item *items, char *params)
{
	int a;

	a = 0;
	if (ft_strchr(params, 'l'))
	{
		print_ls_l(items, params);
	}
	else
	{
		if (ft_strchr(params, 'a'))
			a = 1;
		while (items)
		{
			if ((items->item_name[0] == '.' && a)
					|| items->item_name[0] != '.')
					print_basic_item(items->item_name);
			items = items->next;
		}
	}
}


