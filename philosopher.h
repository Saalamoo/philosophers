/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saalamoo <saalamoo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:50:44 by saalamoo          #+#    #+#             */
/*   Updated: 2023/09/03 18:50:45 by saalamoo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_prog	t_prog;

typedef struct s_philo
{
	int					eaten;
	int					died;
	int					id;
	long long			ate_at;
	int					left_fork;
	int					right_fork;
	t_prog				*prog;
}						t_philo;

typedef struct s_prog
{
	long long			time_die;
	int					num_philos;
	long long			time_eat;
	long long			time_sleep;
	int					am_eat;
	int					done_eat;
	long long			start_time;
	int					dead;
	struct s_philo		philos[200];
	int					forks[200];
	pthread_mutex_t		fork_mutex[200];
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		died_mutex;
	pthread_mutex_t		done_eat_mutex;
	pthread_mutex_t		eat_mutex;
	pthread_mutex_t		ate_mutex;
	pthread_t			philo_thread[200];
	pthread_t			check_thread;
}						t_prog;

void					ft_putstr_fd(char *str, int fd);
int						ft_isdigit(int c);
void					exit_and_msg(void);
int						ft_atoi(const char *str);
int						init_mutex(t_prog *prog);
int						is_notdigit(char *str);
int						init_philo(t_prog *prog);
int						parse(t_prog *prog, int argc, char **argv);
long long				get_time(void);
void					print_task(t_prog *prog, char *str, int id);
void					pause_prog(t_prog *prog, long long pause);
void					return_forks(t_prog *prog, t_philo *philo);
void					start_eating(t_prog *prog, t_philo *philo);
void					philo_eat(t_philo *philo, t_prog *prog);
int						get_chk(t_prog *prog);
void					*philo_thread(void *prog);
void					exit_prog(t_prog *prog);
void					check_dead(t_prog *prog);
void					*check_prog(void *arg);
void					check_eat(t_prog *prog);
int						start_prog(t_prog *prog);
int						is_fork_avalable(t_philo *ph, t_prog *prog);
int						char_parse(char **argv);

#endif
