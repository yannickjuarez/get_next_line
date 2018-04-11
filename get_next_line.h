/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumont- <ydumont-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 14:34:51 by ydumont-          #+#    #+#             */
/*   Updated: 2018/04/11 05:37:55 by nlt              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define BUFF_SIZE 32

typedef struct		s_slot
{
	char			*save;
	int				fd;
	struct s_slot	*next;
}					t_slot;

int					get_next_line(const int fd, char **line);

#endif
