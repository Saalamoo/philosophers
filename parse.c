/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saalamoo <saalamoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:50:34 by saalamoo          #+#    #+#             */
/*   Updated: 2023/09/03 18:50:35 by saalamoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_philo(t_prog *prog)
{
	int	i;

	i = 0;
	prog->dead = 0;
	prog->done_eat = 0;
	while (i < prog->num_philos)
	{
		prog->philos[i].died = 0;
		prog->philos[i].eaten = 0;
		prog->philos[i].left_fork = i;
		prog->philos[i].right_fork = (i + 1) % prog->num_philos;
		prog->forks[i] = -1;
		prog->philos[i].prog = prog;
		prog->philos[i].id = i + 1;
		i++;
	}
	if (init_mutex(prog))
	{
		ft_putstr_fd("\033[0;31mFailed to initiate mutex\033[0m", 2);
		return (1);
	}
	return (0);
}

int	parse(t_prog *prog, int argc, char **argv)
{
	prog->num_philos = ft_atoi(argv[1]);
	prog->time_die = ft_atoi(argv[2]);
	prog->time_eat = ft_atoi(argv[3]);
	prog->time_sleep = ft_atoi(argv[4]);
	if (prog->num_philos > 200 || prog->num_philos <= 0
		|| prog->time_die <= 0 || prog->time_sleep <= 0 || prog->time_eat <= 0)
		return (1);
	if (argc == 6)
	{
		prog->am_eat = ft_atoi(argv[5]);
		if (prog->am_eat <= 0)
			return (1);
	}
	else
		prog->am_eat = 0;
	if (init_philo(prog))
		return (1);
	return (0);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_task(t_prog *prog, char *str, int id)
{
	int	chk;

	pthread_mutex_lock(&prog->died_mutex);
	chk = !prog->dead;
	pthread_mutex_unlock(&prog->died_mutex);
	pthread_mutex_lock(&prog->done_eat_mutex);
	chk = chk & !prog->done_eat;
	pthread_mutex_unlock(&prog->done_eat_mutex);
	pthread_mutex_lock(&prog->print_mutex);
	pthread_mutex_lock(&prog->died_mutex);
	if (chk && !prog->dead)
		printf("%lld %d %s\n", get_time() - prog->start_time, id, str);
	pthread_mutex_unlock(&prog->died_mutex);
	pthread_mutex_unlock(&prog->print_mutex);
}

void	pause_prog(t_prog *prog, long long pause)
{
	long long	time;
	int			chk;

	time = get_time();
	pthread_mutex_lock(&prog->died_mutex);
	chk = !prog->dead;
	pthread_mutex_unlock(&prog->died_mutex);
	pthread_mutex_lock(&prog->done_eat_mutex);
	chk = chk & !prog->done_eat;
	pthread_mutex_unlock(&prog->done_eat_mutex);
	while (chk)
	{
		if (get_time() - time >= pause)
			break ;
		usleep(100);
		pthread_mutex_lock(&prog->died_mutex);
		chk = !prog->dead;
		pthread_mutex_unlock(&prog->died_mutex);
		pthread_mutex_lock(&prog->done_eat_mutex);
		chk = chk & !prog->done_eat;
		pthread_mutex_unlock(&prog->done_eat_mutex);
	}
}
