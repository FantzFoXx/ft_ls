/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 12:57:21 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/29 11:35:36 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <errno.h>

int				catch_error(int err_code, char *err_msg)
{
	char *def_str;

	(void)err_code; //corriger
	if (ft_strcmp(err_msg, "") == 0)
	{
		free(err_msg);
		perror("ft_ls: fts_open");
		exit(1);
	}
	def_str = ft_strjoin("ft_ls: ",
			ft_strsub(err_msg, 0, ft_strlen(err_msg)));
	perror(def_str);
	errno = 0;
	free(def_str);
	free(err_msg);
	return (0);
}

void			error_params(char *supported, char param)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(param);
	ft_putendl("");
	ft_putstr("usage: ft_ls [-");
	ft_putstr(supported);
	ft_putendl("] [file ...]");
	exit(1);
}
