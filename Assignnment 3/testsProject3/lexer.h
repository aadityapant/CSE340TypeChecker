/*
 * Copyright (C) Rida Bazzi, 2016
 *
 * Do not share this file with anyone
 */
#ifndef __LEXER__H__
#define __LEXER__H__

#include <vector>
#include <string>

#include "inputbuf.h"

 // ------- token types -------------------

typedef enum {
    END_OF_FILE = 0, INT, REAL, BOO, TR, FA, IF, WHILE, SWITCH, CASE, PUBLIC, PRIVATE, NUM, REALNUM, NOT, PLUS, MINUS, MULT, DIV, GTEQ, GREATER, LTEQ, NOTEQUAL, LESS, LPAREN, RPAREN, EQUAL, COLON, COMMA, SEMICOLON, LBRACE, RBRACE, ID, ERROR, NONE, NOTVAR // TODO: Add labels for new token types here
} TokenType;
class Variable {
public:
    std::string name;
    TokenType data_type;
    Variable(std::string, TokenType);
    std::string type_name;
};
class Token {
public:
    void Print();

    std::string lexeme;
    TokenType token_type;
    int line_no;
    TokenType data_type;
    std::string type_name;
};

class LexicalAnalyzer {
public:
    Token GetToken();
    TokenType UngetToken(Token);
    LexicalAnalyzer();
    std::string control;
    std::vector<Token> expression;
    std::vector<std::vector<Token>> compExpress;
    std::vector<std::vector<Token>> mathExpress;
    std::vector<std::vector<Token>> asmtExpress;
    std::vector<std::vector<Token>> switchExpress;
    std::vector<std::vector<Token>> allExpress;
    std::vector<Variable> variable;
    bool searchVariable(std::string);
    void makeVarList();
    void addVar(Token var);
    void updateVarType(TokenType);
    void updateVarSolo(TokenType, std::string);
    void changeTypeName();
    void changeTypeSolo(std::string, std::string);
    TokenType returnVar(std::string);
    int varIndex(std::string);
    int line_no;

private:
    std::vector<Token> tokens;
    //std::String ifExpression;

    Token tmp;
    InputBuffer input;

    bool SkipSpace();
    bool SkipComments();
    bool IsKeyword(std::string);
    TokenType FindKeywordIndex(std::string);
    Token ScanIdOrKeyword();
    Token ScanNumber();
};

#endif  //__LEXER__H__
