/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 11:18:25 by udelorme          #+#    #+#             */
/*   Updated: 2016/03/06 01:14:16 by udelorme         ###   ########.fr       */
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

t_dir_content	*open_dirs(char **paths, char *params);
int				ft_ls(char *params, char **entity);
int				open_file(t_dir_item **files, char *path, char *params);
int				open_dir(t_dir_content *dirs, char *params);
int				rec_open_dir(char *path, char *params, t_dir_item *item);
void			get_args(int ac, char **av, char **ret_params
		, char ***ret_paths);
void			check_params(char *params);
void			get_dir_items(t_dir_content *first, char *params);

#endif
