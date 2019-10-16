//

#include "file.h"
#include "string_view.h"
#include "helper.h"


TEST(file) {
    StringView filename = VIEW("Tests/file.c");
    String content = read_file(filename);
    assert(content.buffer);
    assert(content.length > 0);
    free_string(content);

    SECTION(write) {
        StringView content = VIEW("The answer is 42.");
        StringView filename = VIEW("test_file.txt");
        assert(write_file(filename, content) == 0);
        String actual_content = read_file(filename);
        assert(equal_view(as_view(actual_content), content));
        free_string(actual_content);
        assert(delete_file(filename) == 0);
    }
}
