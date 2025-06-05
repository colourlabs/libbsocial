#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bsocial.h>

int main(int argc, char *argv[])  { 
	BSocialCtx *ctx;
	BSocialError err;
	
	ctx = bsocial_ctx_new(&err);
	printf("error code is %d\n", err);
	bsocial_referenceable_unref(BSOCIAL_REFERENCEABLE(ctx));
	
	return 0;
}


