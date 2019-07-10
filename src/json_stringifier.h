#ifndef JSON_JSON_STRINGIFIER_H
#define JSON_JSON_STRINGIFIER_H

#define JSON_MAX_NUMBER_LENGTH 2048*4

#include "json_value.h"

#include <cvector.h>

CVECTOR_HEAD(json_characters_list, char*)

typedef struct _json_stringifier json_stringifier;

struct _json_stringifier {
    json_characters_list* characters_list;
};

json_stringifier* json_stringifier_alloc();
void json_stringifier_free(json_stringifier*);
void json_stringifier_stringify(json_stringifier*, json_value*);

#endif //JSON_JSON_STRINGIFIER_H
