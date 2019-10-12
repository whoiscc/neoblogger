//
#ifndef NEOBLOGGER_SOURCE_STRING_H
#define NEOBLOGGER_SOURCE_STRING_H

#include <stddef.h>


typedef struct _String {
    char *buffer;
    unsigned int length;
} *String;

#define LITERAL(s) from_literal(s, sizeof(s))
String from_literal(const char *literal, const size_t length);
void free_string(String string);
String concat_string(String first, String second);
String clone_string(String original);
String render_string(String template, const char *tag, String content);

#endif
