/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzuguem <enzuguem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:11:23 by enzuguem          #+#    #+#             */
/*   Updated: 2025/05/19 16:02:31 by enzuguem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(t_philo *philo, char *status)
{
	long long	current_time;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (check_simulation_stop(philo->data))
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	current_time = get_current_time() - philo->data->start_time;
	printf("%lld %d %s\n", current_time, philo->id + 1, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	take_forks(t_philo *philo)
{
	if (check_simulation_stop(philo->data))
		return ;
	pthread_mutex_lock(philo->left_fork);
	if (check_simulation_stop(philo->data))
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	if (check_simulation_stop(philo->data))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	print_status(philo, "has taken a fork");
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	if (check_simulation_stop(philo->data))
	{
		release_forks(philo);
		return ;
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_current_time();
	print_status(philo, "is eating");
	pthread_mutex_unlock(&philo->meal_mutex);
	smart_sleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals++;
	pthread_mutex_unlock(&philo->meal_mutex);
	release_forks(philo);
}

void	sleep_and_think(t_philo *philo)
{
	print_status(philo, "is sleeping");
	smart_sleep(philo->data->time_to_sleep, philo->data);
	print_status(philo, "is thinking");
}
