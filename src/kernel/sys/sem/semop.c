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

    for (size_t k = 0; k < nsops; k++) {
        op = sops[k];

        struct semid_ds ds = semtab[semid];
        struct semaphore sem = ds.sems[op.sem_num];
        

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
                sleep(&sem.waiting,PRIO_SEM);
            }

        } else if (op.sem_op > 0) { /* Giving back ressources. */
            //TODO : check permission
            sem.semval += op.sem_op;

            if (op.sem_flg == SEM_UNDO)
            {
                /* Substract the value sem_op from the semaphore adjustment value (semadj). */
                sem.semadj -= op.sem_op;
            }

            wakeup(&sem.waiting);
        } 
        else 
        { 
            if(sem.semval == 0){
                return -1;
            } else if (op.sem_flg == IPC_NOWAIT) {
                return -1;
            } else {
                sleep(&sem.waitforzero,PRIO_SEM);
            }
        }

        /* Successful completion. */
        for(int i = 0; i<ds.sem_nsems; i++){
            ds.sems[i].sempid = curr_proc->pid;
        }
        //TODO : set otime at curret time
        
        
    }


    return 0;
}