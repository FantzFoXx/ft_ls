/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolkit.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 10:48:44 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/21 18:51:19 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLKIT_H
# define TOOLKIT_H

#include <stdlib.h>

size_t	size_tab(char **tab);
void	realloc_tab(char ***tab, size_t size);
void	realloc_dirent(struct dirent ***items, size_t size);

#endif
