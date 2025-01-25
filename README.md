# Table Node

## description

This is a library for the c++ language. Table Node is literally a 2D array, but on linked lists in all directions in 2D space (top, right, bottom, left)

## constructor

### Table_Node<*your type*> name_table(*default value of your type*);
creates an empty table

### Table_Node<*your type*> name_table(*x*, *y*, *default value of your type*);
creates a table already with x columns and y rows

## functions

- **bool empty()** - true if empty, false if full
- **add_top_border()** - adds a row up
- **add_right_border()** - adds a row to the right
- **add_bottom_border()** - adds a row down
- **add_left_border()** - adds a row to the left
- **delete_top_border()** - delete a row up
- **delete_right_border()** - delete a row on the right
- **delete_bottom_border()** - delete a row down
- **delete_left_border()** - delete the row on the left
- **print_table()** - outputs the entire table by principle: [x,y] data : direction_top direction_right direction_bottom direction_left
- **set_data(const size_t& x, const size_t& y, const T& data)** - sets the data at x and y
- **get_data_(const size_t& x, const size_t& y)** - gets the data at x and y
