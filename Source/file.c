//

#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


String read_file(const StringView filename) {
    // https://stackoverflow.com/a/14002993
    FILE *file = fopen(filename.ref, "rb");
    assert(file);
    
    String string;
    fseek(file, 0, SEEK_END);
    string.length = ftell(file);
    assert(string.length >= 0);
    rewind(file);
    
    string.buffer = malloc(sizeof(char) * (string.length + 1));
    assert(string.buffer);
    int result = fread(string.buffer, sizeof(char), string.length, file);
    assert(result == string.length);
    string.buffer[string.length] = '\0';
    fclose(file);

    return string;
}

int write_file(const StringView filename, const StringView content) {
    FILE *file = fopen(filename.ref, "wb");
    assert(file);

    int result = fwrite(content.ref, sizeof(char), content.length, file);
    fclose(file);
    return result != content.length;
}

int delete_file(const StringView filename) {
    return remove(filename.ref);
}

