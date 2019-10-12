//

#include "string.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>


String from_literal(const char *literal, const size_t length) {
    char *buffer = malloc(sizeof(char) * length);
    String string = malloc(sizeof(struct _String));
    if (!buffer || !string) {
        return NULL;
    }
    assert(literal[length - 1] == '\0');
    string->buffer = buffer;
    string->length = length - 1;
    memcpy(string->buffer, literal, string->length);
    return string;
}

void free_string(String string) {
    free(string->buffer);
    free(string);
}

String concat_string(const String first, const String second) {
    assert(first && second);
    char *buffer = malloc(sizeof(char) * (first->length + second->length));
    String string = malloc(sizeof(struct _String));
    if (!buffer || !string) {
        return NULL;
    }
    string->buffer = buffer;
    string->length = first->length + second->length;
    memcpy(string->buffer, first->buffer, first->length);
    memcpy(string->buffer + first->length, second->buffer, second->length);
    return string;
}

String clone_string(const String original) {
    assert(original);
    char *buffer = malloc(sizeof(char) * original->length);
    String string = malloc(sizeof(struct _String));
    if (!buffer || !string) {
        return NULL;
    }
    string->buffer = buffer;
    string->length = original->length;
    memcpy(string->buffer, original->buffer, original->length);
    return string;
}

