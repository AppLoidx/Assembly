%include "list_config.inc"

%macro add_key 1
%if key_size = 8
    db %1, 0
%elif key_size = 16
    dw %1, 0
%else
    dd %1, 0
%endif
%endmacro
    

colon "hello", key_1
dw "Hello, Onee-chan! 😇", 0

colon "baka", key_2
dw "Baka! 😣", 0

colon "desu", key_3
dw "Watashi wa anata ga suki desu 💖", 0
