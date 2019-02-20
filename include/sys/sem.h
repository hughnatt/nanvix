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

#include <limits.h>
#include <nanvix/const.h>
#include <sys/types.h>
#include <sys/ipc.h>

#ifndef SEM_H_
#define SEM_H_

	/**
	 * @brief Command values for semaphores.
	 */
	/**@{*/
	#define GETPID   11
	#define GETVAL   12 /**< Returns the value of a semaphore. */
	#define GETALL	 13
	#define GETNCNT  14
	#define GETZCNT  15
	#define SETVAL   16 /**< Sets the value of a semaphore.    */
	#define SETALL   17
	/**@}*/

	/**
	 * @brief flags for semaphores
	 */
	#define SEM_UNDO 0x1000

	/*
 * @brief Semaphore structure.
 */
	struct semaphore {
		unsigned short semval; /* Semaphore value. */
		pid_t          sempid; /* Process ID of last operation. */
		unsigned short semncnt; 
		unsigned short semzcnt;
		unsigned short semadj;
		struct process *waiting;
		struct process *waitforzero;
	};
	
	/**
	 * @brief TODO
	 */
	struct semid_ds 
	{
		struct ipc_perm  sem_perm;  /* Operation permission structure. */
		unsigned short   sem_nsems; /* Number of semaphores in set. */
		time_t           sem_otime; /* Last semop() time. */
		time_t           sem_ctime; /* Last time changed by semctl. */
		struct semaphore* sems;
		key_t			 key;
	};

	/**
	 * @brief TODO
	 */
	struct sembuf
	{
		unsigned short sem_num; /* Semaphore number. */
		short          sem_op;  /* Semaphore operation */
		short          sem_flg; /* Operation flags. */
	};

	

	/* Forward definitions. */
	extern int semctl(int, int, int,...);
	extern int semget(key_t, int, int);
	extern int semop(int, struct sembuf * , size_t);

	union semun {
    	int val;
    	struct semid_ds *buf;
    	unsigned short  *array;
	} arg;

#endif /* SEM_H_ */
