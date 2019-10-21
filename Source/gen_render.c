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

String join_path(const StringView dir, const StringView file) {
    String joined = clone_view(dir);
    if (!equal_view(char_at(as_view(joined), -1), VIEW("/"))) {
        append_string(&joined, VIEW("/"));
    }
    append_string(&joined, file);
    return joined;
}

String generate_append_statement(const StringView part) {
    StringView append_template = VIEW("append_string(&@@result@@, VIEW(@@quoted_part@@));\n");
    String quoted_part = quote_view(part);
    String append_statement = replace_view(append_template, VIEW("@@quoted_part@@"), as_view(quoted_part));
    free_string(quoted_part);
    return append_statement;
}

String generate(const StringView template) {
    StringView rest = slice_view(template, 0, template.length);
    String result = clone_view(VIEW(""));
    while (rest.length) {
        int next_comment = search_view(rest, VIEW("<!--"));
        StringView current;
        if (next_comment == -1) {
            current = rest;
        } else {
            current = slice_view(rest, 0, next_comment);
        }
        String append_statement = generate_append_statement(current);
        append_string(&result, as_view(append_statement));
        free_string(append_statement);
        if (next_comment == -1) {
            break;
        }
        rest = slice_view(rest, next_comment, rest.length);
        //
        int comment_end = search_view(rest, VIEW("-->"));
        assert(comment_end != -1);
        rest = slice_view(rest, comment_end + 3, rest.length);
    }
    return result;
}

int main(int argc, char *argv[]) {
    assert(argc > 4);
    StringView module_name = from_cstr(argv[1]);
    StringView base_filename = from_cstr(argv[2]);
    StringView render_assets_dir = from_cstr(argv[3]);
    StringView output_filename = from_cstr(argv[4]);

    String full_base_filename = join_path(render_assets_dir, base_filename);
    printf("[gen_render] base: %s\n", full_base_filename.buffer);
    String base_content = read_file(as_view(full_base_filename));
    free_string(full_base_filename);

    String result = generate(as_view(base_content));
    StringView template = VIEW(
        "#include \"../render.h\"\n"
        "#include \"../string_view.h\"\n"
        "#include \"@@module_name@@.h\"\n"
        "\n"
        "DECLARE_RENDER(@@module_name@@) {\n"
        "@@body@@\n"
        "}\n"
    );
    StringView body_template = VIEW(
        "String @@result@@ = clone_view(VIEW(\"\"));\n"
        "@@main_body@@\n"
        "return @@result@@;\n"
    );
    String body = replace_view(body_template, VIEW("@@main_body@@"), as_view(result));
    free_string(result);
    String indent_body = indent_view(as_view(body), 4);
    free_string(body);
    
    struct {
        StringView tag;
        StringView content;
    } replace_list[] = {
        { VIEW("@@body@@"), as_view(indent_body) },
        { VIEW("@@module_name@@"), module_name },
        { VIEW("@@result@@"), VIEW("result") },
        { VIEW(""), VIEW("") }
    };

    String output = clone_view(template);
    for (int i = 0; replace_list[i].tag.length; i++) {
        String output_temp = replace_view(as_view(output), replace_list[i].tag, replace_list[i].content);
        free_string(output);
        output = output_temp;
    }
    free_string(indent_body);
    
    write_file(output_filename, as_view(output));
    free_string(base_content);
    return 0;
}

