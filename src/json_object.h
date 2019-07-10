#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

typedef struct _json_object json_object;
typedef struct _json_object_value json_object_value;

#include "json_value.h"

#include <cvector.h>

struct _json_object_value {
    char* property;
    json_value* value;
};

void json_object_value_free(json_object_value*);
json_object_value* json_object_value_alloc();

CVECTOR_HEAD(json_object_values_list, struct _json_object_value*)

struct _json_object {
    json_object_values_list* values;
};

json_object* json_object_alloc();
void json_object_free(json_object*);

/**
 * Add, remove or change property from an object. Pass NULL to value to remove the property.
 * If another property exists on the object, it'll be freed and replaced with new property value.
 * @param obj
 * @param property
 * @param value
 */
uint8_t json_object_set_property(json_object* obj, const char* property, json_value* value);

/**
 * @param obj
 * @param property
 * @return NULL if property is not found, property value if it is
 */
json_value* json_object_get_property(json_object* obj, const char* property);

json_object_value* json_object_get_object_value(json_object*, const char*);

#endif //JSON_OBJECT_H
