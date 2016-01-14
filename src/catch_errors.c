/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/14 12:57:21 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/14 13:07:49 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		catch_error(int err_code, char *err_msg)
{
	char *def_str;
	(void)err_code; //corriger
	def_str = ft_strjoin("ft_ls: ", err_msg);
	perror(def_str);
	
	return (0);
}
