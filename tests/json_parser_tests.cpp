#include "gtest/gtest.h"
#include "exceptions.h"
#include "lexer.h"
#include <memory>
#include <string>
#include <utility>
#include "parser.h"

TEST(TokenizerTest, BracesOnly) {
    std::string input = "{ }";
    Tokenizer tokenizer(input);

    ASSERT_EQ(tokenizer.tokens.size(), 2);
    EXPECT_EQ(tokenizer.tokens[0], Token::LEFTBRACE);
    EXPECT_EQ(tokenizer.tokens[1], Token::RIGHTBRACE);
}

TEST(TokenizerTest, withString) {
    std::string input = "{ \" sfdfsfd \" }";
    std::unique_ptr<Tokenizer>tokenizer = std::make_unique<Tokenizer>(input);

    ASSERT_EQ(tokenizer->tokens.size(), 5);
    EXPECT_EQ(tokenizer->tokens[0], Token::LEFTBRACE);
    EXPECT_EQ(tokenizer->tokens[1], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[2], Token::STRING);
    EXPECT_EQ(tokenizer->tokens[3], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[4], Token::RIGHTBRACE);
}

TEST(TokenizerTest, withINT) {
    std::string input = R"({ " sfdfsfd ": 12 })";
    std::unique_ptr<Tokenizer> tokenizer = std::make_unique<Tokenizer>(input);

    ASSERT_EQ(tokenizer->tokens.size(), 7);

    EXPECT_EQ(tokenizer->tokens[0], Token::LEFTBRACE);
    EXPECT_EQ(tokenizer->tokens[1], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[2], Token::STRING);
    EXPECT_EQ(tokenizer->tokens[3], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[4], Token::COLON);
    EXPECT_EQ(tokenizer->tokens[5], Token::INTEGER);
    EXPECT_EQ(tokenizer->tokens[6], Token::RIGHTBRACE);
}
TEST(TokenizerTest, withTRUE) {
    std::string input = R"({ " flag ": true })";
    std::unique_ptr<Tokenizer> tokenizer = std::make_unique<Tokenizer>(input);

    ASSERT_EQ(tokenizer->tokens.size(), 7);

    EXPECT_EQ(tokenizer->tokens[0], Token::LEFTBRACE);
    EXPECT_EQ(tokenizer->tokens[1], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[2], Token::STRING);
    EXPECT_EQ(tokenizer->tokens[3], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[4], Token::COLON);
    EXPECT_EQ(tokenizer->tokens[5], Token::TRUE);
    EXPECT_EQ(tokenizer->tokens[6], Token::RIGHTBRACE);
}
TEST(TokenizerTest, withFALSE) {
    std::string input = R"({ " flag ": false })";
    std::unique_ptr<Tokenizer> tokenizer = std::make_unique<Tokenizer>(input);

    ASSERT_EQ(tokenizer->tokens.size(), 7);

    EXPECT_EQ(tokenizer->tokens[0], Token::LEFTBRACE);
    EXPECT_EQ(tokenizer->tokens[1], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[2], Token::STRING);
    EXPECT_EQ(tokenizer->tokens[3], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[4], Token::COLON);
    EXPECT_EQ(tokenizer->tokens[5], Token::FALSE);
    EXPECT_EQ(tokenizer->tokens[6], Token::RIGHTBRACE);
}
TEST(TokenizerTest, withNULL) {
    std::string input = R"({ " value ": null })";
    std::unique_ptr<Tokenizer> tokenizer = std::make_unique<Tokenizer>(input);

    ASSERT_EQ(tokenizer->tokens.size(), 7);

    EXPECT_EQ(tokenizer->tokens[0], Token::LEFTBRACE);
    EXPECT_EQ(tokenizer->tokens[1], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[2], Token::STRING);
    EXPECT_EQ(tokenizer->tokens[3], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[4], Token::COLON);
    EXPECT_EQ(tokenizer->tokens[5], Token::NILL);
    EXPECT_EQ(tokenizer->tokens[6], Token::RIGHTBRACE);
}

