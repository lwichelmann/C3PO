export module token;
import std;

export enum class TokenType {
    IDENTIFIER, NUMBER, STRING, VAR, PRINT, FOR_LOOP, PLUS, MINUS,
    MULTIPLY, DIVIDE, EQUALS, TRUE_LITERAL, FALSE_LITERAL, IF, ELSE,
    SEMICOLON, LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    FUNCTION, UNKNOWN, END_OF_FILE, IMPORT
};

export class Token {
public:
    using Value = std::variant<int, std::string>;
private:
    TokenType m_type;
    Value m_value;
    std::size_t m_lineNumber;
    std::size_t m_columnNumber;
    std::size_t m_length;

public:
    Token(TokenType type, std::string value, std::size_t lineNumber, std::size_t columnNumber, std::size_t m_length);
    Token(TokenType type, int value, std::size_t lineNumber, std::size_t columnNumber, std::size_t m_length);
    explicit Token(TokenType type, std::size_t lineNumber, std::size_t columnNumber, std::size_t m_length);

    [[nodiscard]] TokenType getType() const;
    const Value& getValue() const;
    bool isLiteral() const;
    bool isOperator() const;
    [[nodiscard]] std::size_t getLineNumber() const;
    [[nodiscard]] std::size_t getColumnNumber() const;
    [[nodiscard]] std::size_t getLength() const;

    static std::string typeToString(TokenType type);
    friend std::ostream& operator<<(std::ostream& os, const Token& token);
};
