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
    void test_render2();
    test_render2();

    return 0;
}

static void assert_equal(String first, String second) {
    assert(first && second);
    assert(first->length == second->length);
    for (int i = 0; i < first->length; i++) {
        assert(first->buffer[i] == second->buffer[i]);
    }
    free_string(first);
    free_string(second);
}

void test_clone() {
    printf(" - clone\n");
    String cowsay = LITERAL("cowsay");
    String cowsay2 = clone_string(cowsay);
    assert_equal(cowsay, cowsay2);
}

void test_concat() {
    printf(" - concat\n");
    String hello = LITERAL("Hello, "), world = LITERAL("world!");
    String hello_world = concat_string(hello, world);
    free_string(hello);
    free_string(world);
    assert_equal(hello_world, LITERAL("Hello, world!"));
}

void test_render() {
    printf(" - render\n");
    String template = LITERAL("Hello, @@NAME@@!");
    String name = LITERAL("cowsay");
    String greetings = render_string(template, "NAME", name);
    free_string(template);
    free_string(name);
    assert_equal(greetings, LITERAL("Hello, cowsay!"));
}

void test_render2() {
    printf(" - render2\n");
    String template = LITERAL("The @@FRUIT@@ is @@COLOR@@.");
    String fruit = LITERAL("apple"), color = LITERAL("red");
    assert_equal(
        render_string(template, "FRUIT", fruit), 
        LITERAL("The apple is @@COLOR@@.")
    );
    assert_equal(
        render_string(template, "COLOR", color),
        LITERAL("The @@FRUIT@@ is red.")
    );
    assert_equal(
        render_string(render_string(template, "FRUIT", fruit), "COLOR", color),
        render_string(render_string(template, "COLOR", color), "FRUIT", fruit)
    );
    free_string(template);
    free_string(fruit);
    free_string(color);
}

