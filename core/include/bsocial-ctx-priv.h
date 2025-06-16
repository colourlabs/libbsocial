#include <bsocial-types.h>
#include <bsocial-httpclient.h>
#include <bsocial-url-priv.h>
#include <bsocial-ctx.h>

#ifndef BSOCIAL_CTX_PRIV_H
#define BSOCIAL_CTX_PRIV_H

struct _BSocialCtx {
	BSocialReferenceable _parent;
	
	/* client and parser */
	BSocialHTTPClient *client;
	BSocialJSONParser *parser;
 
	/* urls */
	_BSocialURLs urls;
	
	/* user info */
	char *token;
};


#endif /* BSOCIAL_CTX_PRIV_H */
