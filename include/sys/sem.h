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

#ifndef SEM_H_
#define SEM_H_

	/**
	 * @brief Command values for semaphores.
	 */
	/**@{*/
	#define GETNCNT  0
	#define GETPID   1
	#define GETVAL   2 /**< Returns the value of a semaphore. */
	#define GETALL   3
	#define GETZCNT  4
	#define SETVAL   5 /**< Sets the value of a semaphore.    */
	#define SETALL   6 
	#define IPC_RMID 7 /**< Destroys a semaphore.             */
	#define IPC_STAT 8
	#define IPC_SET 9
	/**@}*/

	/**
	 * @brief flags for semaphores
	 */
	#define SEM_UNDO 0
	#define IPC_NOWAIT 1
	
	/**
	 * @brief TODO
	 */
	struct semid_ds 
	{
		//struct ipc_perm sem_perm;  /* Operation permission structure. */
		unsigned short  sem_nsems; /* Number of semaphores in set. */
		time_t          sem_otime; /* Last semop() time. */
		time_t          sem_ctime; /* Last time changed by semctl. */
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

#endif /* SEM_H_ */
