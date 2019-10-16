//

#include "string_view.h"
#include <stdio.h>
#include <assert.h>

#define SECTION(title) printf("- " #title "\n");

int main(void) {
    printf("string_view\n");
    StringView hello = VIEW("hello");
    assert(hello.ref);
    assert(hello.length == 5);

    SECTION(equal) {
        StringView cowsay = VIEW("cowsay");
        assert(equal_view(cowsay, cowsay));
        StringView catsay = VIEW("catsay");
        assert(!equal_view(cowsay, catsay));
        assert(!equal_view(catsay, cowsay));
    }

    SECTION(clone) {
        StringView original = VIEW("cowsay");
        String cloned = clone_view(original);
        assert(equal_view(original, as_view(cloned)));
        free_string(cloned);
    }

    SECTION(slice) {
        StringView cowsay = VIEW("cowsay");
        assert(equal_view(slice_view(cowsay, 0, 3), VIEW("cow")));
        assert(equal_view(slice_view(cowsay, 0, -3), VIEW("cow")));
        assert(equal_view(slice_view(cowsay, 3, 6), VIEW("say")));
    }

    SECTION(char_at) {
        StringView cowsay = VIEW("cowsay");
        char *expected = "cowsay";
        for (int i = 0; i < 6; i++) {
            assert(equal_view(char_at(cowsay, i), create_view(&expected[i], 1)));
            assert(equal_view(char_at(cowsay, i), char_at(cowsay, i - 6)));
        }
    }

    return 0;
}
