#ifndef JSON_VALUE_H_
#define JSON_VALUE_H_

typedef struct _json_value json_value;

#include "json_array.h"
#include "json_object.h"

#include <cvector.h>
#include <stdlib.h>

#define JSON_VALUE_OBJECT 1
#define JSON_VALUE_ARRAY 2
#define JSON_VALUE_NUMBER 3
#define JSON_VALUE_STRING 4

struct _json_value {
    uint8_t type;
    json_object* json_object;
    double json_number;
    char* json_string;
    json_array* json_array;
};

json_value* json_value_alloc();
void json_value_free(json_value*);

#endif // JSON_VALUE_H_