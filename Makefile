#

CC = clang
CFLAGS += -g


project = neoblogger
source_dir = Source
tests_dir = Tests
# core modules are modules with tests
core_modules = string_view file
modules = $(core_modules)
render_modules = post
render_dir = Render
assets_dir = Assets
gen_render_exe = gen_render
gen_render_main = gen_render
render_base = base.html


all: source testcases


static_library = lib$(project).a
core_source_objects = $(core_modules:%=$(source_dir)/%.o)
source_objects = $(modules:%=$(source_dir)/%.o)
render_source_objects = $(render_modules:%=$(source_dir)/$(render_dir)/%.o)
source_objects += $(render_source_objects)
source: $(static_library)
$(static_library): $(source_objects)
	$(AR) rc $@ $+
$(source_dir)/$(render_dir)/%.c: $(assets_dir)/$(render_dir)/$(render_base) $(assets_dir)/$(render_dir)/%/*.html $(gen_render_exe)
	./$(gen_render_exe) $(basename $(notdir $@)) $(render_base) $(assets_dir)/$(render_dir) $@
source_deps = $(source_objects:%.o=%.d)
include $(source_deps)
%.d: %.c
	$(CC) -MM -MP -MT '$(<:%.c=%.o) $(<:%.c=%.d)' -MF $(<:%.c=%.d) $<
$(gen_render_exe): $(core_source_objects) $(source_dir)/$(gen_render_main).o
	$(CC) $(CFLAGS) -o $@ $+


test_executables = $(core_modules:%=test_%)
testcases: $(test_executables)
$(test_executables): test_%: $(tests_dir)/%.c $(static_library)
	$(CC) $(CFLAGS) -I$(source_dir) -o $@ $+


test: testcases
	for test in $(test_executables); do \
		./$$test || break; \
	done


clean:
	-$(RM) $(source_objects)
	-$(RM) $(source_deps)
	-$(RM) $(static_library)
	-$(RM) $(test_executables)
	-$(RM) $(render_modules:%=$(source_dir)/$(render_dir)/%.c)
	-$(RM) $(gen_render_exe) $(source_dir)/$(gen_render_main).o

