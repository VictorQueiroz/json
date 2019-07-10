#include "json_string.h"

#include <stdio.h>

json_value* json_string_alloc(const char* string) {
    size_t length = strlen(string);
    json_value* value = json_value_alloc();
    value->type = JSONValueString;
    value->json_string = malloc(length + 1);
    memcpy(value->json_string, string, length);
    value->json_string[length] = 0;
    return value;
}
