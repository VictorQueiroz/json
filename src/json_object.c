#include "json_object.h"

CVECTOR_NEW(json_object_values_list, json_object_value*)

void json_object_values_list_free_items(json_object_values_list* list) {
    vector_foreach(list, i) {
        json_object_value_free(vector_get(list, i));
    }
}

void json_object_value_free(json_object_value* value) {
    if(value->property != NULL) {
        free(value->property);
    }
    json_value_free(value->value);
    free(value);
}

json_object_value* json_object_value_alloc() {
    json_object_value* value = calloc(1, sizeof(json_object_value));
    return value;
}

json_object* json_object_alloc() {
    json_object* value = calloc(1, sizeof(json_object));
    value->values = json_object_values_list_alloc();
    return value;
}

json_object_value* json_object_get_object_value(json_object* obj, const char* property) {
    json_object_value* item = NULL;
    vector_foreach(obj->values, i) {
        item = vector_get(obj->values, i);
        if(strcmp(item->property, property) != 0) {
            continue;
        }
        return item;
    }
    return NULL;
}

json_value* json_object_get_property(json_object* obj, const char* property) {
    json_object_value* item = json_object_get_object_value(obj, property);
    if(!item) {
        return NULL;
    }
    return item->value;
}

uint8_t json_object_set_property(json_object* obj, const char* property, json_value* value) {
    json_object_value* item = json_object_get_object_value(obj, property);
    if(item != NULL) {
        json_object_value_free(item);
    }
    size_t property_length = strlen(property);
    json_object_value* object_value = json_object_value_alloc();
    if(!object_value) {
        return JSONMemoryAllocationError;
    }
    object_value->property = malloc(property_length + 1);
    memcpy(object_value->property, property, property_length);
    object_value->property[property_length] = 0;
    object_value->value = value;
    if(json_object_values_list_add(obj->values, object_value) != CVECTOR_OK) {
        return JSONUnknownError;
    }
    return JSONOk;
}

void json_object_free(json_object* value) {
    json_object_values_list_free(value->values);
    free(value);
}
