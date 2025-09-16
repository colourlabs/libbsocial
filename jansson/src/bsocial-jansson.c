#include <stdlib.h>
#include <string.h>
#include <jansson.h>
#include <bsocial.h>
#include <bsocial-jansson.h>
#include <bsocial-types-priv.h>

typedef struct {
	BSocialJSONObject _parent;

	json_t *obj;
} BSocialJanssonJSONObject;

BSocialJSONObject *_bsocial_jansson_json_object_get_object_of_key(BSocialJSONObject *obj, char *key);

BSocialJSONObjectType _bsocial_jansson_json_object_get_type(BSocialJSONObject *obj) {
	BSocialJanssonJSONObject *json_object;
	json_object = (BSocialJanssonJSONObject *)obj;

	/* JSON_ARRAY
	JSON_INTEGER
	JSON_REAL
	JSON_TRUE
	JSON_FALSE */

	switch (json_typeof(json_object->obj)) {
		case JSON_OBJECT:
			return BSOCIAL_JSON_OBJECT_TYPE_OBJECT;
			break;
		case JSON_STRING:
			return BSOCIAL_JSON_OBJECT_TYPE_STRING;
			break;		
		default:
			return BSOCIAL_JSON_OBJECT_TYPE_NULL;
	}
}

char *_bsocial_jansson_json_object_get_string_value(BSocialJSONObject *obj) {
	BSocialJanssonJSONObject *json_object;

	json_object = (BSocialJanssonJSONObject *)obj;

	return (char *)json_string_value(json_object->obj);
}

void _bsocial_jansson_json_object_free_string_value(BSocialJSONObject *obj, char *str) {
	/* do nothing */
}

void _bsocial_jansson_json_object_free(BSocialJSONObject *obj) {
	BSocialJanssonJSONObject *json_object;

	json_object = (BSocialJanssonJSONObject *)obj;

	json_decref(json_object->obj);		
}

void _fill_parent(BSocialJSONParser *parser, BSocialJSONObject *obj) {
	obj->from_parser = parser;
	obj->vtable.get_type = _bsocial_jansson_json_object_get_type;
	obj->vtable.get_object_of_key = _bsocial_jansson_json_object_get_object_of_key;
	obj->vtable.get_string_value = _bsocial_jansson_json_object_get_string_value;
	obj->vtable.free_string_value = _bsocial_jansson_json_object_free_string_value;
	obj->vtable.free = _bsocial_jansson_json_object_free;
}

BSocialJSONObject *_bsocial_jansson_json_object_get_object_of_key(BSocialJSONObject *obj, char *key) {
	BSocialJanssonJSONObject *json_object;
	BSocialJanssonJSONObject *ret_json_object;
	BSocialJSONObject *pret_json_object;

	json_object = (BSocialJanssonJSONObject *)obj;
	ret_json_object = malloc(sizeof(BSocialJanssonJSONObject));
	if (!ret_json_object) {
		_BSOCIAL_RET_ERROR(ret_json_object);		
	}	
	pret_json_object = (BSocialJSONObject *)ret_json_object;
	
	ret_json_object->obj = json_object_get(json_object->obj, key);
	if (!ret_json_object->obj) {
		_BSOCIAL_RET_ERROR(ret_json_object);
	}
	
	_fill_parent(obj->from_parser, pret_json_object);

	return pret_json_object;
}

BSocialJSONObject *_bsocial_jansson_json_parser_parse_str(BSocialJSONParser *parser, char *str) {
	BSocialJanssonJSONObject *json_object;
	BSocialJSONObject *pjson_object;
	json_error_t error;

	json_object = malloc(sizeof(BSocialJanssonJSONObject));
	if (!json_object) {
		_BSOCIAL_RET_ERROR(json_object);		
	}	
	pjson_object = (BSocialJSONObject *)json_object;

	json_object->obj = json_loads(str, 0, &error);
	if (!json_object->obj) {
		_BSOCIAL_RET_ERROR(json_object);
	}
	
	_fill_parent(parser, pjson_object);

	return pjson_object;
}

void _bsocial_jansson_json_parser_free(BSocialJSONParser *parser) {
	if (parser) {
		free(parser);
	}
}

BSocialJSONParser *bsocial_jansson_json_parser_new(void) {
	BSocialJSONParser *parser;

	parser = malloc(sizeof(BSocialJSONParser));
	if (!parser) {
		_BSOCIAL_RET_ERROR(parser);		
	}
	
	parser->type = "Jansson";
	parser->vtable.parse_str = _bsocial_jansson_json_parser_parse_str;
	parser->vtable.free = _bsocial_jansson_json_parser_free;	
	
	return parser;	
}
