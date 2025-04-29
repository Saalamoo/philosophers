/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saalamoo <saalamoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:50:49 by saalamoo          #+#    #+#             */
/*   Updated: 2023/09/03 19:17:24 by saalamoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	return_forks(t_prog *prog, t_philo *philo)
{
	pthread_mutex_lock(&prog->fork_mutex[philo->left_fork]);
	prog->forks[philo->left_fork] = -1;
	pthread_mutex_unlock(&prog->fork_mutex[philo->left_fork]);
	pthread_mutex_lock(&prog->fork_mutex[philo->right_fork]);
	prog->forks[philo->right_fork] = -1;
	pthread_mutex_unlock(&prog->fork_mutex[philo->right_fork]);
}

void	start_eating(t_prog *prog, t_philo *philo)
{
	pthread_mutex_lock(&prog->fork_mutex[philo->left_fork]);
	prog->forks[philo->left_fork] = philo->id;
	pthread_mutex_unlock(&prog->fork_mutex[philo->left_fork]);
	print_task(prog, "\033[1;38;2;32;178;134mhas taken a left fork\033[0m",
		philo->id);
	pthread_mutex_lock(&prog->fork_mutex[philo->right_fork]);
	prog->forks[philo->right_fork] = philo->id;
	pthread_mutex_unlock(&prog->fork_mutex[philo->right_fork]);
	print_task(prog, "\033[1;38;2;32;178;134mhas taken a right fork\033[0m",
		philo->id);
	print_task(prog, "\033[1;38;2;255;255;77mis eating\033[0m", philo->id);
	pthread_mutex_lock(&prog->ate_mutex);
	philo->ate_at = get_time();
	pthread_mutex_unlock(&prog->ate_mutex);
	pause_prog(prog, prog->time_eat);
	pthread_mutex_lock(&prog->eat_mutex);
	philo->eaten++;
	pthread_mutex_unlock(&prog->eat_mutex);
}

int	is_fork_avalable(t_philo *ph, t_prog *prog)
{
	pthread_mutex_lock(&(prog->fork_mutex[ph->left_fork]));
	if (prog->forks[ph->left_fork] == -1)
	{
		pthread_mutex_unlock(&(prog->fork_mutex[ph->left_fork]));
		pthread_mutex_lock(&(prog->fork_mutex[ph->right_fork]));
		// pthread_mutex_lock(&(prog->fork_mutex[ph->left_fork]));
		if (prog->forks[ph->right_fork] == -1 )//&& (ph->left_fork != ph->id || ph->right_fork != ph->id)
		{
			// pthread_mutex_unlock(&(prog->fork_mutex[ph->left_fork]));
			pthread_mutex_unlock(&(prog->fork_mutex[ph->right_fork]));
			return (1);
		}
		else
		{
			// pthread_mutex_unlock(&(prog->fork_mutex[ph->left_fork]));
			pthread_mutex_unlock(&(prog->fork_mutex[ph->right_fork]));
		}
	}
	else
		pthread_mutex_unlock(&(prog->fork_mutex[ph->left_fork]));
	return (0);
}

void	philo_eat(t_philo *philo, t_prog *prog)
{
	start_eating(prog, philo);
	return_forks(prog, philo);
}
