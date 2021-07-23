/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"





/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @return int: Standard putput indicates errors
  */
int main(int argc, char **argv) {
  // socket 
  int sockfd;
  // counter of received bytes
  int n;
  // error number
  int _status = 1;
  // buffer to store the date
  char recvline[MAXLINE + 1];
  // server info 
  struct sockaddr_in servaddr;

  if (argc != 2)
    err_quit("usage: %s <IPaddress>", argv[0]);

  // define socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sockfd < 0) {
    err_sys("socket error");
    exit(1);
  }

  // zero the struct 
  bzero(&servaddr, sizeof(servaddr));
  
  // define protocol family
  servaddr.sin_family = AF_INET;
  // define protocol port (host to network short)
  servaddr.sin_port   = htons(SRV_PROTO);	/* daytime server */
  
  // (presentation to numeric)
  _status = inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

  if (_status <= 0) {
    err_quit("inet_pton error for %s", argv[1]);
    exit(1);
  }

  // connect to server
  _status = connect(sockfd, (SA*)&servaddr, sizeof(servaddr));

  if (_status < 0) {
    err_sys("connect error");
    exit(1);
  }

  // read the stream until a null comes
  while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
    recvline[n] = 0;	/* null terminate */
    if (fputs(recvline, stdout) == EOF) {
      err_sys("fputs error");
      exit(1);
    }
  }
  
  // exit with error if the stread is empty
  if (n < 0) {
    err_sys("read error");
    exit(1);
  }

  exit(0);
}
