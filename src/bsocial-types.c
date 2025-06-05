#define BSOCIAL_PRIV
#include <stdlib.h>
#include <bsocial-types.h>

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
