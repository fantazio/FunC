# Pointers inside #
Usually when you have a linear data structure, it is not just used for storage. Often you will want to do something with the data in it, and about as often, you will want to do it all over the structure. This idea leads to a series of functions to iterate over, transform or assemble our data structure.

_All of the following functions are parts of macros.
+ `t_in` will designate the type of the given function's input 
+ `t_out` will designate the type of the given function's output_

## Say Hi ##
The first thing we will create is a simple iterating function. This will just go through the list and apply a function on each element.
It is defined as follow:

	void t_in##_iter(void (*fun)(t_in), LIST_TYPE(t_in)* list)	\
	{                                                           \
	  	while (list)                                            \
  	  	{                                                     \
    		fun(list->head);                                      \
    		list = list->tail;                                    \
  		}                                                       \
	}

As you can see I did not lie: it just go through the whole list and apply the given function over each elements. A use example is printing a list's content.
The return type is void. This is due to the fact that there is nothing to do with the output of `fun` as `iter` should be used when something as to be done *with* the elements, not *on* the elements.


## Eevee I choose you! ##
Doing something with a list is good but we can do better. How could we change its content? Well, there is something for that and it is called `map`.
> The concept of mapping is getting something wrapped in a certain way and gives something else wrapped in the same way.
Knowing this information, `map` will have to take a list and return a list, only the content being changed:

	LIST_TYPE(t_out) * t_in##_##t_out##_map(t_out (*fun)(t_in),                   		\
    	LIST_TYPE(t_in) *list)                                                    		\
	{                                                                             		\
  		if (!list)                                                                  	\
    		return NULL;                                                              	\
  		LIST_TYPE(t_out) *res= malloc(sizeof (LIST_TYPE(t_out)));                   	\
  		LIST_TYPE(t_out) *tmp = res;                                                	\
		do                                                                          	  \
  		{                                                                           	\
    		tmp->head = fun(list->head);                                              	\
    		tmp = list->tail ? (tmp->tail = malloc(sizeof (LIST_TYPE(t_out)))) : tmp; 	\
  		} while ((list = list->tail));                                              	\
                                                                              			\
  		return res;                                                                 	\
	}

Here we have a way of creating a new list whose elements are the results of applying `fun` the old list's ones. We do have to create a new list and not just rewrite over the old one because `t_out` and `t_in` are not necessarily the same and thus the nodes for each lists not the same size.


## Origami ##
Maybe the thing to do with the content is reducing it to one element. What we will do is *folding* the elements. They are two main ways of folding (not going into some eccentricities): `fold left` and `fold right`. Both will need a value as default value.
Fold left is supposed to pass through a structure from left to right. On `[val1; val2; ...; valn]` with `def` as default value and `f` the function to apply it gives us:
`f(... (f(f(def, val1), val2),...), valn)`
Fold right works the opposite way: passing through the data from right to left, giving us:
`f(x1,(f(x2,... (f(vn, def))...)))`
Both return the default value in case of an empty structure.

As we know how they should behave, we can implement the two functions as
  t_out t_in##_##t_out##_fold_left(t_out (*fun)(t_out, t_in),                   \
      t_out init, LIST_TYPE(t_in)* list)                                        \
  {                                                                             \
    if (list)                                                                   \
      return t_in##_##t_out##_fold_left(fun, fun(init, list->head),             \
        list->tail);                                                            \
    return init;                                                                \
  }                                                                             \
                                                                                \
  t_out t_in##_##t_out##_fold_right(t_out (*fun)(t_in, t_out),                  \
      LIST_TYPE(t_in)* list, t_out end)                                         \
  {                                                                             \
    if (list)                                                                   \
      return fun(list->head,                                                    \
                  t_in##_##t_out##_fold_right(fun, list->tail, end));           \
    return end;                                                                 \
  }

## Let it go ##
As we talked in the previous article, there has not been created any way of destructing all of our data structure. _The following assumes you use the typedef from the previous article_. Now that we have folds, we can do it easily calling either `fold left` with
  t_in##list_ptr t_in##_free_list(listptr l, t_in unused) \
  {                                                       \
    return LIST_FUN(t_in, dest)(l)                        \
  }
as `fun` and the list to free as default value and as list, or `fold_right` with the same function with arguments swapped.
This function has not been added to the library,