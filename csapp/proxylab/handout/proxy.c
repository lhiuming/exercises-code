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

    /* Close the connection after handeling */
    Cloase(clientfd);
  }

  exit(0);
}
