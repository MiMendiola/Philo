/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:19:30 by mmendiol          #+#    #+#             */
/*   Updated: 2024/11/13 21:55:18 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    rotine( void *item )
{
    /* [Sincronización] */
    t_philo *philo = (t_philo*)item;

    /* Guardar momento actual como ultima vez que comiste */

    /* Simulación/bucle hasta que alguien muera o este philo haya hecho sus comidas */
    while (is_someone_dead( philo ))
    {
        eat();
        /* Coger tenedores y bloquearlos */

        /* Comer el tiempo indicado */

        /* Desbloquear los tenedores */

        /* Actualizamos ultima vez que comio -> gettimeofday() */

        /* Comprobar si ha hecho sus comidas para pirarse */
        if ( philo_has_complete_eaten() )
            break ;

        sleep();
        /* Ponerlo a dormir el tiempo indicado */

        thnk();
        /* Ponerlo a pensar (esperar que los dos tenedores necearios esten libres)*/
    }

    return NULL;
}

void    monitor_routine()
{
    /* El monitor mira si los filosofos han muerto o no*/
    while (1)
    {
        /* Bucle para cada filosofo */

    }
}

int main(int ac, char *av[])
{
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


for (int i = 0; i < philo_count; i++)
    pthead_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
pthead_create(&monitor_thread, NULL, monitor_routine, &gloabl_data)

