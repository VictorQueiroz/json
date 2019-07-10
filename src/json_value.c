#include "json_value.h"

json_value* json_value_alloc() {
    json_value* value = calloc(1, sizeof(json_value));
    return value;
}

void json_value_free(json_value* value) {
    switch(value->type) {
        case JSON_VALUE_STRING:
            free(value->json_string);
            break;
        case JSON_VALUE_ARRAY:
            json_array_free(value->json_array);
            break;
    }
    free(value);
}
