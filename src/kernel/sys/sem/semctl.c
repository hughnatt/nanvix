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
#include <nanvix/sem.h>

#include <sys/sem.h>


/*
 * @brief Operations on semaphores.
 */
PUBLIC int sys_semctl(int semid, int semnum, int cmd, semun arg){
    
    /* Invalid semaphore entry. */
    if (semtab[semid].key == 0){
        return -1;
    }

    switch(cmd){
        case GETVAL:
            return semtab[semid].semval;
        case SETVAL:
            semtab[semid].semval = arg.val;
            return 0;
        case GETPID :
            return semtab[semid].sempid;
        case GETNCNT :
            return semtab[semid].semncnt;
        case GETZCNT :
            return semtab[semid].semzcnt;

        case GETALL :
            for(int i =0;i<SEM_MAX;i++){
                arg.array[i] = semtab[i].semval;
            }
            return 0;
        case SETALL :
            for(int i = 0; i<SEM_MAX;i++){
                semtab[i].semval = arg.array[i];
            }
            return 0;
        case IPC_STAT :
            return 0;
        case IPC_SET :
            return 0;

        case IPC_RMID:
            semtab[semid].key = 0;
            return 0;
        default:
            return -1;
    }
}