#include <bsocial-export.h>

#ifndef BSOCIAL_TYPES_PRIV_H
#define BSOCIAL_TYPES_PRIV_H

/* REF COUNTING */
struct _BSocialReferenceable  {
    unsigned int refs;
	void (*free)(struct _BSocialReferenceable *rc);
};

void _bsocial_referenceable_init(BSocialReferenceable *r, void (*free_func)(BSocialReferenceable *r));

/* ERRORS */
#define _BSOCIAL_ERROR_SET_RET(x, y) if (x) { *x = y; } 

#endif /* BSOCIAL_TYPES_PRIV_H */
