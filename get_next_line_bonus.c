/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 23:10:32 by amwahab           #+#    #+#             */
/*   Updated: 2025/05/30 23:27:01 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#include "get_next_line_bonus.h"

static char	*ft_free(char *pointer)
{
	free(pointer);
	return (NULL);
}

static char	*get_line(char *stash)
{
	int		index;
	char	*line;

	index = 0;
	if (!stash || !stash[0])
		return (NULL);
	while (stash[index] && stash[index] != '\n')
		index++;
	if (stash[index] == '\n')
		index++;
	line = malloc(index + 1);
	if (!line)
		return (NULL);
	index = -1;
	while (stash[++index] && stash[index] != '\n')
		line[index] = stash[index];
	if (stash[index] == '\n')
		line[index++] = '\n';
	line[index] = 0;
	return (line);
}

static char	*clean_stash(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (ft_free(stash));
	new_stash = malloc(ft_strlen(stash) - i + 1);
	if (!new_stash)
		return (ft_free(stash));
	i++;
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = 0;
	free(stash);
	return (new_stash);
}

static char	*fed_stash(int fd, char *stash)
{
	char	*buffer;
	char	*joined_stash;
	int		readed;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (ft_free(stash), NULL);
	if (!stash)
		stash = ft_strdup("");
	readed = 1;
	while (readed > 0 && !ft_strchr(stash, '\n'))
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed < 0)
			return (free(buffer), ft_free(stash));
		buffer[readed] = 0;
		joined_stash = ft_strjoin(stash, buffer);
		free(stash);
		stash = joined_stash;
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (stash[fd])
			free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = fed_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = get_line(stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = clean_stash(stash[fd]);
	return (line);
}
