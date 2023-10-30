/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:41:55 by msulc             #+#    #+#             */
/*   Updated: 2023/03/13 15:41:58 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*dest;
	int		i;
	int		j;

	if (!s1)
		s1 = ft_new_s1();
	if (!s1 || !s2)
		return (NULL);
	dest = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		dest[i++] = s1[j++];
	j = 0;
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	free((char *)s1);
	return (dest);
}

char	*ft_strdup_yes(const char *s)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	while (s[i] != 10 && s[i])
		i++;
	dst = (char *)malloc((i + 2) * sizeof(char));
	if (!dst)
		return (0);
	j = 0;
	while (j <= i)
	{
		dst[j] = s[j];
		j++;
	}
	dst[j] = '\0';
	return (dst);
}

char	*ft_strdup_new(const char *s)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	while (s[i] != 10 && s[i] != '\0')
		i++;
	if (s[i] == 10)
		i++;
	if (i == 0)
	{
		free((char *)s);
		return (NULL);
	}
	dst = (char *)malloc(((ft_strlen(s) - i) + 1) * sizeof(char));
	if (!dst)
		return (0);
	j = 0;
	while (s[i])
		dst[j++] = s[i++];
	dst[j] = '\0';
	free((char *)s);
	return (dst);
}

char	*ft_new_s1(void)
{
	char	*str;	

	str = (char *)malloc(sizeof(char) * 1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}
