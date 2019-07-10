#ifndef JSON_VALUE_H_
#define JSON_VALUE_H_

typedef struct _json_value json_value;

#include "json_array.h"
#include "json_object.h"

#include <cvector.h>
#include <stdlib.h>

enum JSONResultCode {
    JSONOk,
    JSONUnknownError,
    JSONMemoryAllocationError
};

enum JSONBoolean {
    JSONFalse = 0,
    JSONTrue = 1
};

enum JSONValue {
    JSONValueObject = 1,
    JSONValueArray,
    JSONValueNumber,
    JSONValueString,
    JSONValueUndefined,
    JSONValueNull
};

struct _json_value {
    enum JSONValue type;
    json_object* json_object;
    double json_number;
    char* json_string;
    json_array* json_array;
};

json_value* json_value_alloc();
json_value* json_undefined_alloc();
void json_value_free(json_value*);

#endif // JSON_VALUE_H_