/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcosv2 <marcosv2@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:38:21 by marcosv2          #+#    #+#             */
/*   Updated: 2024/01/22 16:31:34 by marcosv2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_info	info;

	if ((ac < 5 || ac > 6) || ph_check_info(av) || ph_inits(&info, ac, av))
		return (1);
	if (info.ph_num == 1)
		return (ph_loner(&info));
	if (ph_agora(&info))
		return (1);
	ph_free_all(&info);
	return (0);
}
