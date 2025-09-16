#include <stdlib.h>
#include <stdio.h>
#include <bsocial-types.h>
#include <bsocial-types-priv.h>
#include <bsocial-url-priv.h>
#include <bsocial-http-client.h>
#include <bsocial-ctx.h>
#include <bsocial-ctx-priv.h>

void _bsocial_ctx_free(BSocialReferenceable *r) {
	BSocialCtx* ctx;
	
	ctx = BSOCIAL_CTX(r);
	_bsocial_urls_free_contents(&ctx->urls);
	ctx->client->vtable.free(ctx->client);
	free(ctx);
}

BSOCIAL_EXPORT BSocialCtx *bsocial_ctx_new(BSocialHTTPClient *(*http_client_create)(void), BSocialJSONParser *(*json_parser_create)(void), BSocialError *err_ret) {
	BSocialCtx *ctx;
	
	ctx = NULL;
	
	/* CHECK FOR VARIOUS INVALID PARAMETERS */
	if (!http_client_create) {
		_BSOCIAL_ERROR_SET_RET(err_ret, BSOCIAL_ERROR_INVALID_PARAM);
		_BSOCIAL_RET_ERROR(ctx);		
	}
	if (!json_parser_create) {
		_BSOCIAL_ERROR_SET_RET(err_ret, BSOCIAL_ERROR_INVALID_PARAM);
		_BSOCIAL_RET_ERROR(ctx);		
	}
	
	/* ALLOCATE STRUCT */
	ctx = malloc(sizeof(BSocialCtx));
	if (!ctx) {
		_BSOCIAL_ERROR_SET_RET(err_ret, BSOCIAL_ERROR_ALLOC_FAILED);
		_BSOCIAL_RET_ERROR(ctx);
	}
	
	/* INIT REFCOUNTING */
	_bsocial_referenceable_init(BSOCIAL_REFERENCEABLE(ctx), _bsocial_ctx_free);
	
	/* CREATE HTTP CLIENT */
	ctx->client = http_client_create();
	if (!ctx->client) {
		_BSOCIAL_ERROR_SET_RET(err_ret, BSOCIAL_ERROR_HTTP_CLIENT_CREATION_FAILED);
		_BSOCIAL_RET_ERROR(ctx);
	}
	
	/* CREATE JSON PARSER */
	ctx->parser = json_parser_create();
	if (!ctx->parser) {
		_BSOCIAL_ERROR_SET_RET(err_ret, BSOCIAL_ERROR_JSON_PARSER_CREATION_FAILED);
		_BSOCIAL_RET_ERROR(ctx);
	}	
	
	/* INIT URLS */
	_bsocial_urls_init(&ctx->urls, BSOCIAL_TRUE);

	/* INIT AUTH */
	ctx->token = NULL;
	
	/* SET ERROR TO NONE AND RETURN */
	_BSOCIAL_ERROR_SET_RET(err_ret, BSOCIAL_ERROR_NONE);	
	return ctx;
}

BSocialError bsocial_ctx_login(BSocialCtx *ctx, char *username, char *pwd) {
	BSocialJSONObject *obj;
	BSocialJSONObject *strobj;
	
	obj = bsocial_json_parser_parse_str(ctx->parser, "{\"name\":\"John\", \"age\":30, \"car\":null}");
	strobj = bsocial_json_object_get_object_of_key(obj, "name");
	puts(bsocial_json_object_get_string_value(strobj));
	bsocial_json_object_free(obj);
	
	
}
