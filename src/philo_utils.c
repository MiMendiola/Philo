/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 22:01:44 by mmendiol          #+#    #+#             */
/*   Updated: 2024/11/13 22:39:54 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_list(t_philo **stack)
{
	t_philo	*aux;

	while (*stack)
	{
		aux = (*stack)->next;
		pthread_mutex_destroy(&aux->lock);
		free(*stack);
		*stack = aux;
	}
	free(stack);
}

t_philo	*last_node(t_philo *lst)
{
	while (lst && lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_philo	*new_node(int id, char *av[])
{
	t_philo	*philo;

	philo = ft_calloc(1, sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	pthread_create(&philo->thread, NULL, philo_routine, (void *)philo);
	pthread_mutex_init(&philo->lock, NULL);
	philo->prev = NULL;
	philo->next = NULL;
	philo->timeToDieMs = ft_atoi(av[2]);
	philo->timeToEatMs = ft_atoi(av[3]);
	philo->timeToSleepMs = ft_atoi(av[4]);
	if (av[5])
		philo->maxTimesEaten = ft_atoi(av[5]);
	else
		philo->maxTimesEaten = INT_MAX;
	if ((philo->timeToDieMs == INT_MAX + 1) || (philo->timeToEatMs == INT_MAX + 1) || (philo->timeToSleepMs == INT_MAX + 1) || (philo->maxTimesEaten == INT_MAX + 1))
		return(free(philo), NULL);
	return (philo);
}

void	add_node_back(t_philo **stack, t_philo *new)
{
	t_philo	*aux;

	aux = last_node(*stack);
	if (*stack != NULL)
	{
		new->prev = aux;
		new->next = NULL;
		aux->next = new;
	}
	else
		*stack = new;
}

long	ft_atol(char *str)
{
	long	n;
	int		i;
	long	sign;

	n = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	if (!ft_isdigit(str[i]))
		return (INT_MAX + 1);
	while (ft_isdigit(str[i]))
		n = (str[i++] - '0') + (n * 10);
	if (!ft_isdigit(str[i]) && str[i])
		return (INT_MAX + 1);
	n *= sign;
	if (n > INT_MAX || n < INT_MIN)
		return (INT_MAX + 1);
	return (n);
}