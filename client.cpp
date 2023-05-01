

#include <iostream>
#include <sys/types.h>   // defines types (like size_t)
#include <sys/socket.h>  // defines socket class
#include <netinet/in.h>  // defines port numbers for (internet) sockets, some address structures, and constants
#include <netdb.h> 
#include <iostream>
#include <fstream>
#include <arpa/inet.h>   // if you want to use inet_addr() function
#include <string.h>
#include <unistd.h>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]){
  char ack[512] = "";
  char templine[512] = "";
  
  string filename = argv[3];
  char payload[512]="123"; 

  char line[512];
 
  int port = atoi(argv[2]);
       char c;
       int templineSize = 0;
  struct hostent *s; 
  s = gethostbyname(argv[1]);

  struct sockaddr_in server;
  int mysocket = 0;
  socklen_t slen = sizeof(server);
  struct sockaddr_in client;
  socklen_t clen = sizeof(client);

  if ((mysocket=socket(AF_INET, SOCK_DGRAM, 0))==-1)
    cout << "Error in creating socket.\n";
    
  memset((char *) &server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  bcopy((char *)s->h_addr, 
	(char *)&server.sin_addr.s_addr,
	s->h_length);

        FILE* file = fopen(filename.c_str(), "r");
        int tmp = 1;
        while((c = fgetc(file)) != EOF){
              tmp = 1;
              templine[templineSize] = c;
              templineSize += 1;
              if((templineSize % 4) == 0) {
                 payload[0] = templine[0];
                 payload[1] = templine[1];
                 payload[2] = templine[2];
                 payload[3] = templine[3];
                 sendto(mysocket, payload, 512, 0, (struct sockaddr *)&server, slen);
}
                 while(tmp){
                      
                     if(( recvfrom(mysocket, ack, 512, 0, (struct sockaddr *)&server, &slen))!=-1){
                           tmp = 0;
                       
                    }
                      }
                 cout << ack << endl;
                  memset(templine, 0, templineSize);
                  templineSize = 0;
             }
       
       int tmp2 = 1;
       if(templineSize > 0) {
           y

           sendto(mysocket, templine, 8, 0, (struct sockaddr *)&server, slen);
           while(tmp2){
                  if((recvfrom(mysocket, ack, 512, 0, (struct sockaddr *)&server, &slen)) != -1) {
                   tmp2 = 0;
                  }
           }
           cout << ack;
           templineSize = 0;
       }
  
  recvfrom(mysocket, ack, 512, 0, (struct sockaddr *)&server, &slen); 
  cout << ack << endl;
  close(mysocket);
  return 0;
}
