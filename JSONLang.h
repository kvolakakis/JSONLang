#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <stdarg.h> 
#include <fstream>
#include <typeinfo>

#define PROGRAM_BEGIN int main(){ string tmp; string temp_key = "key"; 
#define PROGRAM_END  ; return 0;} 
#define JSON(temp) ; ::json_name=#temp; JSON_val temp
#define STRING(value) JSON_val((string)value, temp_key) 
#define NUMBER(value) JSON_val((double)value, temp_key)
#define OBJECT  *new JSON_val
#define ARRAY JSON_val("array")
/*
 * # is used to stringify value
 * trickiest so far (commit 3)
 * assign true value to expression so that using expr1 ? expr2 : expr3 leads to calling both expr1 and expr3
 */ 
#define KEY(value) (((temp_key = #value) == #value) && (cout << "key: " << temp_key << endl )  && false) ? true
#define PRINT ; cout << 


using namespace std;
int tabs = 0;
string json_name = "obj";
typedef enum JSON_Type{
    STRING,
    INTEGER,
    DOUBLE,
    BOOLEAN,
    NIL,
    OBJ,
    ARR
}JSON_Type;

string getJsonName(){return ::json_name;}

//TODO: check if it's possible to keep different types of values using templates
//TODO; maybe use map to keep (key, value) pairs
class JSON_val{
    private:
        JSON_Type type;
        string strValue;
        double numValue;
        bool boolValue;
        string key;
        vector<JSON_val> object;
    public:
        string  temp;

    //common methods for every value type
    JSON_Type getType(){
        return this->type;
    }

    void setType(JSON_Type newType){
        this->type = newType;
    }

    string getKey(){
        return this->key;
    }

    void setKey(string key){
        this->key = key;
    }

    //basic methods regarding strings    
    JSON_val(string value, string key){
        this->key = key;
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
    JSON_val(int value, string key){
        this->key = key;
        this->type = INTEGER;
        this->numValue = value;
        cout << "creating integer " << this->numValue << endl;
    }

    JSON_val(double value, string key){
        this->key = key;
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

    JSON_val(initializer_list<JSON_val> list){
        cout << "=====>in object contructor with list of size: " << list.size() << endl;
        vector<JSON_val>::iterator obj_iterator;
        obj_iterator = this->object.begin();
        obj_iterator = this->object.insert(obj_iterator, list);
        this->type = OBJ;  
        this->key = getJsonName();  
    }

    vector<JSON_val> getObject(){
        return this->object;
    }


    friend ostream &operator<<(ostream  &os, JSON_val &json){
        cout << "\"" << json.getKey() <<"\" : ";
        switch(json.getType()){
            case STRING:
                cout << "\"" <<json.getStrValue() << "\"" << endl;
                break;
            case INTEGER:
            case DOUBLE:
                cout << json.getNumValue() << endl;
                break;
            case BOOLEAN:
                cout << json.getBoolValue() << endl;
                break;
            case OBJ:
                tabs+=2;
                cout << "object{\n";
                //cout << "size: " << json.getObject().size() << endl;
                for(int i = 0; i < json.getObject().size(); i++){
                    for(int j = 0; j<tabs; j++) cout << "   ";
                    //cout << i <<"-> type: " << json.getObject()[i].getType() << ": ";
                    PRINT json.getObject()[i];
                }
                tabs-=2;
                for(int j = 0; j<tabs; j++) cout << "   ";
                cout << "}\n";

                break;
        }
    }

    JSON_val &operator,(JSON_val *value){
        this->object.push_back(value);
        return *value;
    }

    /*JSON_val &operator,(JSON_val value){
        this->object.push_back(value);
        return value;
    }

    JSON_val &operator[](JSON_val value){
        cout << "in array making " << value.getType() << endl;
        return value;
    }

    JSON_val operator[](JSON_val Head){return Head;};
    JSON_val operator[](JSON_val *Head){return Head;};*/
};
