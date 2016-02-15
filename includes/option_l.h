/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_l.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/08 12:49:31 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/15 16:47:48 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_L_H
# define OPTION_L_H

typedef struct	s_foo
{
	char			*str;
	struct s_foo	*next;
}				t_foo;

void			print_ls_l(t_dir_item *items, char *params);

#endif
