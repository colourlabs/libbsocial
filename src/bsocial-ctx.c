#include <stdlib.h>
#include <curl/curl.h>
#include <bsocial-types.h>
#include <bsocial-ctx.h>
#define _BSOCIAL_RET_ERROR(x) if (x) { free(x); } return NULL 

void _bsocial_ctx_free(BSocialReferenceable *r) {
	BSocialCtx* ctx;
	
	ctx = BSOCIAL_CTX(r);
	curl_easy_cleanup(ctx->curl_ctx);
	free(ctx);
}

BSocialCtx *bsocial_ctx_new(BSocialError *err_ret) {
	BSocialCtx* ctx;
	
	ctx = malloc(sizeof(BSocialCtx));
	if (!ctx) {
		_BSOCIAL_ERROR_SET_RET(err_ret, BSOCIAL_ERROR_ALLOC_FAILED);
		_BSOCIAL_RET_ERROR(ctx);
	}
	
	_bsocial_referenceable_init(BSOCIAL_REFERENCEABLE(ctx), _bsocial_ctx_free);
	
	ctx->curl_ctx = curl_easy_init();
	if (!ctx->curl_ctx) {
		_BSOCIAL_ERROR_SET_RET(err_ret, BSOCIAL_ERROR_UNABLE_TO_CREATE_HTTP_CLIENT);
		_BSOCIAL_RET_ERROR(ctx);
	}

	ctx->token = NULL;
	
	_BSOCIAL_ERROR_SET_RET(err_ret, BSOCIAL_ERROR_NONE);	
	return ctx;
}
