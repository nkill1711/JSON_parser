#include "parser.h"
#include "exceptions.h"
#include "lexer.h"
#include <iostream>
#include <memory>
#include <utility>

Parser::Parser(std::unique_ptr<Tokenizer> tokenizer)
    : tokenizer(std::move(tokenizer))
{
    it = this->tokenizer->tokens.begin();
    parseJson();

    if (it != this->tokenizer->tokens.end()) {
        throw InvalidJsonException(*it);
    }

    std::cout << "Valid JSON (recursive descent)\n";
}

Token Parser::lookahead() const {
    if (it == tokenizer->tokens.end()) {
        return Token::INVALID;
    }
    return *it;
}

void Parser::match(Token t) {
    if (lookahead() != t) {
        throw InvalidJsonException(lookahead());
    }
    ++it;
}

void Parser::parseJson(){ // json->obj
    parseObject();
}

void Parser::parseObject(){ // obj->LEFTBRACE obj_tail
    match(Token::LEFTBRACE);
    parseObjectTail();

}

void Parser::parseObjectTail(){ // obj_tail -> RIGHTBRACE | strings RIGHTBRACE
    if(lookahead() == Token::RIGHTBRACE){
        match(Token::RIGHTBRACE);
        return;
    }
    if(lookahead() == Token::STRING_OPENER){
        parseMembers();
        match(Token::RIGHTBRACE);
        return;
    }
    throw InvalidJsonException(lookahead());
}
void Parser::parseMembers(){ // parsemembers -> parseMember parseMembersTail
    parseMember();
    parseMembersTail();
}

void Parser::parseMembersTail() {
    if (lookahead() == Token::COMMA) {
        match(Token::COMMA);
        if (lookahead() == Token::RIGHTBRACE) {
            throw InvalidJsonException(Token::RIGHTBRACE);
        }
        parseMember();
        parseMembersTail();
    }
}


void Parser::parseMember(){ // member -> key COLON value
    parseKey();
    match(Token::COLON);
    parseValue();
}

void Parser::parseKey(){ // key -> string
    parseString();
}

void Parser::parseValue(){ // value -> string | INTEGER | NILL| TRUE| FALSE | array| object
    if (lookahead() == Token::STRING_OPENER) {
        parseString();
        return;
    }
    if (lookahead() == Token::INTEGER) {
        match(Token::INTEGER);
        return;
    }
    if(lookahead() == Token::LEFTBRACE){
        parseObject();
        return;
    }
    if (lookahead() == Token::LEFTBRACKET) {
        parseArray();
        return;
    }
    if(lookahead() == Token::NILL){
        match(Token::NILL);
        return;
    }
    if (lookahead() == Token::TRUE) {
        match(Token::TRUE);
        return;
    }
    if (lookahead() == Token::FALSE) {
        match(Token::FALSE);
        return;
    }
    throw InvalidJsonException(lookahead());
}
void Parser::parseArray(){//array -> LEFTBRACKET array_tail
    match(Token::LEFTBRACKET);
    parseArrayTail();
}

void Parser::parseArrayTail(){//array_tail -> RIGHTBRACKET | elements RIGHTBRACKET
    if(lookahead() == Token::RIGHTBRACKET){
        match(Token::RIGHTBRACKET);
        return;
    }
    parseElements();
    match(Token::RIGHTBRACKET);
}
void Parser::parseElements(){ // elements -> value elements_tail
    parseValue();
    parseElementsTail();
}
void Parser::parseElementsTail() {
    if (lookahead() == Token::COMMA) {
        match(Token::COMMA);
        if (lookahead() == Token::RIGHTBRACKET) {
            throw InvalidJsonException(Token::RIGHTBRACKET);
        }
        parseValue();
        parseElementsTail();
    }
}

void Parser::parseString(){ //string -> STRING_OPENER STRING STRING_OPENER
    match(Token::STRING_OPENER);
    match(Token::STRING);
    match(Token::STRING_OPENER);
}

