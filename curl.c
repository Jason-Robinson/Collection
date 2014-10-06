#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include<stdlib.h>

struct curl_httppost *post = NULL; 
struct curl_httppost *last = NULL;
struct string
{
  char *ptr;
  size_t len;
};

char* collectFiles(char* url,char cor[],char sec[],char key[]);
size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s);
void init_string(struct string *s);
int filename();

int fileName(){
	char *url = "https://babbage.cs.missouri.edu/~cs4320s14grp10/swe-sp14gj/swe-sp14gJ/collection/collectAssignments.php";
	char course[10];
	char section[3];
	char assignment[10];
	char *file;
	char fileName[25]  ="unzip -j ";
	char fileName1[15]  ="unzip -j ";
	char remove[25] = "rm ";
	
	printf("Select course: ");
	scanf("%s", course);
	printf("Select section: ");
	scanf("%s", section);
	printf("Select assignment: ");
	scanf("%s", assignment);
	
	system("mkdir assignment_files");
	chdir("assignment_files");
	
	file = collectFiles(url,course,section, assignment);
	
	strcat(fileName, file);
	system(fileName);
	
	
	
	system(fileName);
	
	
	
	strcat(remove, file);
	system(remove);
	
	
	chdir("..");
	system(remove);
	return 0;
}
char* collectFiles(char* url,char cor[],char sec[],char key[])
{ 	
	CURLcode res;
	curl_global_init(CURL_GLOBAL_ALL); 
	CURL *easy_handle = curl_easy_init();
	struct string s;
    init_string(&s);
	
	curl_formadd(&post, &last, CURLFORM_COPYNAME, "course", CURLFORM_COPYCONTENTS, cor, CURLFORM_END);
	curl_formadd(&post, &last, CURLFORM_COPYNAME, "section", CURLFORM_COPYCONTENTS, sec, CURLFORM_END);
	curl_formadd(&post, &last, CURLFORM_COPYNAME, "assignmentkey", CURLFORM_COPYCONTENTS, key, CURLFORM_END);
	   
	curl_easy_setopt(easy_handle, CURLOPT_URL, url);
	curl_easy_setopt(easy_handle, CURLOPT_HTTPPOST, post);
	curl_easy_setopt(easy_handle, CURLOPT_WRITEFUNCTION, writefunc);
	curl_easy_setopt(easy_handle, CURLOPT_WRITEDATA, &s);
	res=curl_easy_perform(easy_handle);
	curl_formfree(post);
	char*  first = "wget http://babbage.cs.missouri.edu/~cs4320s14grp10/swe-sp14gj/swe-sp14gJ/collection/";
	char* command = (char *) malloc(1+strlen(first)+strlen(s.ptr));
	strcpy(command, first);
	strcat(command, s.ptr);
	system(command);
	//printf("%s\n", s.ptr);
    
	curl_easy_cleanup(easy_handle);
    curl_global_cleanup();
    return s.ptr;

	}
	
void init_string(struct string *s) {
	s->len = 0;
	s->ptr = malloc(s->len+1);
	if (s->ptr == NULL)
	{
		fprintf(stderr, "malloc() failed\n");
		exit(EXIT_FAILURE);
	}
	s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
	size_t new_len = s->len + size*nmemb;
	s->ptr = realloc(s->ptr, new_len+1);
	if (s->ptr == NULL) 
	{
		fprintf(stderr, "realloc() failed\n");
		exit(EXIT_FAILURE);
	}
	memcpy(s->ptr+s->len, ptr, size*nmemb);
	s->ptr[new_len] = '\0';
	s->len = new_len;

	return size*nmemb;
}
