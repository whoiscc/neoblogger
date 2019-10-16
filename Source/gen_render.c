//

#include "string_view.h"
#include "file.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>


const StringView from_cstr(const char *cstr) {
    StringView view = { .ref = cstr, .length = strlen(cstr) };
    return view;
}

void append_quoted(String *output, const StringView snippet, int newline_ended) {
    append_string(output, VIEW("        \""));
    append_string(output, snippet);
    if (newline_ended) {
        append_string(output, VIEW("\\n"));
    }
    append_string(output, VIEW("\"\n"));
}

void append_append_stat(String *output, const StringView snippet) {
    append_string(output, VIEW("    append_string(&result, VIEW(\n"));
    StringView rest_snippet = slice_view(snippet, 0, snippet.length);
    while (rest_snippet.length) {
        int next_newline = search_view(rest_snippet, VIEW("\n"));
        if (next_newline == -1) {
            append_quoted(output, rest_snippet, 0);
            break;
        }
        StringView this_line = slice_view(rest_snippet, 0, next_newline);
        rest_snippet = slice_view(rest_snippet, next_newline + 1, rest_snippet.length);
        append_quoted(output, this_line, 1);
    }
    append_string(output, VIEW("    ));\n"));
}

int append_render_body(String *output, const StringView input) {
    StringView rest_input = slice_view(input, 0, input.length);
    while (rest_input.length) {
        int next_comment = search_view(rest_input, VIEW("<!--"));
        if (next_comment == -1) {
            append_append_stat(output, rest_input);
            return 0;
        }
        StringView before_comment = slice_view(rest_input, 0, next_comment);
        append_append_stat(output, before_comment);
        rest_input = slice_view(rest_input, next_comment, rest_input.length);
        //
        int comment_closer = search_view(rest_input, VIEW("-->"));
        if (comment_closer == -1) {
            return 1;
        }
        rest_input = slice_view(rest_input, comment_closer + 3, rest_input.length);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    assert(argc > 3);
    StringView input_filename = from_cstr(argv[1]);
    StringView output_filename = from_cstr(argv[2]);
    StringView module_name = from_cstr(argv[3]);

    String input = read_file(input_filename);
    //
    String output = clone_view(VIEW(
        "#include \"string_view.h\"\n"
        "#include \"context.h\"\n"
        "#include <stdio.h>"
        "\n"
        "String render_"
    ));
    append_string(&output, module_name);
    append_string(&output, VIEW(
        "(Context context) {\n"
        "    String result = clone_view(VIEW(\"\"));\n"
    ));
    assert(append_render_body(&output, as_view(input)) == 0);
    append_string(&output, VIEW(
        "    return result;\n"
        "}\n"
    ));

    assert(write_file(output_filename, as_view(output)) == 0);
    free_string(input);
    free_string(output);
    return 0;
}

