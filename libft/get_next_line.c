/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get-next-line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okupin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 19:32:12 by okupin            #+#    #+#             */
/*   Updated: 2018/01/12 19:32:14 by okupin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_join(char *s1, char const *s2)
{
	int		len_1;
	int		len_2;
	char	*string;

	len_2 = ft_strlen(s2);
	len_1 = ft_strlen(s1);
	string = ft_strnew(len_1 + len_2 + 1);
	if (string)
	{
		ft_strncpy(string, s1, len_1);
		free(s1);
		ft_strncpy((string + len_1), s2, len_2);
	}
	return (string);
}

char		*gnl_read(int fd, char *string)
{
	int				c_read;
	char			r_buff[BUFF_SIZE + 1];

	while ((c_read = read(fd, r_buff, BUFF_SIZE)) > 0)
	{
		r_buff[c_read] = '\0';
		if (!(string))
		{
			if (!(string = malloc(sizeof(char) * c_read + 1)))
				return (NULL);
			ft_memset(string, 0, c_read + 1);
			ft_memcpy(string, r_buff, c_read);
		}
		else
			string = ft_join(string, r_buff);
	}
	if (c_read < 0)
		return (NULL);
	return (string);
}

char		*new_sub(char *s, int start, int len)
{
	char	*substring;
	int		string_len;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	string_len = ft_strlen(s);
	substring = NULL;
	if (s[start] == '\n')
		start++;
	if (start < string_len + 1 && len < string_len + 1)
	{
		if ((substring = malloc(sizeof(char) * len + 1)) == NULL)
			return (NULL);
		while (start < string_len && i < len)
		{
			substring[i] = s[start];
			start++;
			i++;
		}
		substring[i] = '\0';
	}
	free(s);
	return (substring);
}

int			get_next_line(const int fd, char **line)
{
	static char	*string[15000];
	int			i;

	i = 0;
	if ((fd < 0 || fd > 15000) || (line == NULL) || (BUFF_SIZE <= 0))
		return (-1);
	if (!(string[fd] = gnl_read(fd, string[fd])))
		return (-1);
	if (*string[fd] == '\0')
	{
		*line = NULL;
		return (0);
	}
	while (string[fd][i] != '\n' && string[fd][i] != '\0')
		i++;
	*line = ft_strncpy(ft_strnew(i), string[fd], i);
	string[fd] = new_sub(string[fd], i, (ft_strlen(string[fd]) - i));
	if (string[fd] == NULL)
		return (-1);
	return (1);
}
