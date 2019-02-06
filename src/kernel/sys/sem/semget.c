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
#include <sys/sem.h>

PUBLIC int sys_semget(unsigned key) {
    int free_semid = -1;
    int semid = -1;

    for (int i = 0; i < SEM_MAX; i++) {
        /* Try to find the key in the table. */
        if (semtab[i].key != key) {
            
            /* Looking for free space in case we need to create a new semaphore. */
            if (free_semid == -1 && semtab[i].key == 0) {
                free_semid = i;
            }

        } else { /* Key found */ 
            semid = i;
            break;
        }
    }

    /* Creation of a semaphore associated with the key. */
    if (semid == -1) {
        if (free_semid == -1){ /* No space available for new semaphore.*/
            return -1;
        }
        semid = free_semid;

        semtab[semid].key = key;
        semtab[semid].waiting = NULL;
        semtab[semid].val = 0;
    }

    return semid;
}