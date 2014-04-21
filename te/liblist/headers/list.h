/*
** list.h for liblist in /home/raphy/Epitech/Libraries/liblist/headers
**
** Made by raphael defreitas
** Login   <defrei_r@epitech.net>
**
** Started on  Thu Apr 17 18:53:27 2014 raphael defreitas
** Last update Mon Apr 21 01:10:40 2014 raphael defreitas
*/

#ifndef		LIST_H_
# define	LIST_H_

# include	<sys/types.h>

# ifndef	RET_ERROR
#  define	RET_ERROR	-1
# endif /* !RET_ERROR */

# ifndef	RET_SUCCESS
#  define	RET_SUCCESS	0
# endif /* !RET_SUCCESS */

# ifndef	RET_FAILURE
#  define	RET_FAILURE	1
# endif /* !RET_FAILURE */

typedef	struct	s_iterator	t_iterator;

typedef	struct	s_item		t_item;

typedef	struct	s_list		t_list;

/*
** +----------+
** | Iterator |
** +----------+
*/
typedef	enum
  {
    IT_DATA,
    IT_ITEM
  }		t_it_type;

struct		s_iterator
{
  t_list	*list;
  t_item	*current;
  t_it_type	type;
};

t_iterator	*iterator_new(t_list *list, t_it_type type);
void		iterator_delete(t_iterator *this);

int		iterator_ctor(t_iterator *this, t_list *list, t_it_type type);
void		iterator_dtor(t_iterator *this);

void		*iterator_current(t_iterator *this);
void		iterator_next(t_iterator *this);
void		iterator_prev(t_iterator *this);
void		iterator_reset(t_iterator *this);

/*
** +------+
** | Item |
** +------+
*/
struct		s_item
{
  void		*data;
  t_item	*prev;
  t_item	*next;
  void		(*data_free_fptr)();
};

t_item		*item_new(void *data, void (*data_free_fptr)());
void		item_delete(t_item *this);

int		item_ctor(t_item *this, void *data, void (*data_free_fptr)());
void		item_dtor(t_item *this);

void		*item_data(t_item *this);
t_item		*item_next(t_item *this);
t_item		*item_prev(t_item *this);

/*
** +------+
** | List |
** +------+
*/
struct		s_list
{
  t_item	*front;
  t_item	*back;
  size_t	length;
  void		(*data_free_fptr)();
};

t_list		*list_new(void (*data_free_fptr)());
void		list_delete(t_list *this);

int		list_ctor(t_list *this, void (*data_free_fptr)());
void		list_dtor(t_list *this);

void		list_dump(t_list *this);
void		*list_front(t_list *this);
void		*list_back(t_list *this);
size_t		list_length(t_list *this);

int		list_push(t_list *this, void *data);
int		list_enqueue(t_list *this, void *data);
void		*list_unlink(t_list *this, t_item *item);
void		*list_find(t_list *this, int (*find_fptr)(), const void *srch,
			   t_it_type type);

#endif /* !LIST_H_*/
