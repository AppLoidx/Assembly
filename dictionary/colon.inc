%define last_elem 0

%macro colon 2
%%last_elem: dq last_elem 
db %1, 0
my_super_label_ %+ %2:

%define last_elem %%last_elem
%endmacro
