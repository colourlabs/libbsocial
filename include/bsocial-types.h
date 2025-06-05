#include <bsocial-export.h>

#ifndef BSOCIAL_TYPES_H
#define BSOCIAL_TYPES_H

/* BOOL */
typedef enum {
    BSOCIAL_FALSE = 0,
    BSOCIAL_TRUE = 1
} BSocialBool;

/* REF COUNTING */
typedef struct _BSocialReferenceable BSocialReferenceable;
#define BSOCIAL_REFERENCEABLE(x) ((BSocialReferenceable*)x)
#ifdef BSOCIAL_PRIV
struct _BSocialReferenceable  {
    unsigned int refs;
	void (*free)(struct _BSocialReferenceable *rc);
};

void _bsocial_referenceable_init(BSocialReferenceable *r, void (*free_func)(BSocialReferenceable *r));
#endif
BSOCIAL_EXPORT void bsocial_referenceable_ref(BSocialReferenceable *r);
BSOCIAL_EXPORT void bsocial_referenceable_unref(BSocialReferenceable *r);

/* ERRORS */
typedef enum {
    BSOCIAL_ERROR_NONE = 0,
    BSOCIAL_ERROR_ALLOC_FAILED,
    BSOCIAL_ERROR_UNABLE_TO_CREATE_HTTP_CLIENT
} BSocialError;
#ifdef BSOCIAL_PRIV
#define _BSOCIAL_ERROR_SET_RET(x, y) if (x) { *x = y; } 
#endif

#endif /* BSOCIAL_TYPES_H */
