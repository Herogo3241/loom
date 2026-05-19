#include "editor.h"
#include <stdio.h>


void create_editor_window(Editor *editor, const char *title, int width, int height){
    if(!create_window(&editor->window, title, width, height)){
        window_destroy(&editor->window);
        perror("failed to open editor window");
    }
}


void editor_run(Editor *editor){
    while (!window_should_close(&editor->window)) {


        window_swap_and_poll(&editor->window);
    
    }
}


void destroy_editor(Editor *editor){
    if(!editor){
        window_destroy(&editor->window);
    }
    editor = NULL;
}
