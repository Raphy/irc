/*
** defs.h for my_irc in /home/raphy/Epitech/Tech_2/PSU_2013_myirc/irc/common/headers
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Fri Apr 18 20:20:07 2014 raphael defreitas
** Last update Fri Apr 25 01:04:36 2014 raphael defreitas
*/

#ifndef		DEFS_H_
# define	DEFS_H_

# ifdef		_cplusplus
extern "C" {
# endif /* !_cplusplus */

# ifndef	RET_ERROR
#  define	RET_ERROR	-1
# endif /* !RET_ERROR */

# ifndef	RET_SUCCESS
#  define	RET_SUCCESS	0
# endif /* !RET_SUCCESS */

# ifndef	RET_FAILURE
#  define	RET_FAILURE	1
# endif /* !RET_FAILURE */

# ifndef	MAX
#  define	MAX(x, y)	((x) > (y) ? (x) : (y))
# endif /* !MAX */

# ifndef	MIN
#  define	MIN(x, y)	((x) > (y) ? (y) : (x))
# endif /* !MIN */

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

# ifdef		_cplusplus
}
# endif /* !_cplusplus */

#endif /* !DEFS_H_*/
