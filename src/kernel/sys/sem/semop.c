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
#include <sys/sem.h>

PUBLIC int sys_semop(int semid, int op) {

    disable_interrupts();
   
    if (op < 0) { /* DOWN sem.P() */

        semtab[semid].val--;

        if (semtab[semid].val < 0) {
            /**/
            sleep(&(semtab[semid].waiting), PRIO_IO);
        }

        
    } else { /* UP sem.V() */
        semtab[semid].val++;

        if (semtab[semid].val <= 0) {
            /* Wake up the sleeping process */
            wakeup(&(semtab[semid].waiting));
            semtab[semid].waiting = NULL;
        }
    }


    
    enable_interrupts();
    return 0;
}