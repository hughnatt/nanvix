/*
 * Copyright(C) 2011-2015 Pedro H. Penna <pedrohenriquepenna@gmail.com>
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

/**
 * @file
 * 
 * @brief String library.
 */

#ifndef STRING_H_
#define STRING_H_

	#include <sys/types.h>

	/**
	 * @defgroup string
	 * 
	 * @brief String library.
	 * 
	 * @todo strcoll()
	 */
	/**@{*/

	extern void *memccpy(void *, const void *, int, size_t);
	extern void *memchr(const void *, int, size_t);
	extern int memcmp(const void *, const void *, size_t);
	extern void *memcpy (void *, const void *, size_t);
	extern void *memmove(void *, const void *, size_t);
	extern void *memset(void *, int, size_t);
	extern char *strcat(char *, const char *);
	extern char *strchr(const char *, int);
	extern int strcmp(const char *, const char *);
	extern char *strcpy(char *, const char *);
	extern size_t strcspn(const char *, const char *);
	extern char *strdup(const char *);
	extern int strncmp(const char *str1, const char *str2, size_t n);
	extern size_t strlen(const char * str);
	extern char *strncpy(char *dest, const char *src, size_t n);
	extern size_t strnlen(const char *str, size_t maxlen);
	
	/**@}*/

#endif /* STRING_H_ */
