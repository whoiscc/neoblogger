#

CC = clang
CFLAGS += -g


project = neoblogger
source_dir = Source
tests_dir = Tests
core_modules = string_view file
modules = $(core_modules)


all: source testcases


static_library = lib$(project).a
source_objects = $(modules:%=$(source_dir)/%.o)
source: $(static_library)
$(static_library): $(source_objects)
	$(AR) rc $@ $+
source_deps = $(source_objects:%.o=%.d)
include $(source_deps)
%.d: %.c
	$(CC) -MM -MP -MT '$(<:%.c=%.o) $(<:%.c=%.d)' -MF $(<:%.c=%.d) $<


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
