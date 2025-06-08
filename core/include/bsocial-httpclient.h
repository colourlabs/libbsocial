#include <bsocial-export.h>
#include <bsocial-types.h>

#ifndef BSOCIAL_HTTPCLIENT_H
#define BSOCIAL_HTTPCLIENT_H

typedef struct _BSocialHTTPClient {
	char *type;
	
	struct _BSocialHTTPClientVTable {
		char *(*get_contents)(struct _BSocialHTTPClient *client, char *url);
		void (*free_contents)(struct _BSocialHTTPClient *client, char *contents);
		void *_for_expansion1;
		void *_for_expansion2;
		void *_for_expansion3;
		void *_for_expansion4;
		void *_for_expansion5;
		void *_for_expansion6;
		void *_for_expansion7;
		void *_for_expansion8;
		void *_for_expansion9;
		void *_for_expansion10;
		void (*free)(struct _BSocialHTTPClient *client);
	} vtable;
} BSocialHTTPClient;

#endif /* BSOCIAL_HTTPCLIENT_H */
