/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:31:55 by amwahab           #+#    #+#             */
/*   Updated: 2025/05/07 16:31:55 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
char	*get_line(char *stash)
{
	int		i;
	char 	*line;

	i = 0;
	while(stash[i] && stash[i] != '\n')
		i++,
	line = (char *)malloc(1 * (i + 2));
	if(!line)
		return (NULL);
	while(i + 2 > 0)
		line[i + 2] = stash[i--];
	return(line);
}
static char	*fed_stash(int fd, char *stash)
{
	int		readed;
	char	*buffer;
	char	*temp;

	buffer = (char *)malloc(1 * BUFFER_SIZE + 1);
	if(!buffer)
		return (NULL);
	readed = 1;
	while(readed > 0)
	{
		readed = read(fd, buffer,BUFFER_SIZE);
		if(readed < 0)
			break ;
		buffer[readed] = '\0';
		temp = stash;
		stash = ft_strjoin(stash, buffer);
		free(temp);
		temp = NULL;
		if(ft_strchr(stash, '\n')) // si il y a un \n donc une ligne on sarrete et on renvoie la ligne et le reste
			break ;
	}
	return(free(buffer), stash);
}

char	*get_next_line(int fd)
{
	static char *stash; //tableau dans lequel on va stocker les elements du buffer;
	char 		*line;
	
	if(fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0) // il y a un fichier? || buffer valide || fichier valide
		return (free(stash), stash = NULL, NULL);
	stash = fed_stash(fd, stash);
	line = get_line(stash);
	return(line);
}