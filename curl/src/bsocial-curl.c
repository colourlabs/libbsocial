#include <stdlib.h>
#include <curl/curl.h>
#include <bsocial.h>
#include <bsocial-curl.h>
#include <bsocial-types-priv.h>

typedef struct {
	BSocialHTTPClient _parent;

	CURL *curl;
} BSocialCurlHTTPClient;

void _bsocial_curl_httpclient_free(BSocialHTTPClient *client) {
	BSocialCurlHTTPClient *cclient;

	cclient = (BSocialCurlHTTPClient *)client;
	curl_easy_cleanup(cclient->curl);
	free(cclient);
}

BSocialHTTPClient *bsocial_curl_httpclient_new(void) {
	BSocialCurlHTTPClient *client;
	BSocialHTTPClient *pclient;

	client = malloc(sizeof(BSocialCurlHTTPClient));
	if (!client) {
		_BSOCIAL_RET_ERROR(client);		
	}
	
	client->curl = curl_easy_init();
	if (!client->curl) {
		_BSOCIAL_RET_ERROR(client);		
	}
	
	pclient = (BSocialHTTPClient *)client;
	pclient->type = "cURL";
	pclient->vtable.get_contents = NULL;
	pclient->vtable.free = _bsocial_curl_httpclient_free;	
	
	return pclient;
}
