//
#ifndef NEOBLOGGER_SOURCE_FILE_H
#define NEOBLOGGER_SOURCE_FILE_H

#include "string_view.h"

String read_file(const StringView filename);

int write_file(const StringView filename, const StringView content);

int delete_file(const StringView filename);

#endif