TEST(TokenizerTest, withArrayValueSingle) {
    std::string input = R"({ " nums ": [1] })";
    std::unique_ptr<Tokenizer> tokenizer = std::make_unique<Tokenizer>(input);

    ASSERT_EQ(tokenizer->tokens.size(), 9);

    EXPECT_EQ(tokenizer->tokens[0], Token::LEFTBRACE);
    EXPECT_EQ(tokenizer->tokens[1], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[2], Token::STRING);
    EXPECT_EQ(tokenizer->tokens[3], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[4], Token::COLON);
    EXPECT_EQ(tokenizer->tokens[5], Token::LEFTBRACKET);
    EXPECT_EQ(tokenizer->tokens[6], Token::INTEGER);
    EXPECT_EQ(tokenizer->tokens[7], Token::RIGHTBRACKET);
    EXPECT_EQ(tokenizer->tokens[8], Token::RIGHTBRACE);
}
TEST(TokenizerTest, withArrayValueMultiple) {
    std::string input = R"({ " nums ": [1,2,3] })";
    std::unique_ptr<Tokenizer> tokenizer = std::make_unique<Tokenizer>(input);

    ASSERT_EQ(tokenizer->tokens.size(), 13);

    EXPECT_EQ(tokenizer->tokens[0], Token::LEFTBRACE);
    EXPECT_EQ(tokenizer->tokens[1], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[2], Token::STRING);
    EXPECT_EQ(tokenizer->tokens[3], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[4], Token::COLON);
    EXPECT_EQ(tokenizer->tokens[5], Token::LEFTBRACKET);
    EXPECT_EQ(tokenizer->tokens[6], Token::INTEGER);
    EXPECT_EQ(tokenizer->tokens[7], Token::COMMA);
    EXPECT_EQ(tokenizer->tokens[8], Token::INTEGER);
    EXPECT_EQ(tokenizer->tokens[9], Token::COMMA);
    EXPECT_EQ(tokenizer->tokens[10], Token::INTEGER);
    EXPECT_EQ(tokenizer->tokens[11], Token::RIGHTBRACKET);
    EXPECT_EQ(tokenizer->tokens[12], Token::RIGHTBRACE);
}

TEST(TokenizerTest, withObjectValueSingle) {
    std::string input = R"({ " obj ": { " a ": 1 } })";
    std::unique_ptr<Tokenizer> tokenizer = std::make_unique<Tokenizer>(input);

    ASSERT_EQ(tokenizer->tokens.size(), 13);

    EXPECT_EQ(tokenizer->tokens[0], Token::LEFTBRACE);
    EXPECT_EQ(tokenizer->tokens[1], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[2], Token::STRING);
    EXPECT_EQ(tokenizer->tokens[3], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[4], Token::COLON);
    EXPECT_EQ(tokenizer->tokens[5], Token::LEFTBRACE);
    EXPECT_EQ(tokenizer->tokens[6], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[7], Token::STRING);
    EXPECT_EQ(tokenizer->tokens[8], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[9], Token::COLON);
    EXPECT_EQ(tokenizer->tokens[10], Token::INTEGER);
    EXPECT_EQ(tokenizer->tokens[11], Token::RIGHTBRACE);
    EXPECT_EQ(tokenizer->tokens[12], Token::RIGHTBRACE);
}

TEST(TokenizerTest, withNestedObjectValue) {
    std::string input = R"({ " outer ": { " inner ": { " x ": 1 } } })";
    std::unique_ptr<Tokenizer> tokenizer = std::make_unique<Tokenizer>(input);

    ASSERT_EQ(tokenizer->tokens.size(), 19);

    EXPECT_EQ(tokenizer->tokens[0], Token::LEFTBRACE);
    EXPECT_EQ(tokenizer->tokens[1], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[2], Token::STRING);
    EXPECT_EQ(tokenizer->tokens[3], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[4], Token::COLON);
    EXPECT_EQ(tokenizer->tokens[5], Token::LEFTBRACE);
    EXPECT_EQ(tokenizer->tokens[6], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[7], Token::STRING);
    EXPECT_EQ(tokenizer->tokens[8], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[9], Token::COLON);
    EXPECT_EQ(tokenizer->tokens[10], Token::LEFTBRACE);
    EXPECT_EQ(tokenizer->tokens[11], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[12], Token::STRING);
    EXPECT_EQ(tokenizer->tokens[13], Token::STRING_OPENER);
    EXPECT_EQ(tokenizer->tokens[14], Token::COLON);
    EXPECT_EQ(tokenizer->tokens[15], Token::INTEGER);
    EXPECT_EQ(tokenizer->tokens[16], Token::RIGHTBRACE);
    EXPECT_EQ(tokenizer->tokens[17], Token::RIGHTBRACE); 
    EXPECT_EQ(tokenizer->tokens[18], Token::RIGHTBRACE); 
}



