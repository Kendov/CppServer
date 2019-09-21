#include <string>
#include <iostream>
#include <fstream>

//requisition metods
//enum reqMet{GET, POST, PUT, PATCH, DELETE};
const std::string CODE200 = "200 OK";
const std::string CODE404 = "404 Not Found";

//*****************TODO****************
//Put everything in classes and clean all this mess

namespace Req{

    //get request type
    std::string reqType(char buffer[]){
        std::string output;
        

        for(int i = 0;buffer[i] != ' ';i++){
            
            output += buffer[i];
            
        }
        
        

        return output;
    }

    bool isGet(char buffer[]){
        return reqType(buffer) == "GET"? true:false;
    }

    //return file request
    std::string reqFile(char buffer[]){
        std::string output;
        int spaceCount = 0;
        for(int i = 0; buffer[i]!= '\n';i++){
            if(buffer[i] == ' '){
                spaceCount++;
                continue;
            }

            if(spaceCount > 0 && spaceCount < 2){
                if(buffer[i] != '/')
                    output += buffer[i];
            }
            if(spaceCount > 1)
                break;

        }
        
        return output == ""? "index.html":output;
    }
    std::string contType(std::string request){
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
    

    std::string httpHeader(std::string statusCode, std::string contType, int size){
        //"HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: size of body\n\n"
        std::string header;
        header += "HTTP/1.1 ";
        header += statusCode + "\n";
        header += "Content-Type: " + contType + "\n";
        header += "Content-Length: " + std::to_string(size) + "\n\n";

        return header;
    }

    //make http header
    std::string makeResp(char buffer[]){

        

        std::fstream file;
        file.open(reqFile(buffer));

        if(!file){
            std::string error = "ERROR File not found";
            return httpHeader(CODE404, "text/plain", error.size()) + error;
        }

        std::ostringstream sstream;
        sstream << file.rdbuf();

        file.close();

        std::string body = sstream.str();

        std::string response = httpHeader(CODE200, contType(reqFile(buffer)), body.size());
        return response + body;
    }

    //get file requisition

    //
};

namespace res{
    //return file asked
}