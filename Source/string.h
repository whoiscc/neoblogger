//
#ifndef NEOBLOGGER_SOURCE_STRING_H
#define NEOBLOGGER_SOURCE_STRING_H

typedef struct _String {
    char *buffer;
    unsigned int offset;
    unsigned int length;
} String;

#define STRING(s) create_string(s, sizeof(s) - 1)
String create_string(const char *data, unsigned int length);
void append_string(String target, String moved_tail);

String slice_string(String full, int start, int end);
static inline String clone_string(String model) {
    return slice_string(model, 0, model.length);
}
static inline String char_at(String string, int pos) {
    return slice_string(string, pos, pos == -1 ? string.length : pos + 1);
}

void cut_string(String *full, int start, int end);
static inline String cut_head(String *full, int pos) {
    String head = slice_string(*full, 0, pos);
    cut_string(full, pos, full->length);
    return head;
}
static inline String cut_tail(String *full, int pos) {
    String tail = slice_string(*full, pos, -1);
    cut_string(full, 0, pos);
    return tail;
}

int search_string(const String content, const String pattern);
int equal_string(const String first, const String second);
void free_string(String dropped);

#endif
