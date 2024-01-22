/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_extra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcosv2 <marcosv2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:38:04 by marcosv2          #+#    #+#             */
/*   Updated: 2024/01/22 14:38:07 by marcosv2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_check_info(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = 0;
		while (argv[i][j])
		{
			while (argv[i][j] == ' ')
				j++;
			if ((argv[i][j] < 48 || argv[i][j] > 57)
				&& (argv[i][j] != '-' && argv[i][j] != '+'))
				return (ph_error(NULL, ERR_IN_1));
			j++;
		}
	}
	return (0);
}

uint64_t	ph_gtime(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (ph_error(NULL, ERR_GTM));
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

int	ph_usleep(useconds_t time)
{
	uint64_t	start;

	start = ph_gtime();
	while ((ph_gtime() - start) < time)
		usleep(time / 10);
	return (0);
}

void	ph_mss(char *s, t_philo *philo)
{
	uint64_t	time;

	pthread_mutex_lock(&philo->info->write);
	time = ph_gtime() - philo->info->start_tm;
	if (!ft_strcmp(MSS_DIED, s) && !philo->info->died)
	{
		printf("%lu %d %s\n", time, philo->id, s);
		philo->info->died = 1;
	}
	if (!philo->info->died)
		printf("%lu %d %s\n", time, philo->id, s);
	pthread_mutex_unlock(&philo->info->write);
}
