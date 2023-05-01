
#include<iostream>
#include <sys/types.h>   // defines types (like size_t)
#include <sys/socket.h>  // defines socket class
#include <netinet/in.h>  // defines port numbers for (internet) sockets, some address structures, and constants
#include <time.h>        // used for random number generation
#include <string.h> // using this to convert random port integer to string
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <stdlib.h>

#define MAX_DIGITS 10

using namespace std;

int main(int argc, char *argv[]){
  
  int port = atoi(argv[1]);
  struct sockaddr_in server;
  struct sockaddr_in client;
  int mysocket = 0;

  int i = 0;
  socklen_t slen = sizeof(server);
  socklen_t clen = sizeof(client);
  char payload[512];





  if ((mysocket=socket(AF_INET, SOCK_DGRAM, 0))==-1)
    cout << "Error in socket creation.\n";
  
  memset((char *) &server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(mysocket, (struct sockaddr *)&server, sizeof(server)) == -1)
    cout << "Error in binding.\n";

int acksent = 1;
  ofstream myfile;
  myfile.open ("blah.txt");
  while (acksent == 1) {

    char ack[] = "FFFF";
    acksent ==0;
    if (recvfrom(mysocket, payload, 512, 0, (struct sockaddr *)&client, &clen)==-1) {

      cout << "Failed to receive.\n";
      acksent = 0; 
    }
    else{
    myfile << payload;
   
    //////write payload to file
    cout << "Received data: " << payload << endl;
    
    for ( i=0; i<4; i++) {
         ack[i] = payload[i];
    if(islower(payload[i])) {
             ack[i] = toupper(ack[i]);
         }
    
   if(payload[0] == 0) {
       cout << "EMPTY";
   }
    
    sendto(mysocket, ack, 512, 0, (struct sockaddr *)&client, clen);
    acksent = 1;
    }
  }
  }
  char wack[]="Got all that data, thanks?";
  if (sendto(mysocket, wack, 64, 0, (struct sockaddr *)&client, clen)==-1){
   cout << "Error in sendto function.\n";
  }
  
  myfile.close();
  close(mysocket);   
  return 0;
}


