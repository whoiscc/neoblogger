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
        "\n"
        "String render_"
    ));
    append_string(&output, module_name);
    append_string(&output, VIEW(
        "(Context cotext) {\n"
        "    return clone_view(VIEW(\"\"));\n"
        "}\n"
    ));

    assert(write_file(output_filename, as_view(output)) == 0);
    free_string(input);
    free_string(output);
    return 0;
}

