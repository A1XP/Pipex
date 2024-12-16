/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkhvorov <pkhvorov@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:10:01 by pkhvorov          #+#    #+#             */
/*   Updated: 2024/10/14 18:09:19 by pkhvorov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int i)
{
	while (*s != '\0')
	{
		if (*s == (char)i)
			return ((char *)s);
		s++;
	}
	if ((char)i == '\0')
		return ((char *)s);
	return (NULL);
}
