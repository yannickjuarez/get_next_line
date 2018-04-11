/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumont- <ydumont-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:42:16 by ydumont-          #+#    #+#             */
/*   Updated: 2018/04/11 05:37:33 by nlt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static t_slot	*get_slot(t_slot *first, int fd)
{
	t_slot	*slot;

	slot = first;
	while (slot && slot->fd != fd)
		slot = slot->next;
	if (!slot)
	{
		if (!(slot = malloc(sizeof(t_slot))) ||
		!(slot->save = ft_strnew(0)))
			return (0);
		slot->fd = fd;
		slot->next = NULL;
		while (first && first->next)
			first = first->next;
		if (first)
			first->next = slot;
	}
	return (slot);
}

static int		process_slot(t_slot *slot, char **line)
{
	char	*tmp;
	char	*new;

	if (!(tmp = ft_strdup(slot->save)))
		return (-1);
	free(slot->save);
	if (*tmp == '\n')
	{
		if (!(slot->save = ft_strdup(tmp + 1)) ||
		!(*line = ft_strnew(0)))
			return (-1);
		free(tmp);
		return (1);
	}
	if (!(slot->save = ft_strchr(tmp, '\n') ?
	ft_strdup(ft_strchr(tmp, '\n') + 1) : ft_strnew(0)))
		return (-1);
	if (ft_strchr(tmp, '\n'))
		*ft_strchr(tmp, '\n') = '\0';
	if (!(new = *tmp ? tmp : ft_strnew(0)))
		return (-1);
	*line = new;
	if (new != tmp)
		free(tmp);
	return (*new ? 1 : 0);
}

int				get_next_line(const int fd, char **line)
{
	static t_slot	*first;
	t_slot			*slot;
	int				rd;
	char			buff[BUFF_SIZE + 1];
	char			*tmp;

	if (!line || !(slot = get_slot(first, fd)))
		return (-1);
	first = first ? first : slot;
	while ((rd = read(fd, buff, BUFF_SIZE)) && rd != -1)
	{
		buff[rd] = '\0';
		tmp = ft_strjoin(slot->save, buff);
		free(slot->save);
		slot->save = tmp;
		if (ft_strchr(slot->save, '\n'))
			return (process_slot(slot, line));
	}
	return (rd == -1 ? -1 : process_slot(slot, line));
}
