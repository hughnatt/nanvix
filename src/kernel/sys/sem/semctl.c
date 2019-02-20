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
#include <sys/ipc.h>


/*
 * @brief Operations on semaphores.
 */
PUBLIC int sys_semctl(int semid, int semnum, int cmd, union semun arg){
    
    /* Invalid semaphore entry. */
    if (semtab[semid].key == 0){
        return -1;
    }

    switch(cmd){
        case GETVAL:
            return semtab[semid].sems[semnum].semval;
        case SETVAL:
            semtab[semid].sems[semnum].semval = arg.val;
            return 0;
        case GETPID :
            //TODO : check the permission
            return semtab[semid].sems[semnum].sempid;
        case GETNCNT :
            //TODO : check the permission
            return semtab[semid].sems[semnum].semncnt;
        case GETZCNT :
            //TODO : check the permission
            return semtab[semid].sems[semnum].semzcnt;
        case GETALL :
            for(int i = 0; i < semtab[semid].sem_nsems ; i++){
                arg.array[i] = semtab[semid].sems[i].semval;
            }
            return 0;
        case SETALL :
            //TODO : check permission and set ctime at current time
            for(int i = 0; i < semtab[semid].sem_nsems ; i++){
                semtab[semid].sems[i].semval = arg.array[i];
                semtab[semid].sems[i].semadj = 0;
            }
            //semtab[semid].sem_ctime = 
            return 0;
        case IPC_STAT :
            //TODO : check the permission
            semtab[semid] = *arg.buf;
            return 0;
        case IPC_SET :
            //TODO : check the permission, set ctime at current time and check privilege of the process
            semtab[semid].sem_perm = arg.buf->sem_perm;
            return 0;
        case IPC_RMID:
            semtab[semid].key = 0;
            return 0;
        default:
            return -1;
    }
}