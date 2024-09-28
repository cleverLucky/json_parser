#pragma once
#include <string>
#include "json.h"



namespace yazi {
    namespace json {
        class Parser{
            public:
            Parser();
            void load(const std::string & str);

            Json parse();

            private:
            void skip_white_space();
            char get_next_token();

            Json parse_null();
            Json parse_number();
            Json parse_bool();
            std::string parse_string();
            Json parse_array();
            Json parse_object();


            std::string m_str;
            int m_idx;
        };
    }
}