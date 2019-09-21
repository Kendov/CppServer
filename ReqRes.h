#include <string>
#include <iostream>
#include <fstream>

//requisition metods
//enum reqMet{GET, POST, PUT, PATCH, DELETE};

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

    //make http header

    //get file requisition

    //
};

namespace res{
    //return file asked
}