TEST(ParserTest,
     withStringColon){
        std::string input = R"({" sfdfd " : " hello" })";
        std::unique_ptr<Tokenizer>tokenzier = std::make_unique<Tokenizer>(input);
        std::unique_ptr<Parser>parser = std::make_unique<Parser>(std::move(tokenzier));
    }


TEST(ParserTest,
     withStringColonRecursive){
        std::string input = R"({"first name":"John Doe","city":"New York"})";
        std::unique_ptr<Tokenizer>tokenzier = std::make_unique<Tokenizer>(input);
        std::unique_ptr<Parser>parser = std::make_unique<Parser>(std::move(tokenzier));
    }

TEST(ParserTest, MissingColon) {
    std::string input = R"({"key" "value"})";
    std::unique_ptr<Tokenizer> tokenizer = std::make_unique<Tokenizer>(input);
    EXPECT_THROW({
        std::unique_ptr<Parser> parser = std::make_unique<Parser>(std::move(tokenizer));
    }, InvalidJsonException);
}

TEST(ParserTest, withIntegerValue) {
    std::string input = R"({"age": 25})";
    std::unique_ptr<Tokenizer> tokenizer = std::make_unique<Tokenizer>(input);
    std::unique_ptr<Parser> parser = std::make_unique<Parser>(std::move(tokenizer));
}

TEST(ParserTest, withBooleanTrue) {
    std::string input = R"({"isStudent": true})";
    std::unique_ptr<Tokenizer> tokenizer = std::make_unique<Tokenizer>(input);
    std::unique_ptr<Parser> parser = std::make_unique<Parser>(std::move(tokenizer));
}

TEST(ParserTest, withBooleanFalse) {
    std::string input = R"({"verified": false})";
    std::unique_ptr<Tokenizer> tokenizer = std::make_unique<Tokenizer>(input);
    std::unique_ptr<Parser> parser = std::make_unique<Parser>(std::move(tokenizer));
}

TEST(ParserTest, withNullValue) {
    std::string input = R"({"middleName": null})";
    std::unique_ptr<Tokenizer> tokenizer = std::make_unique<Tokenizer>(input);
    std::unique_ptr<Parser> parser = std::make_unique<Parser>(std::move(tokenizer));
}
TEST(ParserTest, withMixedValues) {
    std::string input =
        R"({"name":"Alice","age":30,"active":true,"city":null})";
    std::unique_ptr<Tokenizer> tokenizer = std::make_unique<Tokenizer>(input);
    std::unique_ptr<Parser> parser = std::make_unique<Parser>(std::move(tokenizer));
}

TEST(ParserTest, TrailingComma) {
    std::string input = R"({"a":1,})";
    std::unique_ptr<Tokenizer> tokenizer = std::make_unique<Tokenizer>(input);

    EXPECT_THROW({
        std::unique_ptr<Parser> parser =
            std::make_unique<Parser>(std::move(tokenizer));
    }, InvalidJsonException);
}

TEST(ParserTest, MissingValue) {
    std::string input = R"({"a":})";
    std::unique_ptr<Tokenizer> tokenizer = std::make_unique<Tokenizer>(input);

    EXPECT_THROW({
        std::unique_ptr<Parser> parser =
            std::make_unique<Parser>(std::move(tokenizer));
    }, InvalidJsonException);
}

TEST(ParserTest, MissingRightBrace) {
    std::string input = R"({"a":"b")";
    std::unique_ptr<Tokenizer> tokenizer = std::make_unique<Tokenizer>(input);

    EXPECT_THROW({
        std::unique_ptr<Parser> parser =
            std::make_unique<Parser>(std::move(tokenizer));
    }, InvalidJsonException);
}

