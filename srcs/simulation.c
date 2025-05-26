/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzuguem <enzuguem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:06:30 by enzuguem          #+#    #+#             */
/*   Updated: 2025/05/19 12:11:29 by enzuguem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_simulation_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->stop_mutex);
	stop = data->stop_simulation;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stop);
}

static int	check_death(t_philo *philo, t_data *data)
{
	long long	now;

	pthread_mutex_lock(&philo->meal_mutex);
	now = get_current_time();
	if (now - philo->last_meal_time > data->time_to_die)
	{
		pthread_mutex_lock(&data->stop_mutex);
		data->stop_simulation = 1;
		pthread_mutex_unlock(&data->stop_mutex);
		pthread_mutex_lock(&data->print_mutex);
		printf("%lld %d died\n", now - data->start_time, philo->id + 1);
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&philo->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(1000);
	if (philo->data->nb_philo == 1)
	{
		handle_one_philo(philo);
		return (NULL);
	}
	while (!check_simulation_stop(philo->data))
	{
		eat(philo);
		if (check_simulation_stop(philo->data))
			break ;
		if (philo->data->max_meals != -1
			&& philo->meals >= philo->data->max_meals)
			break ;
		sleep_and_think(philo);
	}
	return (NULL);
}

// void	*routine(void *arg)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)arg;

// 	// Petit décalage pour éviter les collisions au démarrage
// 	if (philo->id % 2 == 1)
// 		usleep(1000);

// 	// Cas particulier : 1 seul philosophe
// 	if (philo->data->nb_philo == 1)
// 	{
// 		handle_one_philo(philo);
// 		return (NULL);
// 	}

// 	while (!check_simulation_stop(philo->data))
// 	{
// 		take_forks(philo);

// 		if (check_simulation_stop(philo->data))
// 		{
// 			release_forks(philo);
// 			break ;
// 		}

// 		// manger met à jour last_meal et le compteur de repas
// 		eat(philo);

// 		release_forks(philo);

// 		// Arrêt si le nombre max de repas est atteint
// 		if (philo->data->max_meals != -1
// 			&& philo->meals >= philo->data->max_meals)
// 			break ;

// 		if (check_simulation_stop(philo->data))
// 			break ;

// 		sleep_and_think(philo);
// 	}

// 	return (NULL);
// }

void	*monitor(void *arg)
{
	t_data		*data;
	int			i;

	data = (t_data *)arg;
	while (!check_simulation_stop(data))
	{
		i = 0;
		while (i < data->nb_philo)
			if (check_death(&data->philos[i++], data))
				return (NULL);
		if (all_satisfied(data))
		{
			pthread_mutex_lock(&data->print_mutex);
			printf("All philosophers are satisfied\n");
			pthread_mutex_unlock(&data->print_mutex);
			pthread_mutex_lock(&data->stop_mutex);
			data->stop_simulation = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

void	start_simulation(t_data *data)
{
	pthread_t	monitor_thread;

	if (create_threads(data))
		return ;
	pthread_create(&monitor_thread, NULL, monitor, data);
	join_threads(data, monitor_thread);
}
