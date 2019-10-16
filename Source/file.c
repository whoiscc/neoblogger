//

#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


static char *create_cstr(const StringView view) {
    char *cstr = malloc(sizeof(char) * (view.length + 1));
    assert(cstr);
    memcpy(cstr, view.ref, view.length);
    cstr[view.length] = '\0';
    return cstr;
}

String read_file(const StringView filename) {
    char *filename_cstr = create_cstr(filename);
    // https://stackoverflow.com/a/14002993
    FILE *file = fopen(filename_cstr, "rb");
    assert(file);
    free(filename_cstr);
    
    String string;
    fseek(file, 0, SEEK_END);
    string.length = ftell(file);
    assert(string.length >= 0);
    rewind(file);
    
    string.buffer = malloc(sizeof(char) * string.length);
    assert(string.buffer);
    int result = fread(string.buffer, sizeof(char), string.length, file);
    assert(result == string.length);
    fclose(file);

    return string;
}

int write_file(const StringView filename, const StringView content) {
    char *filename_cstr = create_cstr(filename);
    FILE *file = fopen(filename_cstr, "wb");
    assert(file);
    free(filename_cstr);

    int result = fwrite(content.ref, sizeof(char), content.length, file);
    fclose(file);
    return result != content.length;
}

int delete_file(const StringView filename) {
    char *filename_cstr = create_cstr(filename);
    int result = remove(filename_cstr);
    free(filename_cstr);
    return result;
}

