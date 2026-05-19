#pragma once
#include "../engine/window.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include <cimgui.h>


typedef struct{
    Window window;
}Editor;


void create_editor_window(Editor* editor, const char* title, int width, int height);

void editor_run(Editor* editor);
void destroy_editor(Editor* editor);
