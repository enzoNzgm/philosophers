/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzuguem <enzuguem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:48:47 by enzuguem          #+#    #+#             */
/*   Updated: 2025/05/05 12:00:14 by enzuguem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	smart_sleep(long long duration, t_data *data)
{
	long long	start_time;

	start_time = get_current_time();
	while (!check_simulation_stop(data)
		&& (get_current_time() - start_time) < duration)
		usleep(100);
}

void	destroy_all_mutex(t_data *data, int nb_initialized_philos)
{
	int	i;

	i = 0;
	while (i < nb_initialized_philos)
	{
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
}

void	cleanup_init(t_data *data, int philos_done)
{
	destroy_all_mutex(data, philos_done);
	free(data->philos);
	free(data->forks);
}
