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



    WSACleanup();
    return 0;
}