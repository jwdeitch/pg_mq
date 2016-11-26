#include <stdio.h>
#include <curl/curl.h>
#include "fmgr.h"
#include "postgres.h"
#include "postgres_ext.h"

PG_MODULE_MAGIC;

typedef struct {
    int32 length;
    char data[FLEXIBLE_ARRAY_MEMBER];
} text;

PG_FUNCTION_INFO_V1(test_text);

Datum
test_text(PG_FUNCTION_ARGS) {
    PG_RETURN_TEXT_P("test");
}

bool send_http_message(char *URL, char *data) {
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://whois.rsa.pub/");

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        }

        /* always cleanup */
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return 0;
}