#include "json_stringifier.h"
#include "json_value.h"

#include <stdio.h>
#include <stdlib.h>

CVECTOR_NEW(json_characters_list, char*)

void json_characters_list_free_items(json_characters_list* list) {
    vector_foreach(list, i) {
        free(vector_get(list, i));
    }
}

json_stringifier* json_stringifier_alloc() {
    json_stringifier* value = calloc(1, sizeof(json_stringifier));
    value->characters_list = json_characters_list_alloc();
    return value;
}

void json_stringifier_free(json_stringifier* item) {
    json_characters_list_free(item->characters_list);
    free(item);
}

void json_stringifier_write(json_stringifier* s, char* ch) {
    size_t length = strlen(ch);
    char* copied = malloc(length + 1);
    memcpy(copied, ch, length);
    copied[length] = 0;
    json_characters_list_add(s->characters_list, copied);
}

void json_stringifier_stringify_array(json_stringifier* s, json_array* value) {
    json_stringifier_write(s, "[");
    json_value* item;
    size_t length = json_values_list_length(value->items);
    vector_foreach(value->items, i) {
        item = vector_get(value->items, i);
        json_stringifier_stringify(s, item);
        if((length - 1) != i) {
            json_stringifier_write(s, ",");
        }
    }
    json_stringifier_write(s, "]");
}

void json_stringifier_stringify_object(json_stringifier* s, json_object* object) {
    json_stringifier_write(s, "{");
    size_t length = json_object_values_list_length(object->values);
    vector_foreach(object->values, i) {
        json_object_value* item = vector_get(object->values, i);
        json_stringifier_write(s, "\"");
        json_stringifier_write(s, item->property);
        json_stringifier_write(s, "\": ");
        json_stringifier_stringify(s, item->value);
        if((length - 1) != i) {
            json_stringifier_write(s, ",");
        }
    }
    json_stringifier_write(s, "}");
}

void json_stringifier_stringify(json_stringifier* s, json_value* value) {
    switch(value->type) {
        case JSON_VALUE_ARRAY:
            json_stringifier_stringify_array(s, value->json_array);
            break;
        case JSON_VALUE_STRING:
            json_stringifier_write(s, "\"");
            json_stringifier_write(s, value->json_string);
            json_stringifier_write(s, "\"");
            break;
        case JSON_VALUE_OBJECT:
            json_stringifier_stringify_object(s, value->json_object);
            break;
        case JSON_VALUE_NUMBER: {
            char output[JSON_MAX_NUMBER_LENGTH];
            int length = sprintf(output, "%.6f", value->json_number);
            char trimmed[length + 1];
            memcpy(trimmed, output, length);
            trimmed[length] = 0;
            json_stringifier_write(s, trimmed);
            break;
        }
    }
}
