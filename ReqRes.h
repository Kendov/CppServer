#ifndef REQRES_H
#define REQRES_H

#include <string>
class ReqRes{
private:
    
    
    const std::string CODE200 = "200 OK";
    const std::string CODE404 = "404 Not Found";

    char *respOutput;

    //used for the httpHeader function. It returns the content type based on the filename extension
    std::string contType(std::string request);

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
    std::string reqType(char buffer[]);

    bool isGet(char buffer[]);
    
    //return file request
    std::string reqFile(char inpbuffer[]);
    
    

    std::string httpHeader(std::string statusCode, std::string contType, int size);

    //make http header
    
    char* makeResp(char buffer[]);
    

    //get file requisition

    //
};
#endif
