#include <curl/curl.h>

class CURLHelper {
  private:
	struct string {
		char * ptr;
		size_t len;
	};

	static void init_string(struct string *s) {
		s->len = 0;
		s->ptr = (char *) malloc(s->len + 1);
		if (s->ptr == NULL) {
			fprintf(stderr, "malloc() failed\n");
			exit(EXIT_FAILURE);
		}
		s->ptr[0] = '\0';
	}

	static size_t writefuncstr(const void *ptr, const size_t size, const size_t nmemb, struct string *s) {
		const size_t new_len = s->len + size * nmemb;
		s->ptr               = (char *) realloc(s->ptr, new_len + 1);
		if (s->ptr == NULL) {
			fprintf(stderr, "realloc() failed\n");
			exit(EXIT_FAILURE);
		}
		memcpy(s->ptr + s->len, ptr, size * nmemb);
		s->ptr[new_len] = '\0';
		s->len          = new_len;

		return size * nmemb;
	}

	static size_t writefuncfile(const void *ptr, const size_t size, const size_t nmemb, FILE *f) {
		size_t written = fwrite(ptr, size, nmemb, f);
		return written;
	}

  public:
	static char *GetUrlStringContents(const char *url) { // define function to return url contents as a string
		CURL *   curl = curl_easy_init();

		string   s;
		init_string(&s);

		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefuncstr);
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
			curl_easy_perform(curl);
			curl_easy_cleanup(curl);
		}

		char *   contents = (char *) malloc(s.len);
		strcpy(contents, s.ptr);

		free(s.ptr);

		return contents;
	}

	static void SaveUrlContents(const char *url, const char *file) { // define function to return url contents as a string
		CURL *  curl = curl_easy_init();
		FILE *  fp   = fopen(file, "wb");

		if (curl) {

			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefuncfile);
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
			curl_easy_perform(curl);

			/* always cleanup */
			curl_easy_cleanup(curl);
		}

		fclose(fp);
	}
};