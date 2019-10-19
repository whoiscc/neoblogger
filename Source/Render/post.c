#include "post.h"
#include "../string_view.h"
#include "../render.h"
#include <stdio.h>

String render_post(CONTEXT_TYPE(post) *context) {
    String result = clone_view(VIEW(""));
    append_string(&result, VIEW("<h1>"));
    append_string(&result, VIEW("</h1>\n<h3>\n    "));
    append_string(&result, VIEW(" | \n    "));
    append_string(&result, VIEW("\n        "));
    append_string(&result, VIEW("\n        viewed "));
    append_string(&result, VIEW(" times\n    "));
    append_string(&result, VIEW("\n        no view\n    "));
    append_string(&result, VIEW("\n</h3>\n"));
    append_string(&result, VIEW("\n\n"));
    return result;
}
