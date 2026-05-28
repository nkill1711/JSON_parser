#include "lexer.h"
#include <memory>

class Parser{
    /*
    Grammar (LL(1), recursive descent)

    json
        → object

    object
        → LEFTBRACE object_tail

    object_tail
        → RIGHTBRACE 
        | members RIGHTBRACE 

    members -> 
        member member_tail
    
    members_tail -> 
        COMMA member members_tail 
        | epsilon

    member 
        -> key colon value

    string
        → STRING_OPENER STRING STRING_OPENER

    key
        ->string
    
    value
        ->string
        | INTEGER
        | null
        | TRUE
        | FALSE
        | array
        | object
    
    array
    -> LEFTBRACKET array_tail

    array_tail
        -> RIGHTBRACKET
        | elements RIGHTBRACKET

    elements
        -> value elements_tail

    elements_tail
        -> COMMA value elements_tail
        | epsilon

    */
    private:
        std::unique_ptr<Tokenizer> tokenizer;
        std::vector<Token>::iterator it;
        void parseJson();        // json → object
        void parseObject();      // object → LEFTBRACE object_tail
        void parseObjectTail();  // object_tail → RIGHTBRACE | member RIGHTBRACE
        void parseMember();      // member -> key COLON value
        void parseMembers();   //  members -> member member_tail
        void parseMembersTail(); // memberstail -> COMMA member members_tail | epsilon
        void parseString();      // string → STRING_OPENER STRING STRING_OPENER
        void parseKey();        // key -> string
        void parseValue();     // value -> string | INTEGER | true | false | null
        void parseArray();           //array -> LEFTBRACKET array_tail
        void parseArrayTail();       // array_tail -> RIGHTBRACKET | elements RIGHTBRACKET
        void parseElements();        // elements -> value elements_tail
        void parseElementsTail();   // elements_tail -> COMMA value elemets_tail | epsilon
        Token lookahead() const;
        void match(Token t);
    public:
        Parser(std::unique_ptr<Tokenizer> tokenizer);

};