#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
        int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

        if(socket_fd == -1)
        {
                printf("error creating socket\n");
                return -1;
        }

        //only for sender
        //tell to send to broadcast address

        //int broadcast = 1;
        //int result_setsockopt = setsockopt(socket_fd,
        //              SOL_SOCKET,
        //              SO_BROADCAST,
        //              &broadcast,
        //              sizeof(broadcast));

        /*if(result_setsockopt == -1)
        {
                printf("setsockopt error\n");
                return -2;
        }*/

        struct sockaddr_in recv_addr;
        recv_addr.sin_family = AF_INET;
        recv_addr.sin_port = htons(1234);
        recv_addr.sin_addr.s_addr = INADDR_ANY;

        int result_bind = bind(socket_fd, (const struct sockaddr*) &recv_addr, sizeof(recv_addr));

        if(result_bind == -1)
        {
                printf("couldn't bind\n");
                return -3;
        }

        struct sockaddr_in sender_addr;
        char response[100];
        socklen_t sender_addr_len;

        //last 2 are receiving info
        int result_recvfrom = recvfrom(socket_fd, response, 100, 0, (struct sockaddr *) &sender_addr, &sender_addr_len);

        if(result_recvfrom == -1)
        {
                printf("error when doing recvfrom\n");
                return -4;
        }
        printf("%s\n", response);

        return 0;
}

