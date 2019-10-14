//

#include "string.h"
#include <stdio.h>
#include <assert.h>

#define SECTION(title) printf("- " #title "\n");

void assert_equal_move(String string1, String string2) {
    assert(equal_string(string1, string2));
    free_string(string1);
    free_string(string2);
}

int main(void) {
    printf("string\n");
    String hello = STRING("hello");
    assert(hello.buffer);
    assert(hello.length == 5);
    free_string(hello);

    SECTION(equal) {
        String cowsay = STRING("cowsay");
        assert(equal_string(cowsay, cowsay));
        String catsay = STRING("catsay");
        assert(!equal_string(cowsay, catsay));
        assert(!equal_string(catsay, cowsay));
        free_string(cowsay);
        free_string(catsay);
    }

    SECTION(clone) {
        String original = STRING("cowsay");
        String cloned = clone_string(original);
        assert_equal_move(original, cloned);
    }

    SECTION(slice) {
        String cowsay = STRING("cowsay");
        assert_equal_move(slice_string(cowsay, 0, 3), STRING("cow"));
        assert_equal_move(slice_string(cowsay, 0, -3), STRING("cow"));
        assert_equal_move(slice_string(cowsay, 3, 6), STRING("say"));
        free_string(cowsay);
    }

    SECTION(equal_offset) {
        String cowsay = STRING("cowsay");
        cowsay.offset = 1;
        cowsay.length = 5;
        assert_equal_move(cowsay, STRING("owsay"));
    }

    SECTION(cut) {
        String cowsay = STRING("cowsay");
        cut_string(&cowsay, 0, -3);
        assert_equal_move(cowsay, STRING("cow"));
    }

    SECTION(cut_head) {
        String cowsay = STRING("cowsay");
        String cow = cut_head(&cowsay, 3);
        assert_equal_move(cow, STRING("cow"));
        assert_equal_move(cowsay, STRING("say"));
    }

    SECTION(char_at) {
        String cowsay = STRING("cowsay");
        char *expected = "cowsay";
        for (int i = 0; i < 6; i++) {
            assert_equal_move(char_at(cowsay, i), create_string(&expected[i], 1));
            assert_equal_move(char_at(cowsay, i), char_at(cowsay, i - 6));
        }
        free_string(cowsay);
    }

    return 0;
}
