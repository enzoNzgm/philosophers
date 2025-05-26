/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enzuguem <enzuguem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:53:50 by enzuguem          #+#    #+#             */
/*   Updated: 2025/04/29 14:58:22 by enzuguem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (parse_args(argc, argv, &data))
		return (1);
	init_philos(&data);
	start_simulation(&data);
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_mutex_destroy(&data.forks[i]);
		pthread_mutex_destroy(&data.philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data.print_mutex);
	free(data.forks);
	free(data.philos);
	return (0);
}
