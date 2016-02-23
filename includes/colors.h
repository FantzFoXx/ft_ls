/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udelorme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 13:35:35 by udelorme          #+#    #+#             */
/*   Updated: 2016/02/23 13:38:36 by udelorme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H
# ifndef BG_LIGHT

#  define BLACK    "\033[1;30m"
#  define RED      "\033[1;31m"
#  define GREEN    "\033[1;32m"
#  define YELLOW   "\033[1;33m"
#  define BLUE     "\033[1;34m"
#  define PURPLE   "\033[1;35m"
#  define CYAN     "\033[1;36m"
#  define GREY     "\033[1;37m"

# else

#  define BLACK    "\033[0;30m"
#  define RED      "\033[0;31m"
#  define GREEN    "\033[0;32m"
#  define YELLOW   "\033[0;33m"
#  define BLUE     "\033[0;34m"
#  define PURPLE   "\033[0;35m"
#  define CYAN     "\033[0;36m"
#  define GREY     "\033[0;37m"

# endif

# define DEFAULT_COLOR "\033[0;m"
#endif
