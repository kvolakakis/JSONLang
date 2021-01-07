#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <stdarg.h> 
#include <fstream>
#include <typeinfo>
#define PROGRAM_BEGIN int main(){ string tmp; 
#define PROGRAM_END  ; return 0;} 
#define PRINT ;cout <<
#define JSON(temp) ;  setKeyName(#temp); JSON_val temp  
#define STRING(value) JSON_val((string)value, temp_key) 
#define NUMBER(value) JSON_val((double)value, temp_key)
#define TRUE JSON_val((bool)true)
#define FALSE JSON_val((bool)false)
#define OBJECT  (((setObjName(temp_key))) && false) ? true :  *new JSON_val
#define ARRAY (((setArrName(temp_key))) && false) ? true : JSON_val("3.1415926535897932384", temp_key)
/*
 * # is used to stringify value
 * trickiest so far (commit 3)
 * assign true value to expression so that using expr1 ? expr2 : expr3 leads to calling both expr1 and expr3
 */ 
#define KEY(value) ((setKeyName(#value)) && false) ? true
#define SET ;
#define ASSIGN |=
#define ERASE |
#define APPEND ^= 


using namespace std;
//JSON_val temp = *new JSON_val{ KEY(3) : JSON_val((string)"1", temp_key)};
//JSON_val temp = JSON_val("3.1415926535897932384", temp_key)[ JSON_val((string)"1", temp_key)];
int tabs = 0;
vector<string> objNames;
vector<string> arrNames;
string temp_key;
bool inside_array = false; 
typedef enum JSON_Type{
    STRING,
    INTEGER,
    DOUBLE,
    BOOLEAN,
    NIL,
    OBJ,
    ARR
}JSON_Type;

//START helper functions to preserve object pairs' keys and arrays values
string getObjName(){
    string tmp = ::objNames.back(); 
    ::objNames.pop_back();
    return tmp;   
}

int setObjName(string name){
    ::objNames.push_back(name);
    return 1;
}

string getArrName(){
    string tmp = ::arrNames.back(); 
    ::arrNames.pop_back();
    return tmp;   
}

int setArrName(string name){
    ::arrNames.push_back(name);
    return 1;
}

string getKeyName(){
    return ::temp_key;   
}

int setKeyName(string name){ 
    ::temp_key = name;
    return 1;
}

void error_message(string mess){
    cout << "ERROR! " << mess << " " << endl;
    exit(1);
}
//END helper functions to preserve object pairs' keys

//TODO: check if it's possible to keep different types of values using templates
//TODO: maybe use map to keep (key, value) pairs
class JSON_val{
    private:
        JSON_Type type;
        string strValue;
        double numValue;
        bool boolValue;
        string key;
        vector<JSON_val> object;
        vector<JSON_val> array;
        bool arr_obj_cell  = false;
        bool arrayDisplay = false;
        int scope; 
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

    //STRING("..") constructor. 
    //It is also used for initialization of arrays, when given string is "3.1415926535897932384"
    //Not quite safe, should be optimized, however works for now. If we find time we might fix it somehow.
    JSON_val(string value, string key){
        this->key = key;
        if(value == "3.1415926535897932384"){
            this->type = ARR;
            //::inside_array = true;
            //cout << "creating array:  " << getKeyName() << endl;
        }
        else
        {
            this->type = STRING;
            this->strValue = value;
            //cout << "creating string " << this->strValue << endl;    
        }
    }
    string getStrValue(){
        return this->strValue;
    }

    void setStrValue(string newValue){
        this->strValue = newValue;
    }

    //basic methods regarding numbers (doubles and integers)

    //NUMBER("..") constructor (possible TODO: goes directly to double. don't think it's a problem ?\_(?)_/? )
    JSON_val(int value, string key){
        this->key = key;
        this->type = INTEGER;
        this->numValue = value;
        //cout << "creating integer " << this->numValue << endl;
    }

    //NUMBER("..") constructor (the proper, always working as planned one)
    JSON_val(double value, string key){
        this->key = key;
        this->type = DOUBLE;
        this->numValue = value;
        //cout << "creating double " << this->numValue << endl;
    }

    double getNumValue(){
        return this->numValue;
    }

    void setNumValue(double newValue){
        this->numValue = newValue;
    }

    //-----NEEDS TO BE CHECKED..NOT SURE IF RIGHT-----//
    //basic methods regarding bool values (true/false)
    JSON_val(bool value){
        cout << "inside boolean constructor" << endl;
        this->type = BOOLEAN;
        this->key = ::getKeyName();
        this->boolValue = value;
    }

    double getBoolValue(){
        return this->boolValue;
    }

