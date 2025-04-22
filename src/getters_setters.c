/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:27:01 by mmendiol          #+#    #+#             */
/*   Updated: 2025/04/22 15:27:02 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_bool(pthread_mutex_t *mutex, bool *dst, bool value)
{
	mutex_handler(mutex, LOCK);
	*dst = value;
	mutex_handler(mutex, UNLOCK);
}

bool	get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	tmp;

	mutex_handler(mutex, LOCK);
	tmp = *value;
	mutex_handler(mutex, UNLOCK);
	return (tmp);
}

void	set_long(pthread_mutex_t *mutex, long *dst, long value)
{
	mutex_handler(mutex, LOCK);
	*dst = value;
	mutex_handler(mutex, UNLOCK);
}

long	get_long(pthread_mutex_t *mutex, long *value)
{
	long	tmp;

	mutex_handler(mutex, LOCK);
	tmp = *value;
	mutex_handler(mutex, UNLOCK);
	return (tmp);
}
