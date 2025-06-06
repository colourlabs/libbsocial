#include <bsocial-types.h>

#ifndef BSOCIAL_URL_PRIV_H
#define BSOCIAL_URL_PRIV_H

#define _BSOCIAL_URL_DEFAULT_BASE "https://bsapi.colourlabs.net/"
#define _BSOCIAL_URL_API_AUTH_LOGIN "api/auth/login"

typedef struct {
	char *base;
	size_t base_size;
	void (*base_free)(void *p);
	
	char *auth_login;
} _BSocialURLs;

void _bsocial_urls_init(_BSocialURLs *urls, BSocialBool init_base);
void _bsocial_urls_free_contents(_BSocialURLs *urlse);

#endif /* BSOCIAL_CTX_H */
