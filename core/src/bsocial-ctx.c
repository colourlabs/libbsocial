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

BSOCIAL_EXPORT BSocialCtx *bsocial_ctx_new(BSocialHTTPClient *(*httpclient_create)(void), BSocialJSONParser *(*jsonparser_create)(void), BSocialError *err_ret) {
	BSocialCtx* ctx;
	
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
	ctx->parser = jsonparser_create();
	if (!ctx->parser) {
		_BSOCIAL_ERROR_SET_RET(err_ret, BSOCIAL_ERROR_JSON_PARSER_CREATION_FAILED);
		_BSOCIAL_RET_ERROR(ctx);
	}	
	
	_bsocial_urls_init(&ctx->urls, BSOCIAL_TRUE);

	ctx->token = NULL;
	
	_BSOCIAL_ERROR_SET_RET(err_ret, BSOCIAL_ERROR_NONE);	
	return ctx;
}

BSocialError bsocial_ctx_login(BSocialCtx *ctx, char *username, char *pwd) {
	BSocialJSONObject *obj;
	BSocialJSONObject *strobj;
	
	obj = ctx->parser->vtable.parse_str(ctx->parser, "{\"name\":\"John\", \"age\":30, \"car\":null}");
	strobj = obj->vtable.get_object_of_key(obj, "name");
	puts(strobj->vtable.get_string_value(strobj));
	obj->vtable.free(obj);
}
