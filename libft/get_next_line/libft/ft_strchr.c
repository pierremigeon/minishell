/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 21:48:59 by pmigeon           #+#    #+#             */
/*   Updated: 2018/12/10 20:52:17 by pmigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t i;

	if (!s)
		return (NULL);
	i = -1;
	while (++i < ft_strlen(s) + 1)
		if (s[i] == (char)c)
			return ((char *)s + i);
	return (NULL);
}
