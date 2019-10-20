//
#ifndef NEOBLOGGER_SOURCE_STRING_VIEW_H
#define NEOBLOGGER_SOURCE_STRING_VIEW_H

#include <assert.h>


typedef struct _String {
    char *buffer;
    unsigned int length;
} String;


typedef struct _StringView {
    const char *ref;
    unsigned int length;
} StringView;

#define VIEW(s) create_view(s, sizeof(s) - 1)

StringView create_view(const char *data, const unsigned int length);

void append_string(String *target, const StringView tail);

StringView slice_view(const StringView view, const int start, const int end);

static inline const StringView as_view(const String string) {
    StringView view = { .ref = string.buffer, .length = string.length };
    return view;
}

String clone_view(const StringView view);

static inline StringView char_at(const StringView string, const int pos) {
    return slice_view(string, pos, pos == -1 ? string.length : pos + 1);
}

int search_view(const StringView content, const StringView pattern);

int equal_view(const StringView first, const StringView second);

void free_string(String dropped);

String replace_view(
    const StringView original, 
    const StringView pattern, 
    const StringView replaced
);

String quote_view(const StringView view);

typedef struct _SplitViewIter {
    StringView rest;
    const StringView delimiter;
    int stop;
    StringView part;
} SplitViewIter;

SplitViewIter split_view(const StringView view, const StringView delimiter);
int iter_split_view(SplitViewIter *iter);

static inline String indent_view(const StringView view, const unsigned int level) {
    assert(level == 2 || level == 4);
    StringView level_view = level == 2 ? VIEW("  ") : VIEW("    ");
    String result = clone_view(VIEW(""));
    int first_time = 1;
    for (
        SplitViewIter iter = split_view(view, VIEW("\n"));
        iter_split_view(&iter);
    ) {
        if (!first_time) {
            append_string(&result, VIEW("\n"));
        }
        first_time = 0;
        append_string(&result, level_view);
        append_string(&result, iter.part);
    }
    return result;
}

#endif
