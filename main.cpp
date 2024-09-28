#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>
#include <string>
#include <fstream>


using namespace std;
#include "./json/json.h"
using namespace yazi::json;

int main(){
    // cout << "yazi json" << endl;

 /* Json v1;
    // Json v2 = true;
    Json v2(true);
    Json v3 = 123;
    Json v4 = 1.23;
    Json v5 = "clever lucky";
    
    bool b = v2;
    double c = v4;
    int d = v3;
    std::string s = v5;

    // cout << b << " " << c << " " << d << " " << s;

    Json arr;
    arr[0] = true;
    arr[1] = 123;

    arr.append(1.23);
    arr.append("hello kugou");

    std::cout << "test: " << (arr.find(0).str()) << " \n";

    bool nb = arr[0];
    int a = arr[1];
    double f = arr[2];
    string ss = arr[3];

    // for(auto it = arr.begin(); it != arr.end(); it++){
    //     std::cout << it->str() << "\n";
    // }
    
    // cout << "\n";
    // cout << nb << " " << a << " " << f << " " << ss << std::endl;

    // std::cout << "obj:\n";

    Json obj;
    obj["bool"] = true;
    obj["int"] = 123;
    obj["double"] = 1.23;
    obj["str"] = "clever lucky";
    obj["arr"] = arr;
    std::cout << "test: " << obj.find("int").str() << std::endl;
    obj.remove("int");
    std::cout << obj.str() << std::endl;

    obj.clear();
    */
    //std::cout << "lucky";
    // const std::string & str = "\"hello world  \u2006 \"";
    // const std::string & str1 = "[1, 2, 3, null, 1.23, true]";
    // const std::string & str2 = "{\"a\":[1, 2, 3, null, 1.23, true], \"b\":1}";
    // // const std::string & str2 = "{}";
    // Json v1,v2;
    // v1.parse(str1);
    // v2.parse(str2);
    // std::cout << v1.str();
   
    // std::cout << '\n' << v2.str();
    // std::cout << typeid(v).name();

    ifstream fin("./test.json");
    stringstream ss;
    ss << fin.rdbuf();

    const std::string & str = ss.str();
    Json v;
    v.parse(str);
    std::cout << v.str() << " " << std::endl; //<< (std::string)v["name"];
    return 0;
}