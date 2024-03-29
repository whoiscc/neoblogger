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
    target->buffer = realloc(target->buffer, sizeof(char) * (target->length + 1));
    assert(target->buffer);
    memcpy(target->buffer + tail_offset, tail.ref, tail.length);
    target->buffer[target->length] = '\0';
}

void normalize_range(
    const unsigned int length, const int start, const int end,
    unsigned int *abs_start, unsigned int *abs_end
) {
    *abs_start = start >= 0 ? start : length + start;
    *abs_end = end >= 0 ? end : length + end;
    assert(*abs_start <= *abs_end && *abs_end <= length);
}   

StringView slice_view(const StringView view, const int start, const int end) {
    unsigned int abs_start, abs_end;
    normalize_range(view.length, start, end, &abs_start, &abs_end);
    return create_view(view.ref + abs_start, abs_end - abs_start);
}

String clone_view(const StringView view) {
    String string;
    string.buffer = malloc(sizeof(char) * (view.length + 1));
    assert(string.buffer);
    memcpy(string.buffer, view.ref, view.length);
    string.buffer[view.length] = '\0';
    string.length = view.length;
    return string;
}

int search_view(const StringView haystack, const StringView needle) {
    if (needle.length > haystack.length) {
        return -1;
    }
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

String quote_view(const StringView original) {
    struct {
        StringView pattern;
        StringView replaced;
    } replace_pair[] = {
        { VIEW("\\"), VIEW("\\\\") },
        { VIEW("\n"), VIEW("\\n") },
        { VIEW("\""), VIEW("\\\"") },
        { VIEW("\'"), VIEW("\\\'") },
        { VIEW(""), VIEW("") }
    };

    int i = 0;
    String result = clone_view(original);
    while (replace_pair[i].pattern.length) {
        String replace_result = replace_view(as_view(result), replace_pair[i].pattern, replace_pair[i].replaced);
        free_string(result);
        result = replace_result;
        i += 1;
    }
    String with_quote = clone_view(VIEW("\""));
    append_string(&with_quote, as_view(result));
    append_string(&with_quote, VIEW("\""));
    free_string(result);
    return with_quote;
}

SplitViewIter split_view(const StringView view, const StringView delimiter) {
    SplitViewIter iter = {
        .rest = slice_view(view, 0, view.length),
        .delimiter = delimiter,
        .stop = 0
    };
    return iter;
}

int iter_split_view(SplitViewIter *iter) {
    if (iter->stop) {
        return 0;
    }
    int split_index = search_view(iter->rest, iter->delimiter);
    if (split_index == -1) {
        iter->part = iter->rest;
        iter->stop = 1;
    } else {
        iter->part = slice_view(iter->rest, 0, split_index);
        iter->rest = slice_view(
            iter->rest, split_index + iter->delimiter.length, iter->rest.length);
    }
    return 1;
}

