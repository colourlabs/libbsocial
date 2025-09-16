#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bsocial.h>
#include <bsocial-curl.h>
#include <bsocial-jansson.h>

int main(int argc, char *argv[])  { 
	BSocialCtx *ctx;
	BSocialError err;
	
	ctx = bsocial_ctx_new(bsocial_curl_http_client_new, bsocial_jansson_json_parser_new, &err);
	puts(bsocial_error_message(err));
	puts(bsocial_error_message(bsocial_ctx_login(ctx, NULL, NULL)));
	bsocial_referenceable_unref(BSOCIAL_REFERENCEABLE(ctx));
	
	return 0;
}


