/*
**  mod_example.c -- Apache sample example module
**  [Autogenerated via ``apxs -n example -g'']
**
**  To play with this sample module first compile it into a
**  DSO file and install it into Apache's modules directory
**  by running:
**
**    $ apxs -c -i mod_example.c
**
**  Then activate it in Apache's apache2.conf file for instance
**  for the URL /example in as follows:
**
**    #   apache2.conf
**    LoadModule example_module modules/mod_example.so
**    <Location /example>
**    SetHandler example
**    </Location>
**
**  Then after restarting Apache via
**
**    $ apachectl restart
**
**  you immediately can request the URL /example and watch for the
**  output of this module. This can be achieved for instance via:
**
**    $ lynx -mime_header http://localhost/example
**
**  The output should be similar to the following one:
**
**    HTTP/1.1 200 OK
**    Date: Tue, 31 Mar 1998 14:42:22 GMT
**    Server: Apache/1.3.4 (Unix)
**    Connection: close
**    Content-Type: text/html
**
**    The sample page from mod_example.c
*/

#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"
#define MAX_LEN 100

#include <unistd.h>
#include <linux/limits.h>


/* The sample content handler */
static int example_handler(request_rec *r)
{
    if (strcmp(r->handler, "example")) {
        return DECLINED;
    }
    r->content_type = "text/html";

   if( !strcmp(r->method,"POST")|| !strcmp(r->method,"GET")){
       //ap_rputs("You used GET or POST method! <br/>",r);
       FILE *pFile = NULL;

       pFile = fopen( "/home/handfriendship/Desktop/example/test.txt", "r" );

       //ap_rputs("You used GET or POST method2! <br/>", r);

       if( pFile != NULL )
       {
            //ap_rputs("You used GET or POST method3! <br/>",r);

           char strTemp[255];
           char *pStr;
           char *pstrstr = NULL;
           int strcmp_var = 1;
           int safe_flag = 0;
            //ap_rputs("You used GET or POST method1! <br/>",r);


           while( !feof( pFile ) )
           {

                   pStr = fgets( strTemp, sizeof(strTemp), pFile );
                   //strcmp_var = strcmp(r->args, strTemp);
                   strTemp[strlen(strTemp) - 1] = '\0';
                   pstrstr=strstr(r->args, strTemp);
                   //ap_rprintf(r,"file content : %s\n",strTemp);
                   //ap_rputs("You used GET or POST method! <br/>", pStr);
                   if(pstrstr != NULL){
                       //ap_rputs("You used GET or POST methodtesttest! <br/>",r);
                       //ap_rprintf(r,"bad request : %s\n",r->args);
                       safe_flag = 0;
                       //printf("woojung=n");

                       //ap_rputs("xss  \n", r);
                       return HTTP_NOT_FOUND;
                   } else {
                       //ap_rprintf(r,"no maching string :%s",r->args);
                        safe_flag = 1;

                   }

                   //printf( "%s", strTemp );
                   //printf( "%s", pStr );
                   //ap_rputs("you did not use Post or Get :(<br/>", pStr);
                   //ap_rputs("You used GET or POST method! <br/>",r);

           }
           if(safe_flag){
               ap_rputs("Welcome :)\n We are cyber Warrior !\n", r);
           }


           fclose( pFile );
       }
       else
       {
               //에러 처리
       }

   }
   else{
       ap_rputs("you did not use Post or Get :(<br/>",r);
   }
   if(r->args){
       ap_rprintf(r,"your query string was :%s\n",r->args);
   }

   //FILE *fp;

   //fp = fopen("test.txt", "r");
   //char str[MAX_LEN];
   //fgets(str,MAX_LEN,fp);
   //printf("%s",str);
   //ap_rputs("teest %s :(<br/>",(request_rec*)str);
   //ap_rprintf(r,"your query string was :%s",str);



   return OK;
}

static void example_register_hooks(apr_pool_t *p)
{
    ap_hook_handler(example_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA example_module = {
    STANDARD20_MODULE_STUFF,
    NULL,                  /* create per-dir    config structures */
    NULL,                  /* merge  per-dir    config structures */
    NULL,                  /* create per-server config structures */
    NULL,                  /* merge  per-server config structures */
    NULL,                  /* table of config file commands       */
    example_register_hooks  /* register hooks                      */
};

