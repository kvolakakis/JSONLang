#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <stdarg.h> 
#include <fstream>
#include <typeinfo>
#define PROGRAM_BEGIN int main(){ string tmp; JSON_val dummy = (JSON_val)0; 
#define PROGRAM_END  ; return 0;} 
#define PRINT ; if(print_newline) cout << endl; print_newline = true; for(int j = 0; j<tabs; j++) cout << "  "; cout <<
#define JSON(temp) ;  setKeyName(#temp); JSON_val temp  
#define STRING(value) *new JSON_val((string)value, temp_key) 
#define NUMBER(value) *new JSON_val((double)value, temp_key)
#define TRUE *new JSON_val((bool)true)
#define FALSE  *new  JSON_val((bool)false)
#define OBJECT  (((setObjName(temp_key))) && false) ? true :  *new JSON_val
#define ARRAY (((setArrName(temp_key))) && false) ? true : JSON_val("3.1415926535897932384", temp_key)
#define NULL *new JSON_val(temp_key)

/*
 * # is used to stringify value
 * trickiest so far (commit 3)
 * assign true value to expression so that using expr1 ? expr2 : expr3 leads to calling both expr1 and expr3
 * Edit(commit 30+): not even close to the trickiest
 */ 
#define KEY(value) ((setKeyName(#value)) && false) ? true
#define SET ;
#define ASSIGN |=
#define ERASE ; dummy |
#define APPEND ^= 
#define SIZE_OF(json) json.size_of(json);
#define IS_EMPTY(json) json.is_empty(json);
#define HAS_KEY(json, key) json.has_key(json, key);
#define TYPE_OF(json) json.type_of(json);
 
using namespace std;
int tabs = 0;
vector<string> objNames;
vector<string> arrNames;
string temp_key;
bool inside_array = false; 
bool print_newline = true;
typedef enum JSON_Type{
    STRING,
    INTEGER,
    DOUBLE,
    BOOLEAN,
    NIL,
    OBJ,
    ARR
}JSON_Type;

string types[] = {
    "string",
    "number",
    "number",
    "boolean",
    "null",
    "object",
    "arr"
};

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
    cout << endl << "ERROR! file: '" <<__FILE__ << "', line: " << __LINE__ << ". "<< mess << "! " << endl;
    exit(1);
}
//END helper functions to preserve object pairs' keys

class JSON_val{
    private:
        JSON_Type type;
        int nullVal = 0;
        string strValue;
        double numValue;
        bool boolValue;
        string key;
        vector<JSON_val> object;
        vector<JSON_val> array;
        bool arrayDisplay  = true;
        int scope;
        bool visible = true;
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
    //
    JSON_val(string key){
        this->key = key;
        this->type = NIL;
    }

    //basic methods regarding strings

