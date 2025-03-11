#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
int main(){
        int socket_fd=socket(AF_INET,SOCK_STREAM,0);
        if(socket_fd==-1){
                printf("Error socket!\n");
                return -1;
        }
        struct sockaddr_in client;
        client.sin_family=AF_INET;
        client.sin_port=htons(1234);
        client.sin_addr.s_addr= inet_addr("172.30.243.22");
        int connect_res= connect(socket_fd,(const struct sockaddr*) &client, sizeof(client));
        if(connect_res==-1){
                printf("Couldn't connect to the server!\n");
                return -2;
        }
        char buffer[100];
        int recv_res=recv(socket_fd,buffer, 100,0);
        if(recv_res==-1){
                printf("Couldn't recieve!\n");
                return -3;
        }
        printf("Received message: %s\n",buffer);
        char response_buffer[100]="Anamaria\0";
        int send_res=send(socket_fd, response_buffer, strlen(response_buffer)+1, 0);
        if(send_res==-1){
                printf("Couldn't send message!\n");
                return -4;
        }
        return 0;
}