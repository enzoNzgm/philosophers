/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzuguem <enzuguem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:43:12 by enzuguem          #+#    #+#             */
/*   Updated: 2025/05/02 15:23:25 by enzuguem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000LL) + (time.tv_usec / 1000));
}

int	all_satisfied(t_data *data)
{
	int	i;

	if (data->max_meals == -1)
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if (data->philos[i].meals < data->max_meals)
		{
			pthread_mutex_unlock(&data->philos[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		i++;
	}
	return (1);
}

int	create_threads(t_data *data)
{
	int	i;

	data->start_time = get_current_time();
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, routine,
				&data->philos[i]) != 0)
		{
			printf("Error: Failed to create thread\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

void	join_threads(t_data *data, pthread_t monitor_thread)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}

void	handle_one_philo(t_philo *philo)
{
	philo->last_meal_time = get_current_time();
	print_status(philo, "has taken a fork");
	usleep((philo->data->time_to_die - 1) * 1000);
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (!philo->data->stop_simulation)
	{
		printf("%lld %d died\n",
			get_current_time() - philo->data->start_time,
			philo->id + 1);
		philo->data->stop_simulation = 1;
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
