/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmevelec <gmevelec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 22:20:45 by ygudusze          #+#    #+#             */
/*   Updated: 2016/03/03 11:01:29 by gmevelec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*p;
	size_t	begin;
	size_t	end;

	if (!s)
		return (NULL);
	begin = 0;
	while (s[begin]
			&& (s[begin] == ' ' || s[begin] == '\n' || s[begin] == '\t'))
		++begin;
	end = ft_strlen(s) - 1;
	while (end > begin && (s[end] == ' ' || s[end] == '\n' || s[end] == '\t'))
		--end;
	p = ft_strnew(end - begin + 1);
	if (p)
		ft_strncpy(p, s + begin, end - begin + 1);
	return (p);
}