    //STRING("..") constructor. 
    //It is also used for initialization of arrays, when given string is "3.1415926535897932384"
    //Not quite safe, should be optimized, however works for now. If we find time we might fix it somehow.
    JSON_val(string value, string key){
        this->key = key;
        if(value == "3.1415926535897932384"){
            this->type = ARR;
            //this->arrayDisplay = false; 
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
        this->type = BOOLEAN;
        this->key = ::getKeyName();
        this->boolValue = value;
    }

    double getBoolValue(){
        return this->boolValue;
    }
    

    void setBoolValue(bool newValue){
        this->boolValue = newValue;
    }

    //OBJECT { } constructor. *google is a friend of ours*
    JSON_val(initializer_list<JSON_val> list){
        this->key = getObjName();
        //this->arrayDisplay = false;
        vector<JSON_val>::iterator it;
        it = this->object.begin();
        it = this->object.insert(it, list);
        for(int i = 0; i < this->object.size(); i++){
            this->object[i].arrayDisplay = false;
            string temp_key = this->object[i].getKey();
            for(int j = 0; j < this->object.size(); j++){
                if(i != j){
                    if(this->object[j].getKey() == temp_key){
                        string error = "Key '" + temp_key + "' already exists in object '" + this->getKey() +"'. Cannot assign it twice.";
                        ::error_message(error);
                    }
                }
            }
        }
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
        if(json.visible){
            if(!json.arrayDisplay && !json.arrayDisplay) 
                cout << "\"" << json.getKey() <<"\" : ";
            switch(json.getType()){
                case NIL:
                    cout << "null";// << endl;
                    break;
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
                    for(int i = 0; i < json.getObject().size(); i++){
                        if(!json.getObject()[i].visible) ::print_newline = false;
                        PRINT json.getObject()[i];
                        if(i != json.getObject().size() - 1 && json.getObject()[i].visible) cout << ", "<< endl;
                    }
                    if(json.getObject().size() !=  0) cout << endl;
                    tabs-=2;
                    for(int j = 0; j<tabs; j++) cout << "  ";
                    cout << "}";
                    break;
                case ARR:
                    tabs+=2;
                    cout << "[";
                    for(int i = 0; i<json.getArray().size();  i++){
                        if(!json.getArray()[i].visible) ::print_newline = false;
                        PRINT json.getArray()[i];
                        if(i != json.getArray().size()-1 && json.getArray()[i].visible) cout << ", " << endl;
                    }
                    if(json.getArray().size()) cout << endl;
                    tabs-=2;
                    for(int j = 0; j<tabs; j++) cout << "  ";
                    cout << "]";
                    break;
            }
            //used to print a cell of an array or an object (without key)
            //if(json.arrayDisplay) json.arrayDisplay = !json.arrayDisplay;
        }
        return os;
    }


    bool checkIfKeyAvailable(JSON_val json, string key){
        PRINT json;
        for(int i = 0; i < json.getObject().size(); i++){
            if(json.object[i].getKey() == key){
                return false;
            }
        }
        return true;
    }

    //operator overloading for , operator (used to separate ARRAY values)
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

    JSON_val operator[](JSON_val value){
        //SINGLE INSERTION IF ONLY ONE VALUE GODDAMMIT
        if(value.array.size() == 0){ 
            value.array.push_back(value);
            value.array[0].setKey("0");
            value.array[0].arrayDisplay = true;
            value.setType(ARR);
        }
        //value.arrayDisplay = false;
        value.setKey(getArrName());
        return value;
    };

    JSON_val &operator[](int index){
        if(this->getType() == ARR){
            if(index < this->array.size()){
                this->array[index].arrayDisplay = true;
                return this->array[index];
            }
            else{
                string error = "Index '" + to_string(index) + "' of array '" + this->getKey() + "' out of bounds. Array is of size: " + to_string(this->array.size());
                ::error_message(error);
            }
        }  
        else if(this->getType() == OBJ){
            for(int i = 0; i < this->getObject().size(); i++){
                if(this->getObject()[i].getKey() == to_string(index)){
                    this->object[i].arrayDisplay = true;
                    return this->object[i];
                }
            }
            //if we reach here it means we dont have a pair with "index" as a key. So we make a new one;
            JSON_val *temp = new JSON_val((string)"dummy", to_string(index));
            this->object.push_back(*temp);
            return this->object[this->object.size() - 1];
        }    
        else{
            ::error_message("Invalid type of json lvalue before []");
        }

        return *this; //hope we don't reach here :)
    };

    JSON_val &operator[](const char* key){
        if(this->getType() == OBJ){
            for(int i = 0; i < this->getObject().size(); i++){
                if(this->getObject()[i].getKey() == key){
                    this->object[i].arrayDisplay = true;
                    return this->object[i];
                }
            }
            //if we reach here it means we dont have a pair with "key" as a key. So we make a new one;
            JSON_val *temp = new JSON_val((string)"new value", key);
            temp->arrayDisplay = false;
            this->object.push_back(*temp);
            return this->object[this->object.size() - 1];
            
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
    JSON_val &operator|(JSON_val &value){
        //value.setKey(""); /*key might be needed for future use. For the sake of reusability we dont delete it.*/ 
        value.setStrValue("");
        value.setNumValue((double)-1111111);
        value.array.clear();
        value.object.clear();
        if(value.getType() != OBJ && value.getType() != ARR)
            value.visible  = false;
        return value;
    }

    //operator overloading for append
    JSON_val &operator^=(JSON_val value){
        if(this->getType() == ARR){
            value.arrayDisplay =  true;
            value.setKey(to_string(this->array.size()));
            this->array.push_back(value);
        } 
        else{
            string error = "Variable with name '" + this->getKey() + "' is not an array and, therefore, cannot be appended";
            ::error_message(error);
        }
		return *this;
    }
    bool checkIfNumber(JSON_val value){
        if(value.getType() == INTEGER || value.getType() == DOUBLE)
            return true;
        return false;
    }

    JSON_val &operator+(JSON_val value){
        string temp = "";
        JSON_val *tmp;
        JSON_val *tmp_array;

        if(this->getType() == value.getType()){
            switch(this->getType()){
                case INTEGER:
                case DOUBLE:
                    tmp = new JSON_val((this->getNumValue() + value.getNumValue()), this->getKey());
                    break;
                case STRING:
                    temp = this->getStrValue(); 
                    temp.append(value.getStrValue()); //just to be sure
                    tmp = new JSON_val(temp, this->getKey());
                    break;
                case ARR:                    
                    tmp_array = &value;
                    for(int i = 0; i < this->array.size(); i++){
                        tmp->array.push_back(this->array[i]);
                    }
                    for(int i = 0; i < tmp_array->array.size(); i++){
                        tmp_array->array[i].setKey(to_string(tmp->array.size()));
                        tmp->array.push_back(tmp_array->array[i]);
                    }
                    
                    break;
                case OBJ:
                    for(int i = 0; i < value.object.size(); i++){
                        value.object[i].setKey(to_string(this->object.size()));
                        this->object.push_back(value);
                    }
                    break;
                default:
                    error_message("Operator '+' can not be used for JSON values with given types.");
                    break;   
            }
        }
        else{
            error_message("JSON types mismatch between values given for '+' operator");
        }
        return *tmp;
    }

    JSON_val &operator-(JSON_val value){
        JSON_val *temp;
        if(this->getType() == value.getType()){
            if(checkIfNumber(*this)) //splitted those if just for error handling purposes
                temp = new JSON_val(this->getNumValue() - value.getNumValue(),this->getKey());
            else
                error_message("Operator '-' can not be used for JSON values with given types.");
        }
        else{
            error_message("JSON types mismatch between values given for '-' operator");
        }
        return *temp;
    }

    JSON_val &operator*(JSON_val value){
        JSON_val *temp;
        if(this->getType() == value.getType()){
            if(checkIfNumber(*this)) //splitted those if just for error handling purposes
                temp = new JSON_val(this->getNumValue() * value.getNumValue(), this->getKey());
            else
                error_message("Operator '*' can not be used for JSON values with given types.");
        }
        else{
            error_message("JSON types mismatch between values given for '*' operator");
        }
        return *temp;
    }

    JSON_val &operator/(JSON_val value){
        JSON_val *temp;
        if(this->getType() == value.getType()){
            if(checkIfNumber(*this)) //splitted those if just for error handling purposes
                if(value.getNumValue()!=0)
                    temp = new JSON_val(this->getNumValue() / value.getNumValue(), this->getKey());
                else
                    error_message("Cannot divide by 0 bro..lol.");
            else
                error_message("Operator '/' can not be used for JSON values with given types.");
        }
        else{
            error_message("JSON types mismatch between values given for '/' operator");
        }
        return *temp;
    }

    JSON_val &operator%(JSON_val value){
        JSON_val *temp;
        if(this->getType() == value.getType()){
            if(checkIfNumber(*this)) //splitted those if just for error handling purposes
                if(value.getNumValue()!=0)
                    temp = new JSON_val((double)((int)this->getNumValue() % (int)value.getNumValue()), this->getKey());//no modulo between doubles. Supposed you needed conversion to integers
                else
                    error_message("Cannot divide by 0 bro..lol.");
            else
                error_message("Operator '%' can not be used for JSON values with given types.");
        }
        else{
            error_message("JSON types mismatch between values given for '%' operator");
        }
        return *temp;
    }

    JSON_val &operator<(JSON_val value){
        bool result;
        JSON_val *temp;
        if(this->getType() == value.getType()){
                if(checkIfNumber(*this))
                    result = this->getNumValue() < value.getNumValue();
                else
                    error_message("Operator '<' cannot be used between JSON values of these types");
        }
        else{
            error_message("JSON types mismatch between values given for '<' operator");
        }
        string old_key = this->getKey();
        temp = new JSON_val((bool)result);
        temp->setKey(old_key);
        return *temp;
    }

    JSON_val &operator<=(JSON_val value){
        bool result;
        JSON_val *temp;
        if(this->getType() == value.getType()){
                if(checkIfNumber(*this))
                    result = this->getNumValue() <= value.getNumValue();
                else
                    error_message("Operator '<=' cannot be used between JSON values of these types");
        }
        else{
            error_message("JSON types mismatch between values given for '<=' operator");
        }
        string old_key = this->getKey();
        temp = new JSON_val((bool)result);
        temp->setKey(old_key);
        return *temp;
    }

    JSON_val &operator>(JSON_val value){
        bool result;
        JSON_val *temp;
        if(this->getType() == value.getType()){
                if(checkIfNumber(*this))
                    result = this->getNumValue() > value.getNumValue();
                else
                    error_message("Operator '>' cannot be used between JSON values of these types");
        }
        else{
            error_message("JSON types mismatch between values given for '>' operator");
        }
        string old_key = this->getKey();
        temp = new JSON_val((bool)result);
        temp->setKey(old_key);
        return *temp;
    }

    JSON_val &operator>=(JSON_val value){
        bool result;
        JSON_val *temp;
        if(this->getType() == value.getType()){
                if(checkIfNumber(*this))
                    result = this->getNumValue() >= value.getNumValue();
                else
                    error_message("Operator '>=' cannot be used between JSON values of these types");
        }
        else{
            error_message("JSON types mismatch between values given for '>=' operator");
        }
        string old_key = this->getKey();
        temp = new JSON_val((bool)result);
        temp->setKey(old_key);
        return *temp;
    }

    JSON_val &operator==(JSON_val value){
        bool result = true;
        JSON_val* temp;
        if(this->getType() == value.getType()){
                switch(this->getType()){
                    case ARR:
                        if(this->getArray().size() != value.getArray().size()){
                            result = false;
                            break;
                        }
                        for(int i = 0; i < this->getArray().size(); i++){
                            if(!(this->array[i] == value.array[i]).boolValue){ //lol...at this moment mental breakdown almost hit
                                result = false;
                                break;
                            }
                        }
                        break;
                    case OBJ:
                        if(this->getObject().size() != value.getObject().size()){
                            result = false;
                            break;
                        }
                        for(int i = 0; i < this->getObject().size(); i++){
                            if(!(this->object[i] == value.object[i]).boolValue){ //lol...at this moment mental breakdown almost hit
                                result = false;
                                break;
                            }
                        }
                        break;
                    case INTEGER:
                    case DOUBLE:
                        result = this->getNumValue() == value.getNumValue();
                        break;
                    case BOOLEAN:
                        result = this->getBoolValue() == value.getBoolValue();
                        break;
                    case STRING:
                        result = this->getStrValue() == value.getStrValue();
                        break;
                    default:
                        error_message("Type of JSON value given not recognized");
                        break;
                }
        }
        else{
            error_message("JSON types mismatch between values given for '>=' operator");
        }
        string old_key = this->getKey();
        temp = new JSON_val((bool)result);
        temp->setKey(old_key);
        return *temp;
    }
    
    JSON_val &operator!=(JSON_val value){
        bool result = false;
        JSON_val* temp;
        if(this->getType() == value.getType()){
                switch(this->getType()){
                    case ARR:
                        if(this->getArray().size() != value.getArray().size()){
                            result = true;
                            break;
                        }
                        for(int i = 0; i < this->getArray().size(); i++){
                            if((this->array[i] == value.array[i]).boolValue){ //lol...at this moment mental breakdown almost hit
                                result = true;
                                break;
                            }
                        }
                        break;
                    case OBJ:
                        if(this->getObject().size() != value.getObject().size()){
                            result = false;
                            break;
                        }
                        for(int i = 0; i < this->getObject().size(); i++){
                            if(!(this->object[i] == value.object[i]).boolValue){ //lol...at this moment mental breakdown almost hit
                                result = true;
                                break;
                            }
                        }
                        break;
                    case INTEGER:
                    case DOUBLE:
                        result = this->getNumValue() != value.getNumValue();
                        break;
                    case BOOLEAN:
                        result = this->getBoolValue() != value.getBoolValue();
                        break;
                    case STRING:
                        result = this->getStrValue() != value.getStrValue();
                        break;
                    default:
                        error_message("Type of JSON value given not recognized");
                        break;
                }
        }
        else{
            error_message("JSON types mismatch between values given for '>=' operator");
        }
        string old_key = this->getKey();
        temp = new JSON_val((bool)result);
        temp->setKey(old_key);
        return *temp;
    }

    JSON_val &operator!(){
        JSON_val* temp;
        if(this->getType() == BOOLEAN){
            temp = new JSON_val(!this->getBoolValue());
            temp->setKey(this->getKey());
        }
        else{
            error_message("Operator '!' cannot be used between JSON values of these types");
        }
        return *temp;
    }

    JSON_val &operator&&(JSON_val value){
        JSON_val* temp;
        if(this->getType() == value.getType()){
                if(this->getType() == BOOLEAN){
                    temp = new JSON_val(this->getBoolValue() && value.getBoolValue());
                    temp->setKey(this->getKey());
                }
                else
                    error_message("Operator '&&' cannot be used between JSON values of these types");
        }
        else{
            error_message("JSON types mismatch between values given for '&&' operator");
        }
        return *temp;
    }

    JSON_val &operator||(JSON_val value){
        JSON_val* temp;
        if(this->getType() == value.getType()){
                if(this->getType() == BOOLEAN){
                    temp = new JSON_val(this->getBoolValue() || value.getBoolValue());
                    temp->setKey(this->getKey());
                }
                else
                    error_message("Operator '||' cannot be used between JSON values of these types");
        }
        else{
            error_message("JSON types mismatch between values given for '||' operator");
        }
        return *temp;
    }
    /*
    //initial approach but we changed in order to be in accordance with mailing list clarification
    int size_of(JSON_val json){
        if(json.getType()  == ARR)
            return json.getArray().size();
        else if(json.getType()  == OBJ)
            return json.getObject().size();
        return 1;
    }

    string type_of(JSON_val json){
        return types[json.getType()];
    }
    //initial approach but we changed in order to be in accordance with PRINT needed from project description.
    bool is_empty(JSON_val json){

        if(json.getType()  == ARR)
            return (json.getArray().size() ==  0); 
        else if(json.getType()  == OBJ)
            return (json.getObject().size() ==0);
        return false;
    }

    bool has_key(JSON_val json, string key){
        if(json.getType()  == OBJ){
            for(int i = 0; i < json.getObject().size(); i++){
                if(json.object[i].getKey() == key)
                    return true;
            }
        }
        return false;
    }*/
    JSON_val &size_of(JSON_val json){
        int size = 1;
        if(json.getType()  == ARR)
            size = json.getArray().size();
        else if(json.getType()  == OBJ)
            size = json.getObject().size();
        JSON_val* temp = new JSON_val(size, "NaN");
        return *temp;
    }

    JSON_val &type_of(JSON_val json){
        JSON_val* temp = new JSON_val(types[json.getType()], "NaN");
        temp->arrayDisplay = true;
        return *temp;
    }

    JSON_val &is_empty(JSON_val json){
        bool result = false;
        if(json.getType()  == ARR)
            result = (json.getArray().size() ==  0); 
        else if(json.getType()  == OBJ)
            result = (json.getObject().size() ==0);
        JSON_val* temp = new JSON_val(result);
        temp->arrayDisplay = true;
        temp->setKey("NaN");
        return *temp;
    }

    JSON_val &has_key(JSON_val json, string key){
        bool result = false;
        if(json.getType()  == OBJ){
            for(int i = 0; i < json.getObject().size(); i++){
                if(json.object[i].getKey() == key){
                    result = true;
                }
            }
        }
        JSON_val* temp = new JSON_val(result);
        temp->arrayDisplay = true;
        temp->setKey("NaN");
        return *temp;
    }
};


/* TODO
 * 
 * 1) FIX APPEND SO THAT WE CAN APPEND MORE THAN ONE VALUES AT ONCE
 * 2) FIX OPERATOR+ REGARDING ARRAY AND OBJECT(LEAST LIKELY)
 * DONE --> 3) IMPLEMENT ALL LOGICAL AND COMPARISON OPERATORS (EAZZZZY)  
 * 4) FIX OPERATOR, SO THAT WE CAN PRINT MORE THAN ONE COMMA SEPARATED VALUES
 * DONE --> 5) FIX ARITHMETIC OPERATORS OVERLOADING SO THAT WE DON'T STORE RESULT TO *this 
 *              BUT TO DIFFERENT VALUE WE WILL RETURN LATER. 
 * DONE --> 6) CHECK FOR, AND HANDLE, MULTIPLE KEY DEFINITION IN OBJECT
 * 
 */
