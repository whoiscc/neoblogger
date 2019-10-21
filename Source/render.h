//
#ifndef NEOBLOGGER_SOURCE_RENDER_H
#define NEOBLOGGER_SOURCE_RENDER_H

#include "string_view.h"

#define CONTEXT_TYPE(name) Context_##name

#define CONTEXT context

#define DECLARE_RENDER(name) \
    String render_##name(CONTEXT_TYPE(name) *CONTEXT)

#endif
