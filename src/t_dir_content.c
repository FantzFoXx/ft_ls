/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dir_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 17:28:13 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/21 19:08:05 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_dir_content.h"

t_dir_content	*t_dir_new(void)
{
	t_dir_content *new;
	items = (struct dirent **)malloc(sizeof(struct dirent*));
	dir_name = NULL;
	next = NULL;
	return (new);
}

void			t_dir_push()
{

}
