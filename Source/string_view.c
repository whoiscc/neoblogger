//

#include "string_view.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>


StringView create_view(const char *data, const unsigned int length) {
    StringView view = { .ref = data, .length = length};
    return view;
}

void append_string(String *target, const StringView tail) {
    unsigned int tail_offset = target->length;
    target->length += tail.length;
    target->buffer = realloc(target->buffer, sizeof(char) * target->length);
    assert(target->buffer);
    memcpy(target->buffer + tail_offset, tail.ref, tail.length);
}

void normalize_range(
    const unsigned int length, const int start, const int end,
    unsigned int *abs_start, unsigned int *abs_end
) {
    *abs_start = start >= 0 ? start : length + start;
    *abs_end = end >= 0 ? end : length + end;
    assert(*abs_start < *abs_end && *abs_end <= length);
}   

StringView slice_view(const StringView view, const int start, const int end) {
    unsigned int abs_start, abs_end;
    normalize_range(view.length, start, end, &abs_start, &abs_end);
    return create_view(view.ref + abs_start, abs_end - abs_start);
}

String clone_view(const StringView view) {
    String string;
    string.buffer = malloc(sizeof(char) * view.length);
    assert(string.buffer);
    memcpy(string.buffer, view.ref, view.length);
    string.length = view.length;
    return string;
}

int search_view(const StringView haystack, const StringView needle) {
    for (int i = 0; i <= haystack.length - needle.length; i++) {
        if (strncmp(haystack.ref + i, needle.ref, needle.length) == 0) {
            return i;
        }
    }
    return -1;
}

int equal_view(const StringView first, const StringView second) {
    if (first.length != second.length) {
        return 0;
    }
    return strncmp(first.ref, second.ref, first.length) == 0;
}

void free_string(String dropped) {
    free(dropped.buffer);
}

