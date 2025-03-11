#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main() {

	int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (socket_fd == -1) {
		printf("Socket error!\n");
		return -1;
	}

	int broadcast = 1;
	int result_setsockopt = setsockopt(socket_fd, SOL_SOCKET,
		SO_BROADCAST, &broadcast, sizeof(broadcast));

	if (result_setsockopt == -1) {
		printf("Setsockopt error!\n");
		return -1;
	}

	struct sockaddr_in recv_addr;
	recv_addr.sin_family = AF_INET;
	recv_addr.sin_port = htons(1234);
	recv_addr.sin_addr.s_addr = inet_addr("192.168.103.255");

	char message[100] = "GAbi mIrcea\n";
	while (1) {
		printf("Here!\n");

		int result_sendto = sendto(socket_fd, message,
			strlen(message) + 1, 0,
			(const struct sockaddr*)&recv_addr, sizeof(recv_addr));

		if (result_sendto == -1) {
			continue;
		}
		sleep(7);
	}

	return 0;
}
