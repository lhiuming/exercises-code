/*
 * proxy.c - a simple proxy server to redirect the GET request for any input
 *     connnects.
 */

 #include "csapp.h"

/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

/* You won't lose style points for including this long line in your code */
//static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";

/* Local functions */
void *thread(void *vargp);
void handle_request(int connfd);
int convert_request(int fd, char *ret, char *hn, char *port);
void parse_url(char *url, char *port, char *dir);
int fetch_and_serve(int connfd, char *request, char *hostname, char *port);
void clienterror(int fd, char *cause, char *errnum, char *shortmsg,
  char *longmsg);


int main(int argc, char **argv)
{
  int listenfd, *connfdp;
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;  // sockaddr_storage extends sockaddr/SA
  char client_hostname[MAXLINE], client_port[MAXLINE];
  pthread_t tid;

  /* Check that the port argument exist */
  if (argc < 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
  }

  /* Open a listenfd by the first argumetn as a port */
  listenfd = Open_listenfd(argv[1]);

  /* Iteratively handle reuqest. */
  // TODO: make it concurrent.
  while (1) {
    /* Wating for a incoming connection. */
    clientlen = sizeof(struct sockaddr_storage); // initialized to maximum
    connfdp = Malloc(sizeof(int));
    *connfdp = Accept(listenfd, (SA *)&clientaddr, &clientlen);

    /* If connection success, grap the information  */
    Getnameinfo((SA *)&clientaddr, clientlen, client_hostname, MAXLINE,
                client_port, MAXLINE, 0);
    printf("[proxy] Connected to (%s, %s)\n", client_hostname, client_port);

    /* Handle the request by a new thread */
    Pthread_create(&tid, NULL, thread, connfdp);
    printf("[proxy] Thread %li is handling.\n", (long int)tid);
  }

  exit(0);
}

/*
 * thread - Wrapper the handle_request into a thread task.
 */
void *thread(void *vargp) {
  pthread_t selfid = pthread_self();
  int connfd = *((int *)vargp);

  Pthread_detach(selfid); // main thread dont join this
  Free(vargp);  // is allocated in main trhead

  /* Call the handler */
  handle_request(connfd);

  /* Close the connection after handeling */
  Close(connfd);  // thread responsibility
  printf("[proxy] Disconnect.\n");

  return NULL;
}



/*
 * handle_request - Handle the transaction.
 */
void handle_request(int fd)
{
  char request[MAXBUF];
  char hostname[MAXLINE], port[MAXLINE];

  /* Get a proxy header for the request */
  if (convert_request(fd, request, hostname, port))
    return;
  printf("[proxy] The converted request looks like: \n%s", request);

  /* Get the proxied content */
  if (fetch_and_serve(fd, request, hostname, port))
    return;
  printf("[proxy] Served the request finished.\n");

  return ;
}


/*
 * convert_request - Read the request and convert it to a proxied request.
 */
int convert_request(int fd, char *ret, char *host, char *port)
{
  rio_t rio;
  char buf[MAXLINE], method[MAXLINE], version[MAXLINE];
  char dir[MAXLINE];

  /* Read and parse the request header line */
  printf("[proxy] Reading request header ... "); fflush(0);
  Rio_readinitb(&rio, fd);
  if (!Rio_readlineb(&rio, buf, MAXLINE)) {
    printf("Not request header!\n");
    return -1;
  }
  printf(" got: %s\n", buf);
  sscanf(buf, "%s %s %s", method, host, version);

  /* Parse the url into: host [: port] [dir] */
  parse_url(host, port, dir);
  if (!strcmp(port, "")) sprintf(port, "80"); // default port : 80
  printf("[proxy] Parsed url: %s, %s, %s\n", host, port, dir);

  /* Return an error message if the request is not supported. */
  if (strcasecmp(method, "GET")) {
    clienterror(fd, method, "501", "Not Implemented",
                "Proxy does not implement this method");
    return -1;
  }
  if (strcasecmp(version, "HTTP/1.0") && strcasecmp(version, "HTTP/1.1")) {
    clienterror(fd, version, "501", "Invalid Protocol",
                "Proxy does not supported this protocol");
    return -1;
  }

  /* Contruct the to-be-sent request */
  sprintf(ret, "GET %s HTTP/1.0\n", dir);  // GET header lines
  sprintf(ret, "%sHost: %s\n", ret, host);  // Host line
  sprintf(ret, "%sConnection: close\n", ret);        // a requirement
  sprintf(ret, "%sProxy-Connection: close\n", ret);  // another requirement

  /* Append the rest of accepted request into the return header */
  Rio_readlineb(&rio, buf, MAXLINE);
  while (strcmp(buf, "\r\n")) {
    sprintf(ret, "%s%s", ret, buf);
    Rio_readlineb(&rio, buf, MAXLINE);
  }
  sprintf(ret, "%s\r\n", ret);  // dont forget the requent-end symbol "\r\n"

  return 0;
}


/*
 * parse_url - Parse the url into two parts: host, port (opional), and
 *     directory (optional);
 */
void parse_url(char *url, char *port,  char *dir)
{
  char dump[MAXLINE]; // placeholder

  /* clean port and dir before using */
  port[0] = '\0';
  dir[0] = '\0';

  /* Get the host name first, and store it at url.
   * The rest is put at dir temporarily */
  sscanf(url, "http%[s:]//%[^:/]%s", dump, url, dir);

  /* Fill port if there is a port.
   * The rest is put in dir, including potential '/' */
  if (dir[0] == ':') {
    if (sscanf(dir, ":%[^/]%s", port, dir) == 1)
      dir[0] = '\0';  // if no dir resd, clean it.
  } else {
    port[0] = '\0';
  }
}


/*
 * fetch_web - Get the wen contetn from target server.
 */
int fetch_and_serve(int connfd, char *request, char *hostname, char *port)
{
  rio_t rio;
  int clientfd;
  char buf[MAXLINE];

  /* Connect to the server */
  printf("[proxy] Fetching from (%s, %s) ... \n", hostname, port);
  clientfd = Open_clientfd(hostname, port);

  /* Write the request */
  printf("[proxy] Writing request ... \n");
  Rio_writen(clientfd, request, MAXLINE);

  /* read the fetched content into the same request buffer */
  printf("[proxy] Reading and feeding response ... \n");
  Rio_readinitb(&rio, clientfd);
  Rio_readlineb(&rio, buf, MAXLINE);
  sprintf(request, "%s", buf); // this will overwrite request buffer
  while (strcmp(buf, "\r\n")) {
    Rio_writen(connfd, buf, MAXLINE);
    Rio_readlineb(&rio, buf, MAXLINE);
  }
  Rio_writen(connfd, buf, MAXLINE); // append the ending symbol;

  return 0;
}


/*
 * clienterror - returns an error message to the client
 * This code is copied from tiny.c
 */
void clienterror(int fd, char *cause, char *errnum,
		 char *shortmsg, char *longmsg)
{
    char buf[MAXLINE], body[MAXBUF];

    /* Build the HTTP response body */
    sprintf(body, "<html><title>Proxy Error</title>");
    sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
    sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
    sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
    sprintf(body, "%s<hr><em>My Proxy</em>\r\n", body);

    /* Print the HTTP response */
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
    Rio_writen(fd, buf, strlen(buf));
    Rio_writen(fd, body, strlen(body));
}
