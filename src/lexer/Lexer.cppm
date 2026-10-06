//
// Created by leonw on 25.09.2025.
//

export module lexer;
import std;
import token;

export class Lexer
{
private:
    std::string m_source;
    std::size_t m_current = 0;
    std::map<std::string, TokenType> m_keywords;
    std::size_t m_startLine = 1;
    std::size_t m_startColumn = 1;

    void advance();
    bool isAtEnd() const;
    [[nodiscard]] char getCurrentChar() const;
    char peek(std::size_t offset = 1) const;
    static bool isWhitespace(char c) ;

    void skipWhitespace();
    Token scanIdentifierOrKeyword();
    Token scanNumber();
    Token scanSymbol();

    Token scanString();

    static std::map<std::string, TokenType> buildKeywords();

public:
    explicit Lexer(std::string source) 
        : m_source(std::move(source))
        , m_keywords(buildKeywords())
    {
    }

    std::vector<Token> lex();
};
