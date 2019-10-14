//

#include "string.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>


String create_string(const char *data, unsigned int length) {
    String string;
    if (length > 0) {
        string.buffer = malloc(sizeof(char) * length);
        assert(string.buffer);
        memcpy(string.buffer, data, length);
    }
    string.length = length;
    string.offset = 0;
    return string;
}

void align_string(String string) {
    if (string.offset != 0) {
        memmove(string.buffer, string.buffer + string.offset, string.length);
        string.offset = 0;
    }
}

void append_string(String target, String moved_tail) {
    align_string(target);
    unsigned int tail_offset = target.length;
    target.length += moved_tail.length;
    target.buffer = realloc(target.buffer, sizeof(char) * target.length);
    assert(target.buffer);
    memcpy(target.buffer + tail_offset, moved_tail.buffer + moved_tail.offset, moved_tail.length);
    free_string(moved_tail);
}

void normalize_range(
    const unsigned int length, const int start, const int end,
    unsigned int *abs_start, unsigned int *abs_end
) {
    *abs_start = start >= 0 ? start : length + start;
    *abs_end = end >= 0 ? end : length + end;
    assert(*abs_start < *abs_end && *abs_end <= length);
}   

String slice_string(String full, int start, int end) {
    unsigned int abs_start, abs_end;
    normalize_range(full.length, start, end, &abs_start, &abs_end);
    return create_string(full.buffer + abs_start, abs_end - abs_start);
}

void cut_string(String *full, int start, int end) {
    unsigned int abs_start, abs_end;
    normalize_range(full->length, start, end, &abs_start, &abs_end);
    full->offset = abs_start;
    full->length = abs_end - abs_start;
}

int search_string(const String haystack, const String needle) {
    for (int i = 0; i <= haystack.length - needle.length; i++) {
        if (strncmp(haystack.buffer + haystack.offset + i, needle.buffer + needle.offset, needle.length) == 0) {
            return i;
        }
    }
    return -1;
}

int equal_string(const String first, const String second) {
    if (first.length != second.length) {
        return 0;
    }
    return strncmp(first.buffer + first.offset, second.buffer + second.offset, first.length) == 0;
}

void free_string(String dropped) {
    free(dropped.buffer);
}

