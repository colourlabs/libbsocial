#include <stdlib.h>
#include <bsocial-types.h>
#include <bsocial-types-priv.h>

void _bsocial_referenceable_init(BSocialReferenceable *r, void (*free_func)(BSocialReferenceable *r)) {
	r->refs = 1;
	r->free = free_func;
}

void bsocial_referenceable_ref(BSocialReferenceable *r) {
	if (r) {
		r->refs++;
	}	
}

void bsocial_referenceable_unref(BSocialReferenceable *r) {
	if (r) {
		if (--r->refs == 0) {
			r->free(r);
		} 
	} 
}

char *bsocial_error_message(BSocialError error) {
	switch (error) {
		case BSOCIAL_ERROR_NONE:
			return "Nothing is wrong.";
			break;
		case BSOCIAL_ERROR_ALLOC_FAILED:
			return "Memory allocation failure.";
			break;
		case BSOCIAL_ERROR_HTTP_CLIENT_CREATION_FAILED:
			return "Unable to create HTTP client.";
			break;
		case BSOCIAL_ERROR_INVALID_PARAM:
			return "An invalid parameter has been given.";
			break;
		default:
			return "What the heck?!";
    }	
}
