//#include <iostream> //inluded in ReqRes.h
#include <winsock2.h>
//#include <fstream>
#include <string> //inluded in ReqRes.h
#include <sstream>

#include "ReqRes.h"


 
using namespace std;



int main()
{   
    //get file
    //saparete this ******

    /*
    fstream htmlfile;
    htmlfile.open("index.html");
    
    std::ostringstream sstream;
    sstream << htmlfile.rdbuf();
    string tochar = sstream.str();
    tochar.insert(0,"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " + to_string(tochar.size()) + "\n\n");
    
    

    char *htmlpage =  new char[tochar.size()];
    //std::cout<<strlen(tochar.c_str) <<"   "<<tochar.size() + 1<<std::endl;
    strcpy(htmlpage, tochar.c_str());
    */
    cout <<"start" <<endl;
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
    
        cout << "Listening for incoming connections..." << endl;
    
        char buffer[1024];
        char newmessage[1024] = "fromServer";
        int clientAddrSize = sizeof(clientAddr);
        if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
        {
            cout << "Client connected!" << endl;
            recv(client, buffer, sizeof(buffer), 0);
            cout << "Client says: \n ********" << endl << buffer << endl;
            //cout<<"get wants = \n"<<Req::reqFile(buffer)<<"\n\n\n"<<endl;
            cout<<"Resp header = \n"<<Req::makeResp(buffer)<<"\n\n\n"<<endl;

            char *htmlpage =  new char[Req::makeResp(buffer).size()];
            strcpy(htmlpage, Req::makeResp(buffer).c_str());
            

            memset(buffer, 0, sizeof(buffer));
            send(client,htmlpage, sizeof(newmessage),0);
    
            closesocket(client);
            cout << "Client disconnected." << endl;

            //delete [] htmlpage; // why i cant delete???????

            cout << "deleted" << endl;
            //cin.get();
        }
        
    }
}

//g++ server.cpp -o server "C:\MinGW\lib\libws2_32.a"
