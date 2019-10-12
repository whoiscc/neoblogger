//

#include "string.h"
#include <stdio.h>
#include <assert.h>


int main(void) {
    printf("string test\n");
    String hello = LITERAL("hello");
    assert(hello);
    assert(hello->buffer);
    assert(hello->length == 5);
    free_string(hello);

    void test_clone();
    test_clone();
    void test_concat();
    test_concat();
    void test_render();
    test_render();

    return 0;
}

void test_clone() {
    printf(" - clone\n");
    String cowsay = LITERAL("cowsay");
    String cowsay2 = clone_string(cowsay);
    assert(cowsay2->buffer);
    assert(cowsay2->length == 6);
    for (int i = 0; i < 6; i++) {
        assert(cowsay2->buffer[i] == cowsay->buffer[i]);
    }
    free_string(cowsay);
    free_string(cowsay2);
}

void test_concat() {
    printf(" - concat\n");
    String hello = LITERAL("Hello, "), world = LITERAL("world!");
    String hello_world = concat_string(hello, world);
    free_string(hello);
    free_string(world);
    String expected = LITERAL("Hello, world!");
    assert(hello_world->length == expected->length);
    for (int i = 0; i < hello_world->length; i++) {
        assert(hello_world->buffer[i] == expected->buffer[i]);
    }
    free_string(expected);
    free_string(hello_world);
}

void test_render() {
    printf(" - render\n");
    String template = LITERAL("Hello, @@NAME@@!");
    String name = LITERAL("cowsay");
    String greetings = render_string(template, "NAME", name);
    free_string(template);
    free_string(name);
    String expected = LITERAL("Hello, cowsay!");
    assert(greetings->length == expected->length);
    for (int i = 0; i < greetings->length; i++) {
        assert(greetings->buffer[i] == expected->buffer[i]);
    }
    free_string(expected);
    free_string(greetings);
}

