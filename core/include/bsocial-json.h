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

#define bsocial_json_parser_parse_str(p, s) p->vtable.parse_str(p, s)
#define bsocial_json_parser_free(p) p->vtable.free(p)

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

#define bsocial_json_object_get_type(o) o->vtable.get_type(o)
#define bsocial_json_object_get_object_of_key(o, k) o->vtable.get_object_of_key(o, k)
#define bsocial_json_object_get_string_value(o) o->vtable.get_string_value(o)
#define bsocial_json_object_free_string_value(o, s) o->vtable.free_string_value(o, s)
#define bsocial_json_object_free(o) o->vtable.free(o)


#endif /* BSOCIAL_JSON_H */
