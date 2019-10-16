//
#ifndef NEOBLOGGER_SOURCE_STRING_VIEW_H
#define NEOBLOGGER_SOURCE_STRING_VIEW_H

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

#endif