
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>

#include "Parser.h"
#include "json.h"


using namespace yazi::json;

Json::Json() : m_type(Json::json_null){
    // std::cout << "m_type:" << this->m_type;
}

Json::Json(bool value) : m_type(json_bool){
    m_value.m_bool = value;
    // std::cout << value << " " << m_value.m_bool;
    // std::cout << "m_type:" << this->m_type;
}

Json::Json(int value) : m_type(json_int){
    m_value.m_int = value;
}

Json::Json(double value) : m_type(json_double){
    m_value.m_double = value;
}

Json::Json(const char * value) : m_type(json_string){
    m_value.m_string = new std::string(value);
}

Json::Json(const std::string & value) : m_type(json_string){
    m_value.m_string = new std::string(value);
}

Json::Json(Type type) : m_type(type){
    switch (m_type) {
        case json_null:
            break;
        case json_int:
            m_value.m_int = 0;
            break;
        case json_bool:
            m_value.m_bool = false;
            break;
        case json_double:
            m_value.m_double = 0.0;
            break;
        case json_string:
            m_value.m_string = new std::string("");
            break;
        case json_array:
            m_value.m_array = new std::vector<Json>;
            break;
        case json_object:
            m_value.m_object = new std::map<std::string, Json>;
            break;
        default:
            break;
    }
}

Json::Json(const Json & other){
    clear();
    copy(other);
}

Json::operator bool(){
    if(m_type != json_bool){
        throw new std::logic_error("type error, not bool value");
    }
    return m_value.m_bool;
}


Json::operator int(){
    if(m_type != json_int){
        throw new std::logic_error("type error, not int value");
    }
    return m_value.m_int;
}


Json:: operator double(){
    if(m_type != json_double){
        throw new std::logic_error("type error, not double value");
    }
    return m_value.m_double;
}


Json::operator std::string(){
    if(m_type != json_string){
        throw new std::logic_error("type error, not string value");
    }
    return * (m_value.m_string);
}

Json & Json:: operator [] (int index){
    if(m_type != json_array){
        m_type = json_array;
        m_value.m_array = new std::vector<Json>();

    }
    if(index < 0){
        throw new std::logic_error("array[] index < 0");
    }
    int size = (m_value.m_array)->size();
    if(index >= size){
        for(int i = size; i <= index; i++){
            (m_value.m_array)->push_back(Json());
        } 
    }
    return (m_value.m_array)->at(index);
}


void Json::append(const Json & other){
    if(m_type != json_array){
        clear();
        m_type = json_array;
        m_value.m_array = new std::vector<Json>();
    }
    (m_value.m_array)->push_back(other);
}

std::string Json::str() const{
    std::stringstream ss;
    switch (m_type) {
        case json_null:
            ss << "null";
            break;
        case json_bool:
            if (m_value.m_bool) {
                ss << "true";
            }
            else ss << "false";
            break;
        case json_int:
            ss << m_value.m_int;
            break;
        case json_double:
            ss << m_value.m_double;
            break;
        case json_string:
            ss << "\"" << * (m_value.m_string) << "\"";
            break;
        case json_array:
            ss << "[";
            for(auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); it++){
                if (it != (m_value.m_array)->begin()){
                    ss << ",";
                }
                ss << it->str();
            }
            ss << "]";
            break;
        case json_object:
            ss << "{";
            for(auto it = (m_value.m_object)->begin(); it != (m_value.m_object)->end(); it++){
                if (it != (m_value.m_object)->begin()){
                    ss << ",";
                }
                ss << "\"" << it->first << "\"" << ":" << it->second.str();
            }
            ss << "}";
            break;
        default:
            break;
    }
    return ss.str();
}

Json & Json::operator [] (const char * key){
    std::string name(key);
    return (*(this))[name]; //调用下面的一个函数
}


Json & Json::operator [] (const std::string & key){
    // auto it = m_value.m_object->find(key);
    // if(it !=)
    if(m_type != json_object){
        clear();
        m_type = json_object;
        m_value.m_object = new std::map<std::string, Json>();
    }
    return (*(m_value.m_object))[key];
}

void Json::operator = (const Json & other){
    clear();
    copy(other);
}

