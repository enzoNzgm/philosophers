/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzuguem <enzuguem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:10:28 by enzuguem          #+#    #+#             */
/*   Updated: 2025/05/15 17:18:53 by enzuguem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi_positive(char *str)
{
	long	num;

	num = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		num = num * 10 + (*str - '0');
		if (num > 2147483647)
			return (-1);
		str++;
	}
	return ((int)num);
}

int	max_meals_check(t_data *data)
{
	if (data->max_meals <= 0)
	{
		printf("Error : max_meals must be a positive number\n");
		return (-1);
	}
	return (0);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		return (printf("./philo nb time_die time_eat time_sleep [meal]\n"), -1);
	data->nb_philo = ft_atoi_positive(argv[1]);
	data->time_to_die = ft_atoi_positive(argv[2]);
	data->time_to_eat = ft_atoi_positive(argv[3]);
	data->time_to_sleep = ft_atoi_positive(argv[4]);
	if (argc == 6)
	{
		data->max_meals = ft_atoi_positive(argv[5]);
		if (max_meals_check(data) == -1)
			return (-1);
	}
	else
		data->max_meals = -1;
	data->stop_simulation = 0;
	if (data->nb_philo <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
	{
		printf("Error: Invalid arguments\n");
		return (-1);
	}
	return (0);
}

// int	parse_args(int argc, char **argv, t_data *data)
// {
// 	if (argc < 5 || argc > 6)
// 	{
// 		printf("./philo nb_philo time_die time_eat time_sleep [max_meals]\n");
// 		return (-1);
// 	}
// 	data->nb_philo = ft_atoi_positive(argv[1]);
// 	data->time_to_die = ft_atoi_positive(argv[2]);
// 	data->time_to_eat = ft_atoi_positive(argv[3]);
// 	data->time_to_sleep = ft_atoi_positive(argv[4]);
// 	if (argc == 6)
// 	{
// 		data->max_meals = ft_atoi_positive(argv[5]);
// 		if (max_meals_check(data) == -1)
// 			return (-1);
// 	}
// 	else
// 		data->max_meals = -1;
// 	pthread_mutex_lock(&data->stop_mutex);
// 	data->stop_simulation = 0;
// 	pthread_mutex_unlock(&data->stop_mutex);
// 	if (data->nb_philo <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
// 		|| data->time_to_sleep <= 0)
// 	{
// 		printf("Error: Invalid arguments\n");
// 		return (-1);
// 	}
// 	return (0);
// }
