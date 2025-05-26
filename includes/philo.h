/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzuguem <enzuguem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:52:58 by enzuguem          #+#    #+#             */
/*   Updated: 2025/05/19 11:42:00 by enzuguem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long long		last_meal_time;
	int				meals;
	struct s_data	*data;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_mutex;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	long long		start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	int				stop_simulation;
}	t_data;
//utils.c
long long	get_current_time(void);
int			all_satisfied(t_data *data);
int			create_threads(t_data *data);
void		join_threads(t_data *data, pthread_t monitor_thread);
void		handle_one_philo(t_philo *philo);
void		smart_sleep(long long duration, t_data *data);
void		destroy_all_mutex(t_data *data, int nb_initialized_philos);
void		cleanup_init(t_data *data, int philos_done);

//actions.c
void		print_status(t_philo *philo, char *status);
void		eat(t_philo *philo);
void		sleep_and_think(t_philo *philo);
void		take_forks(t_philo *philo);
void		release_forks(t_philo *philo);

//init.c
void		init_philos(t_data *data);

//simulation.c
void		*routine(void *arg);
void		*monitor(void *arg);
void		start_simulation(t_data *data);
int			check_simulation_stop(t_data *data);

//args.c
int			parse_args(int argc, char **argv, t_data *data);
int			ft_atoi_positive(char *str);

#endif
