/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:21:26 by mmendiol          #+#    #+#             */
/*   Updated: 2025/03/03 17:48:25 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int perror(char *error)
{
    printf(RED"%s\n"CLEAR , error);
    return (1);
} 

int main(int ac, char *av[])
{

    if (ac != 5 && ac != 6)
    {
        perror("Incorrect usage. Please, correct the input.");
    }

    
    /* Miramos numero de argumentos correctos */

    /* Miramos quue los argumentos sean validos */

    /* Guardamos los argumentos ya convertidos */

    /* Creamos tenedores */

    /* Creamos las estructuras de los philosofos */

    /* Crear hilo monitor */

    /* [Creamos os hilos de los filosofos y el monitor => Empiezan a la vez] <= Es nevcesario que empeicen a la vez (sincronización) */

    /* ROUTINE y MONITOR_ROUTINE */

    /* Liberar memoria - Eliminar todos */

    return (0);
}


// for (int i = 0; i < philo_count; i++)
//     pthead_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
// pthead_create(&monitor_thread, NULL, monitor_routine, &gloabl_data)
