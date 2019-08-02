#include <unistd.h>
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <arpa/inet.h>
#include <sys/socket.h> 

#define MAX 20 
#define PORT 8080 
#define SA struct sockaddr 

void funcClient(int sockfd) 
{ 
	char buff[MAX]; 
	int n; 
	//for (;;) { 
		bzero(buff, sizeof(buff)); 
		printf("Enter the string : "); 
		n = 0; 
		//while ((buff[n++] = getchar()) != '\n') 
			//;
			strcpy(buff, "is a shadow"); 
			printf("testttttttttttt\n");
		//write(sockfd, buff, sizeof(buff));
		send(sockfd, buff, sizeof(buff), 0);

		perror("there an error occur\n");

		bzero(buff, sizeof(buff)); 
		//read(sockfd, buff, sizeof(buff));
		recv(sockfd, buff, sizeof(buff), MSG_WAITALL); 
		printf("From Server : %s", buff); 
		/* if ((strncmp(buff, "exit", 4)) == 0) { 
			printf("Client Exit...\n"); 
			break; 
		} */
	//} 
} 

int startClient() 
{ 
	int sockfd, connfd; 
	struct sockaddr_in servaddr, cli; 

	// socket create and varification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 

	// connect the client socket to server socket 
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("connection with the server failed...\n"); 
		exit(0); 
	} 
	else
		printf("connected to the server..\n"); 

	// function for chat 
	//funcClient(sockfd); 

	// close the socket 
	//close(sockfd); 
	return sockfd;
} 