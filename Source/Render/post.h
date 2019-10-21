//
#ifndef NEOBLOGGER_SOURCE_RENDER_POST_H
#define NEOBLOGGER_SOURCE_RENDER_POST_H

#include "../render.h"

typedef struct _PostContext {
    StringView title;
    StringView author;
    unsigned int view_count;
    StringView rendered_content;
} CONTEXT_TYPE(post);

DECLARE_RENDER(post);

#endif
