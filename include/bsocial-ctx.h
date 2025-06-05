#ifdef BSOCIAL_PRIV
#include <curl/curl.h>
#endif
#include <bsocial-export.h>
#include <bsocial-types.h>

#ifndef BSOCIAL_CTX_H
#define BSOCIAL_CTX_H

typedef struct _BSocialCtx BSocialCtx;
#define BSOCIAL_CTX(x) ((BSocialCtx*)x)
#ifdef BSOCIAL_PRIV
struct _BSocialCtx {
	BSocialReferenceable _parent;
	
	/* curl */
	CURL *curl_ctx;
	
	/* user info */
	char *token;
};
#endif
BSOCIAL_EXPORT BSocialCtx *bsocial_ctx_new(BSocialError *err_ret);
BSOCIAL_EXPORT BSocialError bsocial_ctx_login(BSocialCtx *ctx, char *username, char *pwd);


#endif /* BSOCIAL_CTX_H */
