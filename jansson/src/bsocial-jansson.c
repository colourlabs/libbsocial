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

BSocialJSONParser *bsocial_jansson_jsonparser_new(void) {
	
}
