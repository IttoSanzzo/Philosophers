/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcosv2 <marcosv2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:38:11 by marcosv2          #+#    #+#             */
/*   Updated: 2024/01/22 14:38:12 by marcosv2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_error(t_info *info, char *err)
{
	ft_putendl_fd(err, STDERR_FILENO);
	if (info)
		ph_free_all(info);
	return (1);
}

void	ph_free_all(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->ph_num)
	{
		pthread_mutex_destroy(&info->forks[i]);
		pthread_mutex_destroy(&info->philos[i].lock);
	}
	pthread_mutex_destroy(&info->lock);
	pthread_mutex_destroy(&info->write);
	if (info->tid)
		free(info->tid);
	if (info->forks)
		free(info->forks);
	if (info->philos)
		free(info->philos);
}
