#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct thread_worker_args {
        struct sockaddr_in client;
        int client_fd;
};

void * thread_routine(void* arg) {

        struct thread_worker_args arguments = *((struct thread_worker_args *) arg);
        struct sockaddr_in client = arguments.client;
        int client_fd = arguments.client_fd;

        printf("Client with ip:%s and port:%d has connected!\n",
                                inet_ntoa(client.sin_addr),
                                ntohs(client.sin_port));

        char buffer[100] = "Do you want VIP status???\nIf yes input your username!\n";
        int send_res = send(client_fd, buffer, strlen(buffer) + 1, 0);
        if(send_res == -1) {
                printf("Couldn't send message!\n");
                return NULL;
        }

                        char username[100];

                        int recv_res = recv(client_fd, username, 100, 0);
                        if(recv_res == -1) {
                                printf("Receive error!\n");
                                return NULL;
                        }

                        if(strcmp(username, "no") == 0) {
                                printf("User doesn't want VIP :((\n");
                        } else {
                        printf("User chose VIP name: %s\n", username);
                        }

                        close(client_fd);
        return NULL;
}

int main() {
        int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if(socket_fd == -1) {
                printf("Eroare socket!\n");
                return -1;
        }
        struct sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_port = htons(1234);
        server.sin_addr.s_addr = INADDR_ANY;

        int bind_res = bind(socket_fd,
                        (const struct sockaddr*)  &server, sizeof(server));
        if(bind_res == -1) {
                printf("Eroare bind!\n");
                return -2;
        }

        int listen_res = listen(socket_fd, 7);
        if(listen_res == -1) {
                printf("Eroare listen!\n");
                return -3;
        }

        int max_nr_threads = 16;
        pthread_t threads[max_nr_threads];
        int pthread_count = 0;

        struct sockaddr_in client;
        socklen_t client_len;
        while(1) {
                printf("Expecting clients...\n");
                int client_fd = accept(socket_fd,
                                (struct sockaddr*) &client,
                                &client_len);
                if(client_fd == -1) {
                        printf("Client could not connect to the server!\n");
                        continue;
                }

                struct thread_worker_args * argument = (struct thread_worker_args *) malloc(sizeof(struct thread_worker_args));
                argument->client_fd = client_fd;
                argument->client = client;

                int create_res = pthread_create(&threads[pthread_count++],
                                0,
                                thread_routine,
                                (void*) argument);
                if(create_res == -1) {
                        printf("Error create thread!\n");
                        continue;
                }
        }




        return 0;
}
