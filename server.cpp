//#include <fstream>
//#include <string>
//#include <sstream>
#include <iostream>
#include <winsock2.h>
#include "ReqRes.h"


/*
****************TODO***************
* 
* make a include/link file
* multitread
* request limitation
* print macro for debug mode
* client requests log?
* ASCII ui for data visualization?
* clean code
* 
***********************************
*/


 
int main()
{   
    std::cout <<"start" <<std::endl;
    //**********************

    WSADATA WSAData;
 
    SOCKET server, client;
 
    SOCKADDR_IN serverAddr, clientAddr;
 
    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);
 
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5555);
 
    bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
    while(true){

        listen(server, 0);
    
        std::cout << "Listening for incoming connections..." << std::endl;
        char buffer[1024]; //for receive client request
    
        
        int clientAddrSize = sizeof(clientAddr);
        if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
        {
            std::cout << "Client connected!" << std::endl;
            recv(client, buffer, sizeof(buffer), 0);

            std::cout << "Client says: \n ********" << std::endl << buffer << "**************" << std::endl;

            //*****
            ReqRes Req; //instantiate ReqRes class to http request handling
            //*****
            
            
            
            send(client,Req.makeResp(buffer), Req.responseSize,0);
            std::cout<<Req.responseSize<<std::endl; //414
            

            memset(buffer, 0, sizeof(buffer)); //set buffer to 0
            closesocket(client);
            std::cout << "Client disconnected." << std::endl;
            
            //std::cin.get();
        }
        
    }
}

//g++ server.cpp -o server "C:\MinGW\lib\libws2_32.a"
