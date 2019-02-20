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

/*
 * @brief Semaphore structure.
 */
struct semaphore {
    unsigned short semval; /* Semaphore value. */
    pid_t          sempid; /* Process ID of last operation. */
    unsigned short semncnt; 
    unsigned short semzcnt;
    unsigned short semadj;
    
    int             key;
    struct process *waiting;
    struct process *waitforzero;
};


/*
 * @brief System semaphore array.
 */
EXTERN struct semaphore semtab[SEM_MAX];

/* Forward definitions. */
EXTERN void sem_init(void);