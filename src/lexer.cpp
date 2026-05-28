#include "lexer.h"
#include <algorithm>
#include <cctype>
#include <string>

constexpr int FALSE_LENGTH = 5;
constexpr int TRUE_LENGTH = 4;
constexpr int NULL_LENGTH = 4;

Tokenizer::Tokenizer(const std::string& str)
    : source(str), it(source.begin())
{
    while (it != source.end()) {
        char ch = *it;

        if (std::isspace(static_cast<unsigned char>(ch)) != 0) {
            ++it;
            continue;
        }
        //me dont like this 
        if(std::isdigit(static_cast<unsigned char>(ch)) != 0){
            std::string num;
            while (it != source.end() && std::isdigit(*it)) {
                num += *it;
                it++;
            }
            if (isAllDigits(num)) {
                tokens.push_back(Token::INTEGER);
            }
            else {
                tokens.push_back(Token::INVALID);
            }
            continue;
        }
        
        switch (ch) {
            case '{':
                tokens.push_back(Token::LEFTBRACE);
                ++it;
                break;

            case '}':
                tokens.push_back(Token::RIGHTBRACE);
                ++it;
                break;

            case '"':
                tokens.push_back(Token::STRING_OPENER);
                ++it;        
                stringParse(); 
                tokens.push_back(Token::STRING);
                tokens.push_back(Token::STRING_OPENER);
                break;
            case ':':
                tokens.push_back(Token::COLON);
                ++it;
                break;

            case ',':
                tokens.push_back(Token::COMMA);
                ++it;
                break;
            case '[':
                tokens.push_back(Token::LEFTBRACKET);
                ++it;
                break;
            case ']':
                tokens.push_back(Token::RIGHTBRACKET);
                ++it;
                break;
            
            default:
                if(source.substr(it - source.begin(), TRUE_LENGTH) == "true" ){
                    tokens.push_back(Token::TRUE);
                    it += TRUE_LENGTH;
                    continue;
                }
                if (source.substr(it - source.begin(), FALSE_LENGTH) == "false") {
                    it += FALSE_LENGTH;
                    tokens.push_back(Token::FALSE);
                    continue;
                }
                if (source.substr(it-source.begin(), NULL_LENGTH) == "null") {
                    it += NULL_LENGTH;
                    tokens.push_back(Token::NILL);
                    continue;
                }
                tokens.push_back(Token::INVALID);
                ++it;
                break;
        }
    }
}

void Tokenizer::stringParse() {
    while (it != source.end()) {
        if (*it == '"') {
            ++it;   
            return;
        }
        ++it;
    }
    tokens.push_back(Token::INVALID);
}

bool Tokenizer::isAllDigits(const std::string& str){
    return !str.empty() && std::all_of(str.begin(), str.end(), [](unsigned char c){return std::isdigit(c);});
}