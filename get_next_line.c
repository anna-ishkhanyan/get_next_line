/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_answer.c                                    :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: anishkha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:36:42 by anishkha          #+#    #+#             */
/*   Updated: 2024/04/17 22:34:26 by anishkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_remainder(int fd, char *buffer, char *remainder)
{
	int	read_size;

	read_size = 1;
	while (read_size != 0)
	{
		read_size = read (fd, buffer, BUFFER_SIZE);
		if (read_size == -1)
		{
			free (remainder);
			remainder = NULL;
			return (0);
		}
		else if (read_size == 0)
			break ;
		buffer[read_size] = '\0';
		if (!remainder)
			remainder = ft_strdup("");
		remainder = ft_joining_remainder(remainder, buffer);
		if (ft_strchr(remainder, '\n'))
			break ;
	}
	return (remainder);
}

char	*ft_joining_remainder(char *remainder, char *buffer)
{
	char	*temp;

	temp = remainder;
	remainder = ft_strjoin(temp, buffer);
	free (temp);
	temp = NULL;
	return (remainder);
}

char	*ft_updated(char *answer)
{
	int		i;
	char	*remainder;

	i = 0;
	while (answer[i] != '\n' && answer[i] != '\0')
		i++;
	if (answer[i] == '\0')
		return (0);
	remainder = ft_substr(answer, i + 1, ft_strlen(answer) - i);
	if (*remainder == '\0')
	{
		free(remainder);
		remainder = NULL;
	}
	answer[i + 1] = '\0';
	return (remainder);
}

char	*get_next_line(int fd)
{
	char		*answer;
	char		*buffer;
	static char	*remainder;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	answer = ft_remainder(fd, buffer, remainder);
	free(buffer);
	buffer = NULL;
	if (!answer)
		return (NULL);
	remainder = ft_updated(answer);
	return (answer);
}
