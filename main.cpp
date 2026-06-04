#include<iostream>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib")

int main(){
    
    WSADATA wsaData;

    std::cout << "init winsock+++" << std::endl;
    if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0){
        std::cout << "failed to init winsock++ , Error code: " << WSAGetLastError() << std::endl;
    }

    std::cout << "Winsock++ init successfully" << std::endl;


    
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket == INVALID_SOCKET){
        std::cout << "failed to create socket, Error code: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }   
    std::cout << "Socket created successfully!" << std::endl;

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);


    if(bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR){
        std::cout << "failed to bind socket, Error code: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "Socket binded successfully!" << std::endl;

    if(listen(serverSocket, 3) == SOCKET_ERROR){
        std::cout << "Listen failed, Error code:" << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;

    }

    std::cout << "Server is listening on port 8080..." << std::endl;

    SOCKET clientSocket = accept(serverSocket, NULL, NULL);
    if(clientSocket ==  INVALID_SOCKET){
        std::cout << "Accept failed. Error code" << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "client connected" << std::endl;

    char buffer[1024];

    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if(bytesReceived > 0 ){
        std::cout << "--- Received HTTP Request ---" << std::endl;
        std::cout << buffer << std::endl; // พ่นข้อความที่ Browser ส่งมาดูบนจอเลย
        std::cout << "-----------------------------" << std::endl;



        std::string htmlContent = "<h1>Hello from Zag's Server!</h1><p>My Custom Web Server works completely!</p>";
        
        std::string httpResponse = 
            "HTTP/1.1 200 OK\r\n"                
            "Content-Type: text/html\r\n"        
            "Content-Length: " + std::to_string(htmlContent.length()) + "\r\n" 
            "\r\n"                               
            + htmlContent;                       

        
        send(clientSocket, httpResponse.c_str(), httpResponse.length(), 0);
        std::cout << "Response sent to client success! eiei" << std::endl;

basic http request
        closesocket(clientSocket);
    }


    WSACleanup();
    return 0;
}