/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saalamoo <saalamoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:50:19 by saalamoo          #+#    #+#             */
/*   Updated: 2023/09/03 18:51:34 by saalamoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	get_chk(t_prog *prog)
{
	int	chk;

	pthread_mutex_lock(&prog->died_mutex);
	chk = !prog->dead;
	pthread_mutex_unlock(&prog->died_mutex);
	pthread_mutex_lock(&prog->done_eat_mutex);
	chk = chk & !prog->done_eat;
	pthread_mutex_unlock(&prog->done_eat_mutex);
	return (chk);
}

void	check_dead(t_prog *prog)
{
	int			i;
	long long	ate_time;

	i = 0;
	while (i < prog->num_philos)
	{
		pthread_mutex_lock(&prog->ate_mutex);
		ate_time = prog->philos[i].ate_at;
		pthread_mutex_unlock(&prog->ate_mutex);
		if (get_time() - ate_time >= prog->time_die)
		{
			pthread_mutex_lock(&prog->died_mutex);
			prog->dead = 1;
			pthread_mutex_unlock(&prog->died_mutex);
			pthread_mutex_lock(&prog->print_mutex);
			printf("%lld %d \033[1;38;2;236;0;0mhas died! \n\033[0m",
				get_time() - prog->start_time, i + 1);
			pthread_mutex_unlock(&prog->print_mutex);
			break ;
		}
		i++;
	}
}

void	check_eat(t_prog *prog)
{
	int	i;
	int	eaten;

	i = 0;
	pthread_mutex_lock(&prog->eat_mutex);
	eaten = prog->philos[i].eaten;
	pthread_mutex_unlock(&prog->eat_mutex);
	while (i < prog->num_philos && prog->am_eat != 0
		&& eaten >= prog->am_eat)
	{
		++i;
		if (i < prog->num_philos)
		{
			pthread_mutex_lock(&prog->eat_mutex);
			eaten = prog->philos[i].eaten;
			pthread_mutex_unlock(&prog->eat_mutex);
		}
	}
	if (i == prog->num_philos)
	{
		pthread_mutex_lock(&prog->done_eat_mutex);
		prog->done_eat = 1;
		pthread_mutex_unlock(&prog->done_eat_mutex);
	}
}

void	*check_prog(void *arg)
{
	t_prog	*prog;
	int		chk;

	prog = (t_prog *)arg;
	chk = get_chk(prog);
	while (chk)
	{
		check_dead(prog);
		pthread_mutex_lock(&prog->died_mutex);
		chk = prog->dead;
		pthread_mutex_unlock(&prog->died_mutex);
		if (chk)
			break ;
		check_eat(prog);
		chk = get_chk(prog);
	}
	return (NULL);
}
