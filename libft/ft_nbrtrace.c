/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrtrace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 18:55:46 by udelorme          #+#    #+#             */
/*   Updated: 2016/01/22 16:14:21 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_nbrtrace(const char *mess, int i)
{
	if (mess)
	{
		ft_putstr(mess);
		ft_putstr(" : ");
	}
	else
		ft_putstr("trace : ");
	ft_putendl(ft_itoa(i));
}
