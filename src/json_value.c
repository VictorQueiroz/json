#include "json_value.h"

json_value* json_value_alloc() {
    json_value* value = calloc(1, sizeof(json_value));
    return value;
}

json_value* json_undefined_alloc() {
    json_value* value = json_value_alloc();
    value->type = JSONValueUndefined;
    return value;
}

json_value* json_null_alloc() {
    json_value* value = json_value_alloc();
    value->type = JSONValueNull;
    return value;
}

void json_value_free(json_value* value) {
    switch(value->type) {
        case JSONValueString:
            free(value->json_string);
            break;
        case JSONValueArray:
            json_array_free(value->json_array);
            break;
        case JSONValueObject:
            json_object_free(value->json_object);
            break;
    }
    free(value);
}
