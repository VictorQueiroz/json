#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

typedef struct _json_object json_object;
typedef struct _json_object_value json_object_value;

#include "json_value.h"

#include <cvector.h>

struct _json_object_value {
    char* property;
    json_value* value;
};

void json_object_value_free(json_object_value*);
json_object_value* json_object_value_alloc();

CVECTOR_HEAD(json_object_values_list, struct _json_object_value*)

struct _json_object {
    json_object_values_list* values;
};


#endif //JSON_OBJECT_H
