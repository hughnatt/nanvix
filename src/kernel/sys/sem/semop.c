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
#include <sys/sem.h>

/*
 * @brief System V semaphore operations.
 */
PUBLIC int sys_semop(int semid, struct sembuf *sops, size_t nsops) {
    struct sembuf op;

    for (int k = 0; k < nsops; k++) {
        op = sops[k];

        struct semaphore sem = semtab[op.sem_num];
        

        if (op.sem_op < 0) { /* Taking ressources */

            if (sem.semval >= -op.sem_op){
                sem.semval += op.sem_op;
                
                if (op.sem_flg == SEM_UNDO){
                    sem.semadj += -op.sem_op;
                }

            } else {
                if (op.sem_flg == SEM_UNDO){
                    return -1;
                }

                sem.semncnt++;
                sleep(sem.waiting,PRIO_SEM);
            }

        } else if (op.sem_op > 0) { /* Giving back ressources. */

            sem.semval += op.sem_op;

            if (op.sem_flg == SEM_UNDO)
            {
                /* Substract the value sem_op from the semaphore adjustment value (semadj). */
                sem.semadj -= op.sem_op;
            }

            wakeup(sem.waiting);
        } 
        else 
        { 
            if (op.sem_flg == IPC_NOWAIT) /* Wait-for-zero operation */
            {
                return -1;
            } 
            else 
            {
                sleep(semtab[op.sem_num].waitforzero,PRIO_SEM);
            }
        }

        /* Successful completion. */
        op.sem_num = curr_proc.pid;
        
    }


    return 0;
}