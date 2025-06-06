#include <curl/curl.h>
#include <bsocial-types.h>
#include <bsocial-ctx.h>

#ifndef BSOCIAL_CTX_PRIV_H
#define BSOCIAL_CTX_PRIV_H

struct _BSocialCtx {
	BSocialReferenceable _parent;
	
	/* curl */
	CURL *curl_ctx;
	
	/* user info */
	char *token;
};

#endif /* BSOCIAL_CTX_PRIV_H */
