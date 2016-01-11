/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 11:18:25 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/11 14:17:03 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define TYPE_DEVICE 2 
# define TYPE_DIR    4 
# define TYPE_FILE   8 
# define TYPE_LINK_S 10


#include "libft.h"
#include <dirent.h>

int		ft_ls(char **params);
char	**get_params(int ac, char **av);

#endif
