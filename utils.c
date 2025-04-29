/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saalamoo <saalamoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:50:52 by saalamoo          #+#    #+#             */
/*   Updated: 2023/09/03 18:50:53 by saalamoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i++], 1);
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	exit_and_msg(void)
{
	printf("ERROR ARG\n");
	exit(1);
}

int	ft_atoi(const char *str)
{
	int			mp;
	long long	rnb;

	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	mp = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			mp = 1;
		str++;
	}
	rnb = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		rnb = rnb * 10 + (*str - '0');
		str++;
		if (rnb > 2147483648 && mp == 1)
			exit_and_msg();
		else if (rnb > 2147483647 && mp == 0)
			exit_and_msg();
	}
	if (mp == 1)
		return (-rnb);
	return (rnb);
}

int	is_notdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (1);
		i++;
	}
	if ((str[0] == '-' || str[0] == '+') && !str[1])
		return (1);
	return (0);
}
