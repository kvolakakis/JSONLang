/*
 *
 * KALHMERA....EEEE XAXA TI LEW. KALHSPERA BABE.
 * SIGA MHN EMPAINES APO TO PRWI NA DEIS TI EXW KANEI. :3
 * I COMMENTED AS MUCH AS POSSIBLE ON MAJOR  THINGS SO THAT YOU 
 * (MAY) HOPEFULLY UNDERSTAND SOME OF THEM. 
 * HOWEVER, IN CASE OF EMERGENCY PRESS CTRL + A + BACKSPACE,
 * COMMIT YOUR CHANGES AND EVERYTHING WILL BE FINE. 
 * IF THIS INSISTS NOT WORKING, SMS "991 EMERGENCY <<YOUR_NAME>>" 
 * AT +306981382217 WILL SOLVE ANY POSSIBLE PROBLEMS YOU MIGHT HAVE.
 * HAVE A GREAT AFTERNOON MY LOVE. (?'?'?)
 * 
 */

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <stdarg.h> 
#include <fstream>
#include <typeinfo>

#define PROGRAM_BEGIN int main(){ string tmp; 
#define PROGRAM_END  ; return 0;} 
#define JSON(temp) ;  setKeyName(#temp); JSON_val temp  
#define STRING(value) JSON_val((string)value, temp_key) 
#define NUMBER(value) JSON_val((double)value, temp_key)
#define OBJECT  (((setObjName(temp_key))) && false) ? true :  *new JSON_val
#define ARRAY JSON_val("array")
/*
 * # is used to stringify value
 * trickiest so far (commit 3)
 * assign true value to expression so that using expr1 ? expr2 : expr3 leads to calling both expr1 and expr3
 */ 
#define KEY(value) ((setKeyName(#value)) && (cout << "key: " << temp_key << endl )  && false) ? true
#define PRINT ; cout << 


using namespace std;
int tabs = 0;/*
string outer_name = "";
string inner_name = "";*/
vector<string> objNames;
string temp_key; 
typedef enum JSON_Type{
    STRING,
    INTEGER,
    DOUBLE,
    BOOLEAN,
    NIL,
    OBJ,
    ARR
}JSON_Type;

//START helper functions to preserve object pairs' keys
string getObjName(){
    string tmp = ::objNames.back(); 
    ::objNames.pop_back();
    return tmp;   
}

int setObjName(string name){
    ::objNames.push_back(name);
    return 1;
}

string getKeyName(){
    return ::temp_key;   
}

int setKeyName(string name){ 
    ::temp_key = name;
    return 1;
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

    //STRING("..") constructor   
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

    //NUMBER("..") constructor (fix: goes directly to double. don't think it's a problem ?\_(?)_/? )
    JSON_val(int value, string key){
        this->key = key;
        this->type = INTEGER;
        this->numValue = value;
        cout << "creating integer " << this->numValue << endl;
    }

    //NUMBER("..") constructor (the proper, always working as planned one)
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
    //basic methods regarding bool values (true/false)
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

    //OBJECT { } constructor. Might also be usedfor arrays as well I guess. Not sure yet :/. 
    JSON_val(initializer_list<JSON_val> list){
        cout << "=====>in object contructor with list of size: " << list.size() << endl;
        this->key = getObjName();
        vector<JSON_val>::iterator obj_iterator;
        obj_iterator = this->object.begin();
        obj_iterator = this->object.insert(obj_iterator, list);
        this->type = OBJ;  
    }

    vector<JSON_val> getObject(){
        return this->object;
    }

    //operator overloading for << operator (used for cout << ..;)
    friend ostream &operator<<(ostream  &os, JSON_val &json){
        cout << "\"" << json.getKey() <<"\" : ";
        switch(json.getType()){
            case STRING:
                cout << "\"" <<json.getStrValue() << "\"";// << endl;
                break;
            case INTEGER:
            case DOUBLE:
                cout << json.getNumValue();// << endl;
                break;
            case BOOLEAN:
                cout << json.getBoolValue();// << endl;
                break;
            case OBJ:
                tabs+=2;
                cout << "{\n";
                //cout << "size: " << json.getObject().size() << endl;
                for(int i = 0; i < json.getObject().size(); i++){
                    for(int j = 0; j<tabs; j++) cout << "   ";
                    //cout << i <<"-> type: " << json.getObject()[i].getType() << ": ";
                    PRINT json.getObject()[i];
                    if(i != json.getObject().size() - 1) cout << ", ";
                    cout << endl;
                }
                tabs-=2;
                for(int j = 0; j<tabs; j++) cout << "   ";
                cout << "}";

                break;
        }
    }

    //operator overloading for , operator (used to separate OBJECT, and  possibly ARRAY too, (key, value) pairs)
    JSON_val &operator,(JSON_val *value){
        this->object.push_back(value);
        return *value;
    }


    //operators overloading not (yet) used
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
