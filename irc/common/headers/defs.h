/*
** defs.h for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/common/headers
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Fri Apr 18 20:20:07 2014 raphael defreitas
** Last update Sat Apr 19 05:07:25 2014 raphael defreitas
*/

#ifndef		DEFS_H_
# define	DEFS_H_

# ifndef	RET_ERROR
#  define	RET_ERROR	-1
# endif /* !RET_ERROR */

# ifndef	RET_SUCCESS
#  define	RET_SUCCESS	0
# endif /* !RET_SUCCESS */

# ifndef	RET_FAILURE
#  define	RET_FAILURE	1
# endif /* !RET_FAILURE */

# define	MAX(x, y)	((x) > (y) ? (x) : (y))
# define	MIN(x, y)	((x) > (y) ? (y) : (x))

/*
** +---------+
** | Boolean |
** +---------+
*/
typedef char	t_bool;

# ifndef	FALSE
#  define	FALSE	0
# endif /* !TRUE */

# ifndef	TRUE
#  define	TRUE	!FALSE
# endif /* !TRUE */

#endif /* !DEFS_H_*/
