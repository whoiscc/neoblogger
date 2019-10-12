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

String render_string(String template, const char *tag, String content) {
    assert(template && content);
    char *index;
    unsigned int tag_length;
    while(1) {
        index = strstr(template->buffer, "@@");
        assert(index);
        index += 2;  // shift @@
        char *tag_end = strstr(index, "@@");
        assert(tag_end);
        tag_length = tag_end - index;
        if (strncmp(index, tag, tag_length) == 0) {
            break;
        }
        index = tag_end + 2;  // shift end @@
    }
    unsigned int length = template->length + content->length - tag_length - 4;
    char *buffer = malloc(sizeof(char) * length);
    String string = malloc(sizeof(struct _String));
    if (!buffer || !string) {
        return NULL;
    }
    string->length = length;
    string->buffer = buffer;
    // content offset in new string
    unsigned int content_offset = index - 2 - template->buffer;
    // rest part of template offset in template string
    unsigned int rest_offset = content_offset + tag_length + 4;
    memcpy(string->buffer, template->buffer, content_offset);
    memcpy(string->buffer + content_offset, content->buffer, content->length);
    memcpy(string->buffer + content_offset + content->length, template->buffer + rest_offset, template->length - rest_offset);
    return string;
}
