#ifndef JSON_ARRAY_H
#define JSON_ARRAY_H

typedef struct _json_array json_array;

#include "json_value.h"

#include <cvector.h>

CVECTOR_HEAD(json_values_list, struct _json_value*)

struct _json_array {
    json_values_list* items;
};

json_array* json_array_alloc();
void json_array_free(json_array*);

#endif //JSON_ARRAY_H