void Json::copy(const Json & other){
    m_type = other.m_type;
    switch (m_type) {
        case json_null:
            break;
        case json_int:
            m_value.m_int = other.m_value.m_int;
            break;
        case json_bool:
            m_value.m_bool = other.m_value.m_bool;
            break;
        case json_double:
            m_value.m_double = other.m_value.m_double;
            break;
        case json_string:
            m_value.m_string = other.m_value.m_string;
            break;
        case json_array:
            m_value.m_array = other.m_value.m_array;
            break;
        case json_object:
            m_value.m_object = other.m_value.m_object;
            break;
        default:
            break;
    }
}


void Json::clear(){
    switch (m_type) {
        case json_null:
            break;
        case json_bool:
            m_value.m_bool = false;
            break;
        case json_int:
            m_value.m_int = 0;
            break;
        case json_double:
            m_value.m_double = 0.0;
            break;
        case json_string:
            delete m_value.m_string;
            break;
        case json_array:
            for(auto it = (m_value.m_array)->begin(); it != (m_value.m_array)->end(); it++){
                it->clear();
            }
            delete m_value.m_array;
            break;
        case json_object:
            for(auto it = (m_value.m_object)->begin(); it != (m_value.m_object)->end(); it++){
                    (it->second).clear();
                }
                delete m_value.m_object;
            break;
        default:
            break;
    }
    m_type = json_null;
}

bool Json::operator == (const Json & other) const{
    if (m_type != other.m_type) {
        return false;
    }
    switch (m_type) {
        case json_null:
            return true;
        case json_int:
            return m_value.m_int == other.m_value.m_int;
        case json_double:
            return m_value.m_double == other.m_value.m_double;
        case json_string:
            return *(m_value.m_string) == *(other.m_value.m_string);
        case json_bool:
            return m_value.m_bool == other.m_value.m_bool;
        case json_array:
            return *(m_value.m_array) == *(other.m_value.m_array);
        case json_object:
            return *(m_value.m_object) == *(other.m_value.m_object);
        default:
            break;
    }
}


bool Json::operator != (const Json & other) const{
    return !(*(this) == other);
}

bool Json::asBool() const{
    if(m_type != json_bool){
        throw new std::logic_error("type error, not bool value");
    }
    return m_value.m_bool;
}


int Json::asInt() const{
    if(m_type != json_int){
        throw new std::logic_error("type error, not int value");
    }
    return m_value.m_int;
}


double Json::asDouble() const{
    if(m_type != json_double){
        throw new std::logic_error("type error, not double value");
    }
    return m_value.m_double;
}


std::string Json::asString() const{
    if(m_type != json_string){
        throw new std::logic_error("type error, not str value");
    }
    return * (m_value.m_string);
}

Json Json::find(int index){
    if(m_type != json_array){
        throw new std::logic_error("error type, need array type");
    }
    int size = (m_value.m_array)->size();
    if (index < 0 || index >= size) {
        throw new std::logic_error("out of range");
    }
    return (*((m_value.m_array)->begin() + index));
}
Json Json::find(const char * key){
    std::string name(key);
    return Json::find(name);
}

Json Json::find(const std::string & key){
    if(m_type != json_object){
        throw new std::logic_error("error type, need str/char * type");
    }
    return (m_value.m_object)->find(key)->second;
}

void Json::remove(int index){
    if(m_type != json_array){
        throw new std::logic_error("error type, need array type");
    }
    int size = (m_value.m_array)->size();
    if (index < 0 || index >= size) {
        throw new std::logic_error("out of range");
    }
    (m_value.m_array)->at(index).clear();
    (m_value.m_array)->erase((m_value.m_array)->begin() + index);
}


void Json::remove(const char * key){
    std::string name(key);
    Json::remove(name);
}

void Json::remove(const std::string & key){
    auto it = (m_value.m_object)->find(key);
    if(it == (m_value.m_object)->end()) return;
    (*(m_value.m_object))[key].clear();
    (m_value.m_object)->erase(key);
}

void Json::parse(const std::string & str){
    Parser p;
    p.load(str);
    *this = p.parse();
}