/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_loner.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcosv2 <marcosv2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:20:39 by marcosv2          #+#    #+#             */
/*   Updated: 2024/01/22 16:26:26 by marcosv2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ph_supervisor(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	while (!philo->info->died)
	{
		pthread_mutex_lock(&philo->lock);
		if (ph_gtime() >= philo->tm_to_die && !philo->eating)
			ph_mss(MSS_DIED, philo);
		pthread_mutex_unlock(&philo->lock);
	}
	return (NULL);
}

static void	*ph_routine(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	philo->tm_to_die = philo->info->tm_die + ph_gtime();
	if (pthread_create(&philo->t1, NULL, &ph_supervisor, (void *)philo))
		return ((void *)1);
	pthread_mutex_lock(philo->l_fork);
	ph_mss(MSS_FORK, philo);
	while (philo->info->died == 0)
		ph_usleep(0);
	pthread_mutex_unlock(philo->l_fork);
	if (pthread_join(philo->t1, NULL))
		return ((void *)1);
	return (NULL);
}

int	ph_loner(t_info *info)
{
	info->start_tm = ph_gtime();
	if (pthread_create(&info->tid[0], NULL, &ph_routine, &info->philos[0]))
		return (ph_error(info, ERR_TH));
	pthread_join(info->tid[0], NULL);
	ph_free_all(info);
	return (0);
}
