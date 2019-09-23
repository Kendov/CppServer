#include <string>
#include <iostream>
#include <fstream>

//requisition metods



class ReqRes{
private:
    
    
    const std::string CODE200 = "200 OK";
    const std::string CODE404 = "404 Not Found";

    char *respOutput;

    //used for the httpHeader function. It returns the content type based on the filename extension
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

public:
    /*
    ReqRes(char buffer[]){
        //inpBufferP = new char[sizeof(buffer)];
        //inpBufferP = buffer;
        
    }
    */
    /*
    ~ReqRes(){
        //std::cout<<inpBufferP<<std::endl;
        
        //delete[] respOutput;  //??????  if delete this pointer the server crashes 
        std::cout<<"respOutput deleted"<<std::endl;
    }
    */
    
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
    std::string reqFile(char inpbuffer[]){
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
    
    char* makeResp(char buffer[]){

        

        std::fstream file;
        file.open(reqFile(buffer));

        if(!file){
            std::cout <<"erro cant open file: "<< reqFile(buffer) <<std::endl;
            std::cout <<buffer<<std::endl;
            std::string message = "ERROR File not found";
            std::string error = httpHeader(CODE404, "text/plain", error.size()) + message;

            respOutput =  new char[error.size()];
            strcpy(respOutput, error.c_str());
            return respOutput;
        }

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
    

    //get file requisition

    //
};

