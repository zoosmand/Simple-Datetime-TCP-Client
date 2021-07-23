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
  int socketDateTime = 0;
  // counter of received bytes
  int byteCounter = 0;
  // counter of received packets
  int packetCounter = 0;
  // buffer to store the date
  char receivedLine[MAXLINE + 1];
  // server attributes
  struct sockaddr_in serverAddr;

  if (argc != 2) err_quit("usage: %s <IPaddress>", argv[0]);

  // define socket
  socketDateTime = Socket(AF_INET, SOCK_STREAM, 0);
  // zero the struct 
  bzero(&serverAddr, sizeof(serverAddr));  
  // define protocol family
  serverAddr.sin_family = AF_INET;
  // define protocol port (host to network short)
  serverAddr.sin_port = htons(SRV_PROTO);	/* daytime server */
  
  // (presentation to numeric)
  Inet_pton(AF_INET, argv[1], &serverAddr.sin_addr);

  // connect to server
  Connect(socketDateTime, (SA*)&serverAddr, sizeof(serverAddr));

  // read the stream until a null comes
  while ((byteCounter = read(socketDateTime, receivedLine, MAXLINE)) > 0) {
    packetCounter++;
  }
  
  // exit with error if the stread is empty
  if (byteCounter < 0) err_sys("No bytes received");

  printf("%sreceived: %d\n\n", receivedLine, packetCounter);
  exit(0);
}
