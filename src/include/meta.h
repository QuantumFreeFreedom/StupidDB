#ifndef META
#define META
#include "input.h"

typedef enum {
    META_COMMAND,
    META_UNRECOGNIZED_COMMAND
} MetaType;

MetaType execute_meta(Input* statement);
void meta_init(Input *statement);

#endif