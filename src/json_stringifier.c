#include "json_stringifier.h"
#include "json_value.h"

#include <stdio.h>
#include <stdlib.h>

CVECTOR_NEW(json_characters_list, char)

void json_characters_list_free_items(json_characters_list* list) {
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

void json_stringifier_write_with_options(json_stringifier* s, char* ch, enum JSONBoolean escape) {
    size_t length = strlen(ch);
    size_t i;
    for(i = 0; i < length; i++) {
        if(escape == JSONTrue) {
            if(ch[i] == '"') {
                json_characters_list_add(s->characters_list, '\\');
                s->output_string_length++;
            }
        }
        json_characters_list_add(s->characters_list, ch[i]);
        s->output_string_length++;
    }
}

void json_stringifier_write(json_stringifier* s, char* ch) {
    json_stringifier_write_with_options(s, ch, JSONFalse);
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
        json_stringifier_write(s, "\":");
        json_stringifier_stringify(s, item->value);
        if((length - 1) != i) {
            json_stringifier_write(s, ",");
        }
    }
    json_stringifier_write(s, "}");
}

char* json_stringifier_to_string(json_stringifier* s) {
    return s->characters_list->data;
}

void json_stringifier_stringify(json_stringifier* s, json_value* value) {
    switch(value->type) {
        case JSONValueArray:
            json_stringifier_stringify_array(s, value->json_array);
            break;
        case JSONValueUndefined:
            json_stringifier_write(s, "undefined");
            break;
        case JSONValueNull:
            json_stringifier_write(s, "null");
            break;
        case JSONValueString:
            json_stringifier_write(s, "\"");
            json_stringifier_write_with_options(s, value->json_string, JSONTrue);
            json_stringifier_write(s, "\"");
            break;
        case JSONValueObject:
            json_stringifier_stringify_object(s, value->json_object);
            break;
        case JSONValueNumber: {
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
