#include "json_array.h"
#include "json_value.h"

CVECTOR_NEW(json_values_list, struct _json_value*)

void json_values_list_free_items(json_values_list* list) {
    vector_foreach(list, i) {
        json_value_free(vector_get(list, i));
    }
}

json_array* json_array_alloc() {
    json_array* value = calloc(1, sizeof(json_array));
    value->items = json_values_list_alloc();
    return value;
}

void json_array_free(json_array* list) {
    json_values_list_free(list->items);
    free(list);
}

