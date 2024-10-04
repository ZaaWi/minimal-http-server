#include <arpa/inet.h> // socket(), bind(), listen(), accept(), recv(), send()

# define PORT 8080 // port number


int main(int argc, char const *argv[])
{
	int server_socket; // server socket descriptor
	int randomPORT = PORT;
	struct sockaddr_in server_address;
	char ip4[INET_ADDRSTRLEN];

	server_socket = socket(AF_INET, SOCK_STREAM, 0); // create a server socket

	if(server_socket <= 0) // check if server socket is created successfully
	{
		printf("Error in server socket creation\n");
		perror("Error in server socket creation");
		exit(EXIT_FAILURE); // exit the program
	}

	randomPORT = 8080 + (rand() % 10);
	memset(&server_address, 0, sizeof server_address);
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(randomPORT);

	// bind the server socket to the server address
	while(bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
	{
		randomPORT = 8080 + (rand() % 10);
		server_address.sin_port = htons(randomPORT);
	}
	if(listen(server_socket, 10) < 0) // listen for incoming connections
	{
		printf("Error in listening\n");
		perror("Error in listening");
		exit(EXIT_FAILURE); // exit the program
	}
	
	while(1) {
		socklen_t len = sizeof(clinet_address);
		printf("Server is listening on port %d\n", randomPORT);
		client_socket = accept(server_socket, (struct sockaddr *)&client_address, &len); // accept the incoming connection
		if (client_socket < 0) // check if client socket is created successfully
		{
			printf("Error in client socket creation\n");
			perror("Error in client socket creation");
			// exit(EXIT_FAILURE); // exit the program
			return 0;
		}
		else {
			inet_ntop(AF_INET, &(client_address.sin_addr), ip4, INET_ADDRSTRLEN);
			printf("connected to client with IP address: %s \n", ip4);
		}
	}
}
