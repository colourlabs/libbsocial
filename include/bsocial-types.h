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
BSOCIAL_EXPORT void bsocial_referenceable_ref(BSocialReferenceable *r);
BSOCIAL_EXPORT void bsocial_referenceable_unref(BSocialReferenceable *r);

/* ERRORS */
typedef enum {
    BSOCIAL_ERROR_NONE = 0,
    BSOCIAL_ERROR_ALLOC_FAILED,
    BSOCIAL_ERROR_HTTP_CLIENT_CREATION_FAILED
} BSocialError;

#endif /* BSOCIAL_TYPES_H */
