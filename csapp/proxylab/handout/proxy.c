/*
 * proxy.c - a simple proxy server to redirect the GET request for any input
 *     connnects.
 */

 #include "csapp.h"

/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";

/* Local functions */
void handle_request(int connfd);
void clienterror(int fd, char *cause, char *errnum,
   char *shortmsg, char *longmsg);


int main(int argc, char **argv)
{
  int listenfd, connfd;
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;  // sockaddr_storage extends sockaddr/SA
  char client_hostname[MAXLINE], client_port[MAXLINE];

  /* Check that the port argument exist */
  if (argc < 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
  }

  printf("%s", user_agent_hdr);

  /* Open a listenfd by the first argumetn as a port */
  listenfd = Open_listenfd(argv[1]);
  printf("[proxy] Successfully open a listenfd.\n");

  /* Iteratively handle reuqest. */
  // TODO: make it concurrent.
  while (1) {
    clientlen = sizeof(struct sockaddr_storage); // initialized to maximum

    /* Wating for a incoming connection. */
    connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

    /* If connection success, report it first */
    Getnameinfo((SA *)&clientaddr, clientlen, client_hostname, MAXLINE,
                client_port, MAXLINE, 0);
    printf("[proxy] Connected to (%s, %s)\n", client_hostname, client_port);

    /* TODO: Handle the request */
    handle_request(connfd);

    /* Close the connection after handeling */
    Close(connfd);
  }

  exit(0);
}


/*
 * handle_request - Handle the transaction.
 */
void handle_request(int fd)
{
  rio_t rio;
  char buf[MAXLINE], method[MAXLINE], url[MAXLINE], version[MAXLINE];

  /* Read and parse the Header.
   * Return a error message if the request is not supported. */
  Rio_readinitb(&rio, fd);
  if (!Rio_readlineb(&rio, buf, MAXLINE)) {
    printf("Not request header!\n");
    return;
  } else {
    printf("[proxy] Read request: \n%s", buf);
  }
  sscanf(buf, "%s %s %s", method, url, version);
  printf("[proxy] Parsed as method: %s; url: %s; ver: %s;\n", method, url, version);
  if (strcasecmp(method, "GET")) {
    clienterror(fd, method, "501", "Not Implemented",
                "Proxy does not implement this method");
    return;
  }

  /* 

  return ;
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
