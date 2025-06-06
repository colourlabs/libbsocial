#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <bsocial-types.h>
#include <bsocial-url-priv.h>

void _bsocial_urls_init(_BSocialURLs *urls, BSocialBool init_base) {
	if (init_base) {
		urls->base = _BSOCIAL_URL_DEFAULT_BASE;
		urls->base_free = NULL;
		urls->base_size = strlen(urls->base);
	}
	
	urls->auth_login = malloc(urls->base_size+strlen(_BSOCIAL_URL_API_AUTH_LOGIN)+1);
	strcpy(urls->auth_login, urls->base);
	strcat(urls->auth_login, urls->base);
}

void _bsocial_urls_free_contents(_BSocialURLs *urls) {
	if (urls->base_free) {
		urls->base_free(urls->base);
	}
	
	free(urls->auth_login);
}
