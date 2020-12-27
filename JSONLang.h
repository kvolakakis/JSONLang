#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <stdarg.h> 
#include <fstream>
#include <typeinfo>

#define PROGRAM_BEGIN int main(){
#define PROGRAM_END  return 0;} 
#define JSON(temp) ;JSON_String temp 
#define STRING(value) *new JSON_String(value)   


using namespace std;

typedef enum JSON_Type{
    STRING,
    INTEGER,
    DOUBLE,
    BOOLEAN,
    NULL_TYPE,
    OBJECT,
    ARRAY
}JSON_Type;


class JSON_String{
    private:
        JSON_Type type = STRING;
        string value;
    public:
        string  temp;
    JSON_String(string value){
        this->value = value;
    }
    
    string getValue(){
        return this->value;
    }

    void setValue(string newValue){
        this->value = newValue;
    }

    JSON_Type getType(){
        return this->type;
    }

    void setType(JSON_Type newType){
        this->type = newType;
    }

};



void start(){
    std::cout << "Let's begin" << std::endl;
}