#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include <stdbool.h>

char* parseShader(const char* filepath){
    FILE* fp;

    fp = fopen(filepath, "rb");
    if(!fp){
        perror("failed to open shader\n");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* buffer = (char*)malloc(length + 1);
    if(buffer){
        size_t bytesRead = fread(buffer, 1, length, fp);
        buffer[bytesRead] = '\0';
    }

    fclose(fp);

    return buffer;
}


