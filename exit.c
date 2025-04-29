/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saalamoo <saalamoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:50:23 by saalamoo          #+#    #+#             */
/*   Updated: 2023/09/03 18:51:26 by saalamoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	exit_prog(t_prog *prog)
{
	int	i;

	i = 0;
	while (i < prog->num_philos)
	{
		pthread_join(prog->philo_thread[i++], NULL);
	}
	pthread_join(prog->check_thread, NULL);
	i = 0;
	while (i < prog->num_philos)
	{
		pthread_mutex_destroy(&prog->fork_mutex[i++]);
	}
	pthread_mutex_destroy(&prog->eat_mutex);
	pthread_mutex_destroy(&prog->died_mutex);
	pthread_mutex_destroy(&prog->print_mutex);
	pthread_mutex_destroy(&prog->ate_mutex);
	pthread_mutex_destroy(&prog->done_eat_mutex);
}
