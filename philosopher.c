/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saalamoo <saalamoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:50:39 by saalamoo          #+#    #+#             */
/*   Updated: 2023/09/03 18:50:40 by saalamoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_mutex(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->num_philos)
	{
		if (pthread_mutex_init(&prog->fork_mutex[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&prog->print_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&prog->died_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&prog->eat_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&prog->ate_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&prog->done_eat_mutex, NULL))
		return (1);
	return (0);
}

void	single_philo(t_prog *prog)
{
	if (prog->num_philos == 1)
	{
		print_task(prog, "\033[1;38;2;32;178;134mhas taken a left fork\033[0m",
		prog->philos->id);
		pause_prog(prog, prog->time_die);
	}
}

int	start_prog(t_prog *prog)
{
	int	i;

	i = 0;
	prog->start_time = get_time();
	while (i < prog->num_philos)
	{
		prog->philos[i].ate_at = get_time();
		if (pthread_create(&prog->philo_thread[i], NULL, philo_thread,
				&prog->philos[i]))
			return (1);
		usleep(650000);
		++i;
	}
	if (pthread_create(&prog->check_thread, NULL, check_prog, prog))
		return (1);
	exit_prog(prog);
	return (0);
}

void	*philo_thread(void *prog)
{
	t_philo	*arg;
	t_prog	*prog_arg;
	int		chk;

	arg = (t_philo *)prog;
	prog_arg = arg->prog;
	single_philo(prog_arg);
	if (arg->id - 1 % 2)
		usleep(250);
	chk = get_chk(prog_arg);
	while (chk)
	{
		chk = 1;
		if (is_fork_avalable(arg, prog_arg))
		{
			philo_eat(arg, prog_arg);
			print_task(prog_arg, "\033[1;36mis sleeping\033[0m", arg->id);
			pause_prog(prog_arg, prog_arg->time_sleep);
			print_task(prog_arg, "\033[1;38;2;147;112;219mis thinking\033[0m",
				arg->id);
		}
		chk = get_chk(prog_arg);
		usleep(300);
	}
	return (NULL);
}

int	char_parse(char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (argv[j])
	{
		while (argv[j][i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9')
				return (1);
			i++;
		}
		i = 0;
		j++;
	}
	return (0);
}
