/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amargolo <amargolo@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:35:58 by amargolo          #+#    #+#             */
/*   Updated: 2024/12/05 12:35:58 by amargolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t dest_size);
char	*ft_strchr(const char *str, int c);
char	*ft_substr(char const *s, long start, long len);
char	*ft_free(char **str);
char	*get_next_line(int fd);

#endif
