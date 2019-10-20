//

#include "string_view.h"
#include "helper.h"


TEST(string_view) {
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

    SECTION(replace) {
        StringView original = VIEW("My name is cowsay, cowsay is my name.");
        String replaced = replace_view(original, VIEW("cowsay"), VIEW("catsay"));
        assert(equal_view(as_view(replaced), VIEW("My name is catsay, catsay is my name.")));
        free_string(replaced);
    }

    SECTION(quote) {
        StringView original = VIEW("The symbol \'\\\' is called \"backslash\".");
        String quoted = quote_view(original);
        assert(equal_view(as_view(quoted), VIEW("\"The symbol \\\'\\\\\\\' is called \\\"backslash\\\".\"")));
        free_string(quoted);
    }

    SECTION(split) {
        int i = 0;
        StringView expected[] = { VIEW("How"), VIEW("are"), VIEW("you?") };
        for (
            SplitViewIter iter = split_view(VIEW("How are you?"), VIEW(" "));
            iter_split_view(&iter);
        ) {
            assert(equal_view(iter.part, expected[i]));
            i += 1;
        }
    }
    
    SECTION(split_empty) {
        int i = 0;
        StringView expected[] = { VIEW("I\'m"), VIEW(""), VIEW("fine."), VIEW("") };
        for (
            SplitViewIter iter = split_view(VIEW("I\'m  fine. "), VIEW(" "));
            iter_split_view(&iter);
        ) {
            assert(equal_view(iter.part, expected[i]));
            i += 1;
        }
    }

    SECTION(indent) {
        String result = indent_view(VIEW(
            "int a = 40, b = 2, c;\n"
            "c = a + b;\n"
        ), 2);
        assert(equal_view(as_view(result), VIEW(
            "  int a = 40, b = 2, c;\n"
            "  c = a + b;\n"
            "  "
        )));
        free_string(result);
    }
}

