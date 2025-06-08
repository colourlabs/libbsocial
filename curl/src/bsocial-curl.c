#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <bsocial.h>
#include <bsocial-curl.h>
#include <bsocial-types-priv.h>

typedef struct {
	BSocialHTTPClient _parent;

	CURL *curl;
} BSocialCurlHTTPClient;

typedef struct {
	char *str;
	size_t sz;
} BSocialCurlHTTPClientStr;

void _bsocial_curl_httpclient_free(BSocialHTTPClient *client) {
	BSocialCurlHTTPClient *cclient;

	cclient = (BSocialCurlHTTPClient *)client;
	curl_easy_cleanup(cclient->curl);
	free(cclient);
}

size_t _bsocial_curl_httpclient_get_contents_write(void *ptr, size_t size, size_t nmemb, void *udata) {
	BSocialCurlHTTPClientStr *str;
	size_t new_sz;
	size_t coming_sz;
	
	str = (BSocialCurlHTTPClientStr *)udata;
	coming_sz = size * nmemb;
	new_sz = str->sz + coming_sz;
	str->str = realloc(str->str, new_sz + 1);
	if (!str->str) {
		return 0;
	}
	memcpy(str->str+str->sz, ptr, coming_sz);
	str->str[new_sz] = '\0';
	str->sz = new_sz;

	return coming_sz;
}

void _bsocial_curl_httpclient_free_contents(BSocialHTTPClient *client, char *contents) {
	free(contents);
}

char *_bsocial_curl_httpclient_get_contents(BSocialHTTPClient *client, char *url) {
	BSocialCurlHTTPClient *cclient;
	BSocialCurlHTTPClientStr str;
	CURLcode res;
		
	cclient = (BSocialCurlHTTPClient *)client;
	str.sz = 0;
	str.str = malloc(str.sz + 1);
	if (!str.str) {
		return NULL;
	} else {
		str.str[0] = '\0';
	}
	
    curl_easy_setopt(cclient->curl, CURLOPT_URL, url);
    curl_easy_setopt(cclient->curl, CURLOPT_WRITEFUNCTION, _bsocial_curl_httpclient_get_contents_write);
    curl_easy_setopt(cclient->curl, CURLOPT_WRITEDATA, &str);
    res = curl_easy_perform(cclient->curl);	
	if (res != CURLE_OK) {
		return NULL;
	}
	
	return str.str;
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
	pclient->vtable.get_contents = _bsocial_curl_httpclient_get_contents;
	pclient->vtable.free_contents = _bsocial_curl_httpclient_free_contents;
	pclient->vtable.free = _bsocial_curl_httpclient_free;	
	
	return pclient;
}
