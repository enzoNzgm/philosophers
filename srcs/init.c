/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzuguem <enzuguem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:57:39 by enzuguem          #+#    #+#             */
/*   Updated: 2025/05/07 15:09:20 by enzuguem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_mutex(pthread_mutex_t *mutex, const char *error_msg)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		printf("%s\n", error_msg);
		return (-1);
	}
	return (0);
}

static int	init_forks_and_print_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (init_mutex(&data->forks[i], "Error: Failed init fork mutex") != 0)
			return (-1);
		i++;
	}
	if (init_mutex(&data->print_mutex, "Error: Failed init print mutex") != 0)
		return (-1);
	if (init_mutex(&data->stop_mutex, "Error: Failed to init stop mutex") != 0)
		return (-1);
	pthread_mutex_lock(&data->stop_mutex);
	data->stop_simulation = 0;
	pthread_mutex_unlock(&data->stop_mutex);
	return (0);
}

static int	init_one_philo(t_philo *philo, t_data *data, int i)
{
	philo->id = i;
	philo->data = data;
	philo->last_meal_time = get_current_time();
	philo->meals = 0;
	philo->left_fork = &data->forks[i];
	philo->right_fork = &data->forks[(i + 1) % data->nb_philo];
	if (pthread_mutex_init(&philo->meal_mutex, NULL) != 0)
	{
		printf("Error: Failed to init meal mutex for philo %d\n", i);
		return (-1);
	}
	return (0);
}

void	init_philos(t_data *data)
{
	int		i;

	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
	{
		printf("Error: Failed to allocate memory for philosophers\n");
		return ;
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
	{
		printf("Error: Failed to allocate memory for forks\n");
		free(data->philos);
		return ;
	}
	if (init_forks_and_print_mutex(data) == -1)
		return (cleanup_init(data, 0));
	i = 0;
	while (i < data->nb_philo)
	{
		if (init_one_philo(&data->philos[i], data, i) == -1)
			return (cleanup_init(data, i));
		i++;
	}
}

// void	init_philos(t_data *data)
// {
// 	int		i;

// 	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
// 	if (!data->philos)
// 	{
// 		printf("Error: Failed to allocate memory for philosophers\n");
// 		return ;
// 	}
// 	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
// 	if (!data->forks)
// 	{
// 		printf("Error: Failed to allocate memory for forks\n");
// 		free(data->philos);
// 		return ;
// 	}
// 	if (init_forks_and_print_mutex(data) == -1)
// 	{
// 		free(data->philos);
// 		free(data->forks);
// 		return ;
// 	}
// 	i = 0;
// 	while (i < data->nb_philo)
// 	{
// 		if (init_one_philo(&data->philos[i], data, i) == -1)
// 		{
// 			destroy_all_mutex(data, i);
// 			free(data->philos);
// 			free(data->forks);
// 			return ;
// 		}
// 		i++;
// 	}
// }
