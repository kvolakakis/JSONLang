#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <stdarg.h> 
#include <fstream>
#include <typeinfo>

#define PROGRAM_BEGIN int main(){ string tmp;
#define PROGRAM_END  ; return 0;} 
#define JSON(temp) ;JSON_val temp 
#define STRING(value) *new JSON_val((string)value) 
#define NUMBER(value) *new JSON_val((double)value) 
#define KEY(value) STRING(#value) //# is used to stringify value
#define PRINT ; cout << 


using namespace std;

typedef enum JSON_Type{
    STRING,
    INTEGER,
    DOUBLE,
    BOOLEAN,
    NIL,
    OBJECT,
    ARRAY
}JSON_Type;


class JSON_val{
    private:
        JSON_Type type;
        string strValue;
        double numValue;
        bool boolValue;
    public:
        string  temp;

    //common methods for every value type
    JSON_Type getType(){
        return this->type;
    }

    void setType(JSON_Type newType){
        this->type = newType;
    }

    //basic methods regarding strings    
    JSON_val(string value){
        this->type = STRING;
        this->strValue = value;
        cout << "creating string " << this->strValue << endl;
    }
    string getStrValue(){
        return this->strValue;
    }

    void setStrValue(string newValue){
        this->strValue = newValue;
    }

    //basic methods regarding numbers (doubles and integers)
    JSON_val(int value){
        this->type = INTEGER;
        this->numValue = value;
        cout << "creating integer " << this->numValue << endl;
    }

    JSON_val(double value){
        this->type = DOUBLE;
        this->numValue = value;
        cout << "creating double " << this->numValue << endl;
    }

    double getNumValue(){
        return this->numValue;
    }

    void setNumValue(double newValue){
        this->numValue = newValue;
    }

    //-----NEEDS TO BE CHECKED..NOT SURE IF RIGHT-----//
    //basic methods regarding bool valus (true/false)
    JSON_val(bool value){
        this->type = BOOLEAN;
        this->boolValue = value;
    }

    double getBoolValue(){
        return this->boolValue;
    }

    void setNumValue(bool newValue){
        this->boolValue = newValue;
    }
    //-----END NEEDS TO BE CHECKED-----//

    friend ostream &operator<<(ostream  &os, JSON_val &json){
        switch(json.getType()){
            case STRING:
                cout << json.getStrValue() << endl;
                break;
            case INTEGER:
            case DOUBLE:
                cout << json.getNumValue() << endl;
                break;
            case BOOLEAN:
                cout << json.getBoolValue() << endl;
                break;
        }
    }

};
