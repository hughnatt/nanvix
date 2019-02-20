/*
 * Copyright(C) 2011-2016 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * This file is part of Nanvix.
 *
 * Nanvix is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Nanvix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Nanvix. If not, see <http://www.gnu.org/licenses/>.
 */

#include <nanvix/const.h>
#include <nanvix/pm.h>
#include <nanvix/sem.h>

/*
 * @brief Tries to get 1 ressource from the semaphore.
 */
PRIVATE void sem_down(int semid) 
{    
    disable_interrupts();

    semtab[semid].val--;

    if (semtab[semid].val < 0) 
    {
        /* No ressources available ATM, sleep and wait. */
        sleep(&(semtab[semid].waiting), PRIO_SEM);
    }

    enable_interrupts();
}

/*
 * @brief Releases 1 ressource and wakes up 1 blocked process.
 */
PRIVATE void sem_up(int semid) 
{
    disable_interrupts();

    semtab[semid].val++;

    if (semtab[semid].val <= 0)
    {
        /* Wake up the sleeping processes. */
        wakeup_single(&(semtab[semid].waiting));
    }

    enable_interrupts();
}

/*
 * @brief Takes and releases semaphore ressources.
 */
PUBLIC int sys_semop(int semid, int op) 
{
    int n;

    if (op < 0) /* Taking ressources */ 
    { 
        for (n = 0; n > op; n--) 
        {
            sem_down(semid);
        }

    } 
    else if (op > 0) /* Giving back ressources. */ 
    { 
        for (n = 0; n < op; n++) 
        {
            sem_up(semid);
        }
    }
    
    return 0;
}