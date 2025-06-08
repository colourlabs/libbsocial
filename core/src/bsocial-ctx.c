#include <stdlib.h>
#include <stdio.h>
#include <bsocial-types.h>
#include <bsocial-types-priv.h>
#include <bsocial-url-priv.h>
#include <bsocial-httpclient.h>
#include <bsocial-ctx.h>
#include <bsocial-ctx-priv.h>

void _bsocial_ctx_free(BSocialReferenceable *r) {
	BSocialCtx* ctx;
	
	ctx = BSOCIAL_CTX(r);
	_bsocial_urls_free_contents(&ctx->urls);
	ctx->client->vtable.free(ctx->client);
	free(ctx);
}

BSocialCtx *bsocial_ctx_new(BSocialHTTPClient *(*httpclient_create)(void), BSocialError *err_ret) {
	BSocialCtx* ctx;
	char *proof;
	
	ctx = NULL;
	if (!httpclient_create) {
		_BSOCIAL_ERROR_SET_RET(err_ret, BSOCIAL_ERROR_INVALID_PARAM);
		_BSOCIAL_RET_ERROR(ctx);		
	}
	
	ctx = malloc(sizeof(BSocialCtx));
	if (!ctx) {
		_BSOCIAL_ERROR_SET_RET(err_ret, BSOCIAL_ERROR_ALLOC_FAILED);
		_BSOCIAL_RET_ERROR(ctx);
	}
	
	_bsocial_referenceable_init(BSOCIAL_REFERENCEABLE(ctx), _bsocial_ctx_free);
	
	ctx->client = httpclient_create();
	if (!ctx->client) {
		_BSOCIAL_ERROR_SET_RET(err_ret, BSOCIAL_ERROR_HTTP_CLIENT_CREATION_FAILED);
		_BSOCIAL_RET_ERROR(ctx);
	}
	
	proof = NULL;
	proof = ctx->client->vtable.get_contents(ctx->client, "example.com");
	printf("PROOF THAT THE CLIENT WORKS: %s\n", proof);
	ctx->client->vtable.free_contents(ctx->client, proof);
	
	_bsocial_urls_init(&ctx->urls, BSOCIAL_TRUE);

	ctx->token = NULL;
	
	_BSOCIAL_ERROR_SET_RET(err_ret, BSOCIAL_ERROR_NONE);	
	return ctx;
}
