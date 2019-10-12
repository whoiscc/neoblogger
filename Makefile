#

CC = clang
CFLAGS += -g


project = neoblogger
source_dir = Source
tests_dir = Tests
core_modules = render
modules = $(core_modules)


all: source test


static_library = lib$(project).a
source_objects = $(modules:%=$(source_dir)/%.o)
source: $(static_library)
$(static_library): $(source_objects)
	$(AR) rc $@ $+


test_executables = $(core_modules:%=test_%)
test: $(test_executables)
$(test_executables): test_%: $(tests_dir)/%.c $(static_library)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $+


clean:
	-$(RM) $(source_objects)
	-$(RM) $(static_library)
	-$(RM) $(test_executables)
