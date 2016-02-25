/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 15:18:01 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/25 12:54:01 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_LS_H
# define PRINT_LS_H

# include "ft_ls.h"

void				print_ls(t_dir_item *items, char *params);
void				print_dir_name(char *dir_name);

#endif
