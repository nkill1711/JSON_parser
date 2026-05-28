#include "lexer.h"
#include <memory>
#include <string>
#include <utility>
#include "parser.h"
int main(){
    std::string input = "{}";
    std::unique_ptr<Tokenizer>tokenzier = std::make_unique<Tokenizer>(input);
    std::unique_ptr<Parser>parser = std::make_unique<Parser>(std::move(tokenzier));
    return 0;
}