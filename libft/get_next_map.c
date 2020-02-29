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

static char		*ft_append(char *stat, char *buff)
{
	char	*joined;
	size_t	len;

	if (stat == NULL || buff == NULL)
		return (NULL);
	len = ft_strlen(stat) + ft_strlen(buff) + 1;
	joined = ft_strnew(len);
	if (joined != NULL)
	{
		joined[len - 1] = '\0';
		ft_strcat(ft_strcpy(joined, stat), buff);
		free(stat);
		return (joined);
	}
	return (NULL);
}

static char		*ft_free_stat(char *stat, char *cropped)
{
	char *ret;

	if (stat == NULL || cropped == NULL)
		return (NULL);
	ft_memset(stat, 0, ft_strlen(stat) + 1);
	ret = ft_strdup(cropped);
	if (cropped == NULL)
		return (NULL);
	free(stat);
	free(cropped);
	return (ret);
}

static int		ft_buildline(const int fd, char **stat, char **line)
{
	int		i;
	char	*cropped;

	i = 0;
	while (stat[fd][i] != '\n' && stat[fd][i] != '\0')
		i++;
	if (((*line) = ft_strsub(stat[fd], 0, i)) == NULL)
	{
		free(stat[fd]);
		return (-1);
	}
	if ((cropped = ft_strdup(stat[fd] + (i + 1))) == NULL)
	{
		free(stat[fd]);
		return (-1);
	}
	stat[fd] = ft_free_stat(stat[fd], cropped);
	if (stat[fd] == NULL)
		return (-1);
	return (1);
}

static int		ft_readintostat(const int fd, char **stat)
{
	char	buff[BUFF_SIZE + 1];
	int		countr;

	while ((countr = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[countr] = '\0';
		stat[fd] = ft_append(stat[fd], buff);
		if (stat[fd] == NULL)
			return (-1);
	}
	return (countr);
}

int				get_next_map(const int fd, char **line)
{
	static char *stat[LIMIT];

	if ((fd < 0 || fd > LIMIT) || (line == NULL) || (BUFF_SIZE <= 0))
		return (-1);
	if (stat[fd] == NULL)
	{
		stat[fd] = ft_strnew(1);
		stat[fd][0] = '\0';
		if (stat[fd] == NULL)
			return (-1);
	}
	if ((ft_readintostat(fd, stat)) < 0)
		return (-1);
	if (stat[fd][0] == '\0')
	{
		(*line) = NULL;
		return (0);
	}
	if ((ft_buildline(fd, stat, line)) == -1)
		return (-1);
	if ((*line[0] < '0' || *line[0] > '9')
	&& *line[0] != ' ' && *line[0] != '-')
		return (-1);
	return (1);
}
