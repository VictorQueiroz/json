#include "json_object.h"

CVECTOR_NEW(json_object_values_list, json_object_value*)

void json_object_values_list_free_items(json_object_values_list* list) {
    vector_foreach(list, i) {
        json_object_value_free(vector_get(list, i));
    }
}

void json_object_value_free(json_object_value* value) {
    json_value_free(value->value);
    free(value);
}

json_object_value* json_object_value_alloc() {
    json_object_value* value = calloc(1, sizeof(json_object_value));
    return value;
}

