#include <bsocial-export.h>
#include <bsocial-types.h>

#ifndef BSOCIAL_JSON_H
#define BSOCIAL_JSON_H

typedef struct _BSocialJSONParser {
	char *type;

	struct _BSocialJSONParserVTable {
		struct _BSocialJSONObject *(*parse_str)(struct _BSocialJSONParser *parser, char *string);
		void (*free)(struct _BSocialJSONParser *parser);
	} vtable;
} BSocialJSONParser;

typedef enum {
	BSOCIAL_JSON_OBJECT_TYPE_NULL = 0,
	BSOCIAL_JSON_OBJECT_TYPE_OBJECT,
	BSOCIAL_JSON_OBJECT_TYPE_STRING
} BSocialJSONObjectType;

typedef struct _BSocialJSONObject {
	BSocialJSONParser *from_parser;

	struct _BSocialJSONObjectVTable {
		BSocialJSONObjectType (*get_type)(struct _BSocialJSONObject *obj);
		struct _BSocialJSONObject *(*get_object_of_key)(struct _BSocialJSONObject *obj, char *key);
		char *(*get_string_value)(struct _BSocialJSONObject *obj);
		void (*free_string_value)(struct _BSocialJSONObject *obj, char *string);
		void (*free)(struct _BSocialJSONObject *obj);
	} vtable;	
} BSocialJSONObject;

#endif /* BSOCIAL_JSON_H */
