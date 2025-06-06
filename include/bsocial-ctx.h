#include <bsocial-export.h>
#include <bsocial-types.h>
#include <bsocial-httpclient.h>

#ifndef BSOCIAL_CTX_H
#define BSOCIAL_CTX_H

typedef struct _BSocialCtx BSocialCtx;
#define BSOCIAL_CTX(x) ((BSocialCtx*)x)
BSOCIAL_EXPORT BSocialCtx *bsocial_ctx_new(BSocialHTTPClient *(*httpclient_create)(void), BSocialError *err_ret);
BSOCIAL_EXPORT BSocialError bsocial_ctx_login(BSocialCtx *ctx, char *username, char *pwd);

#endif /* BSOCIAL_CTX_H */
