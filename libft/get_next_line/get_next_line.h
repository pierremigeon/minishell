/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmigeon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:59:23 by pmigeon           #+#    #+#             */
/*   Updated: 2018/12/11 21:27:18 by pmigeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 5
# define FD_MAX 5000
# include <unistd.h>
# include "./libft/libft.h"

int		get_next_line(const int fd, char **line);
int		ft_spool(char **buf, int fd, char *temp);
int		get_next_line(const int fd, char **line);
char	*ft_strjoinfree(const char *s1, const char *s2);
int		ft_strcmpz(const char *s1, const char *s2);

#endif
