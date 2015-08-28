#FunC#

##Data Structure##
As for many functional languages such as Lisp, Haskell and OCaml, I chose linked lists as main data structure. This choice is based on both my knowledge of functional programming in some specific langiages but also on the logic used by their creator that a recursive type is more prone to the paradigm.

###The List###
The entire library is macro based for genericity, starting by the linked list which is as simple as possible:

	#define LIST_DEFINE(type)		\
	typedef struct type##_list_s	\
	{								\
		type head;					\
		struct type##_list_s *tail;	\
	} type##_list;

This gives us a way to access the current element of the node using `head`, and the next node using `tail`.
The biggest issue with this macro is that you cannot have a list of pointers as `type` would be replaced by your type followed by *. It would give us something like `struct your_type*_list_s` which is not allowed in C.
Having a data structure by its own is not really interesting, it needs at least a basic set of functions to use it, its own library.
_Every functions in this library will be added in the LIST_DEFINE macro._

###Building###
The first thing needed is a way to build lists. It would be possible of course to do something like:

	LIST_DEFINE(int)
	// ...
	int_list* my_list = malloc (sizeof (int_list));
	my_list->head = 0;
	my_list->tail = malloc(sizeof (int_list));
	my_list->tail->head = 1;
	my_list->tail->tail = NULL;
	//...

Here 5 lines are needed to properly create a list of two integers. We can simplify the task of adding elements and creating lists with a simple function called `cons`.

	type##_list *type##_list_cons(type, type##_list *)		\
	{														\
		type##_list *res = malloc(sizeof (type##_list));	\
		res->head = elt;									\
		res->tail = list;									\
		return res;											\
	}														\

Okay, it looks like four lines to add one element and it is. Now we can create a two integers list the following way:

	LIST_DEFINE(int)
	// ...
	int_list* my_list = int_list_cons(0, NULL);
	my_list->tail = int_list_cons(1, NULL);
	//...

This time, only two lines have been needed.
It has to be noticed that one should prefer adding elements to the head of the list instead of the tail. Always adding to the tail implies either writing something such as `list->tail->tail->/*...*/->tail->tail` and knowing the number of nodes yourself to access the last node or having a **O(n)** complexity every time an element is added with n the number of nodes in the list. On the other hand adding to the head does not need you to memorize the number of nodes and has a **O(1)** complexity.

If we can create a new list from another one and an element, we might also want to build one from a list and a set of element. This set of element will be a list to simplify things.
this is what concatenation is about: given two lists of element of the same type, it will create a new one with the second list put after the first one.
To `append` the two lists we will create the funtion as follow:

	type##_list *type##_list_append(type##_list *l1, type##_list *l2)	\
	{																	\
		if (!l1)														\
			return l2;													\
		type##_list *tmp = l1;											\
		while (tmp->tail)												\
			tmp = tmp->tail;											\
		tmp->tail = l2;													\
		return l1;														\
	 }																	\

Concatenating two lists will have **O(n1)** complexity with n1 the number of nodes in the first list.

###Access###
Now we are able to construct lists. What if one wants to access an element? there already are, `head` and `tail` in our structure. There is no need to explain that accessing the 42nd element would become tiring, and one would not want to try to access the 6785th one writing by himself all the `tail`s necessary.
To do this frequent task, the function `nth` will do the thing.

	type type##_list_nth(type##_list *list, int pos)	\
	{													\
		while (pos-- > 0)								\
			list = list->tail;							\
		return list->head;								\
	}													\

Consistency leads us to create functions to access the head and the tail also

	type type##_list_head(type##_list *list)	\
	{											\
		return list->head;						\
	}											\

	type type##_list_tail(type##_list *list)	\
	{											\
		return list->tail;						\
	}											\

These three functions will have undefined behaviour if used with an invalid list.
Then `nth` function will also have undefined behaviours when used with a value less than 0 or more than the length of the list. Accessing the nth element of a list has **O(n)** complexity.

###Length###