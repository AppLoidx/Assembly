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

global list_start
global list_end
    
list_start:

colon "hello", key_1
add_key "Hello, Onee-chan! 😇"

colon "baka", key_2
add_key "Baka! 😣"

colon "desu", key_3
add_key "Watashi wa anata ga suki desu 💖"

list_end:

