#include "ReqRes.h"

#include <string.h>
#include <sstream>
#include <iostream>
#include <fstream>


//used for the httpHeader function. It returns the content type based on the filename extension
std::string ReqRes::contType(std::string request){
    std::string type;
    bool isType = false;

    for(int i = 0; i < request.size(); i++){
        if(request[i] == '.'){
            isType = true;
            continue;
        }
        if(isType){
            type += request[i];
        }
    }
    
    if(type == "html" || type == "htm" ) return "text/html";
    if(type == "css"                   ) return "text/css";
    if(type == "js"                    ) return "application/javascript";
    if(type == "json"                  ) return "application/json";
    if(type == "ico"                   ) return "image/x-icon";
    if(type == "jpeg" || type == "jpg" ) return "image/jpe";
    if(type == "png"                   ) return "image/png";
}




//get request type
std::string ReqRes::reqType(char buffer[]){
    std::string output;
    

    for(int i = 0;buffer[i] != ' ';i++){
        
        output += buffer[i];
        
    }

    return output;
}

bool ReqRes::isGet(char buffer[]){
    return reqType(buffer) == "GET"? true:false;
}

//return file request
std::string ReqRes::reqFile(char inpbuffer[]){
    std::string fileoutput;
    int spaceCount = 0;
    for(int i = 0; inpbuffer[i]!= '\n';i++){
        if(inpbuffer[i] == ' '){
            spaceCount++;
            continue;
        }
        
        if(spaceCount > 0 && spaceCount < 2){
            if(inpbuffer[i] != '/')
                fileoutput += inpbuffer[i];
            
        }
        if(spaceCount > 1)
            break;

    }
    
    return fileoutput == ""? "index.html":fileoutput;
    //if fileoutput is empty return the index.html file
}



std::string ReqRes::httpHeader(std::string statusCode, std::string contType, int size){
    //"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: size of body\n\n"
    std::string header;
    header += "HTTP/1.1 ";
    header += statusCode + "\n";
    header += "Content-Type: " + contType + "\n";
    header += "Content-Length: " + std::to_string(size) + "\n\n";

    return header;
}

//make http header

char* ReqRes::makeResp(char buffer[]){

    

    std::fstream file;
    file.open(reqFile(buffer));

    if(!file){
        std::cout <<__LINE__<<"erro cant open file: "<< reqFile(buffer) <<std::endl;
        //std::cout <<buffer<<std::endl;
        std::string message = "ERROR File not found";
        std::string error = httpHeader(CODE404, "text/plain", error.size()) + message;

        respOutput =  new char[error.size()];
        strcpy(respOutput, error.c_str());
        return respOutput;
    }
    std::cout<<__LINE__<<"responce call"<<std::endl;
    std::ostringstream sstream;
    sstream << file.rdbuf();

    file.close();

    std::string body = sstream.str();

    std::string response = httpHeader(CODE200, contType(reqFile(buffer)), body.size());
    std::string message = response + body;
    respOutput =  new char[message.size()];
    strcpy(respOutput, message.c_str());

    return respOutput;
}


