/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 11:18:25 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/05 17:19:26 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define TYPE_DEVICE 2
# define TYPE_DIR    4
# define TYPE_FILE   8
# define TYPE_LINK_S 10

# include "catch_errors.h"
# include "toolkit.h"

int		ft_ls(char *params, char **entity);
void	get_args(int ac, char **av, char **ret_params, char ***ret_paths);
void	check_params(char *params);

#endif