    void setNumValue(bool newValue){
        this->boolValue = newValue;
    }
    //-----END NEEDS TO BE CHECKED-----//

    //OBJECT { } constructor. 
    JSON_val(initializer_list<JSON_val> list){
        this->key = getObjName();
        vector<JSON_val>::iterator obj_iterator;
        obj_iterator = this->object.begin();
        obj_iterator = this->object.insert(obj_iterator, list);
        this->type = OBJ;
    }

    vector<JSON_val> getObject(){
        return this->object;
    }
    vector<JSON_val> getArray(){
        return this->array;
    }
    //operator overloading for << operator (used for cout << ..;)
    friend ostream &operator<<(ostream  &os, JSON_val &json){
        if(!json.arrayDisplay && !json.arr_obj_cell) 
            cout << "\"" << json.getKey() <<"\" : ";
        switch(json.getType()){
            case STRING:
                cout << "\"" << json.getStrValue() << "\"";// << endl;
                break;
            case INTEGER:
            case DOUBLE:
                cout << json.getNumValue();// << endl;
                break;
            case BOOLEAN:
                if(json.getBoolValue()) 
                    cout << "true"; 
                else    
                    cout << "false";
                break;
            case OBJ:
                tabs+=2;
                cout << "{";
                //cout << "size: " << json.getObject().size() << endl;
                for(int i = 0; i < json.getObject().size(); i++){
                    cout << endl;
                    for(int j = 0; j<tabs; j++) cout << "  ";
                    //cout << i <<"-> type: " << json.getObject()[i].getType() << ": ";
                    PRINT json.getObject()[i];
                    if(i != json.getObject().size() - 1) cout << ", ";
                    cout << endl;
                }
                tabs-=2;
                for(int j = 0; j<tabs; j++) cout << "  ";
                cout << "}" << endl;;
                break;
            case ARR:
                tabs+=2;
                cout << "[";
                for(int i = 0; i<json.getArray().size();  i++){
                    cout << endl;
                    for(int j = 0; j<tabs; j++) cout << "  ";
                    PRINT json.getArray()[i];
                    if(i != json.getArray().size()-1) cout << ", ";
                    cout << endl;
                }
                tabs-=2;
                for(int j = 0; j<tabs; j++) cout << "  ";
                cout << "]"  << endl;
                break;
        }
        //used to print a cell of an array or an object (without key)
        if(json.arr_obj_cell) json.arr_obj_cell = !json.arr_obj_cell; 
    }

    //operator overloading for , operator (used to separate OBJECT, and  possibly ARRAY too, (key, value) pairs)
    JSON_val &operator,(JSON_val *value){
        this->object.push_back(value);
        return *this;
    }

    //operators overloading not (yet) used
    JSON_val &operator,(JSON_val value){
        //FIRST INSERTION GODDAMMIT
        if(this->array.size() == 0){ 
            this->array.push_back(*this);
            this->array[0].setKey("0");
            this->array[0].arrayDisplay = true;
            this->setType(ARR);
        }
        value.arrayDisplay = true;
        value.setKey(to_string(this->array.size()));
        this->array.push_back(value);
        return *this;
    }
    //operator overloading for displaying array
    /*JSON_val &operator[](JSON_val value){
        cout << "in array making " << value.getType() << endl;
        return value;
    }*/
    JSON_val operator[](JSON_val value){
        value.setKey(getArrName());
        return value;
    };

    JSON_val &operator[](int index){
        if(this->getType() == ARR){
            this->array[index].arr_obj_cell = true;
            return this->array[index];
        }  
        else if(this->getType() == OBJ){
            for(int i = 0; i < this->getObject().size(); i++)
                if(this->getObject()[i].getKey() == to_string(index)){
                    this->object[i].arr_obj_cell = true;
                    return this->object[i];
                }
        }    
        else{
            ::error_message("invalid type before []");
        }

        return *this;
    };

    JSON_val &operator[](const char* key){
        if(this->getType() == OBJ){
            for(int i = 0; i < this->getObject().size(); i++)
                if(this->getObject()[i].getKey() == key){
                    this->object[i].arr_obj_cell = true;
                    return this->object[i];
                }
        }    
        else{
            ::error_message("invalid type before [string]");
        }
        return *this;
    };

    //operator overloading for set .. assign
    JSON_val &operator|=(JSON_val value){
        string old_key = this->getKey();
        bool inside_array = this->arrayDisplay; 
        *this = value;
        this->arrayDisplay = inside_array;
        this->setKey(old_key);
        return *this;
    }
    //operator overloading for erase
    JSON_val &operator|(JSON_val value){

    }

    //operator overloading for append
    JSON_val &operator^=(JSON_val value){

    }


};
