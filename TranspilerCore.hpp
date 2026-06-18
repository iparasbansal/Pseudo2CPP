#ifndef TRANSPILER_CORE_HPP
#define TRANSPILER_CORE_HPP

#include <algorithm>
#include <cctype>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

namespace transpiler {

enum class TokenType {
    FUNCTION, LET, FOR, FROM, TO, WHILE, IF, ELSE, RETURN,
    IDENTIFIER, NUMBER, 
    PLUS, MINUS, MULTIPLY, DIVIDE, MODULO,
    EQUALS, DOUBLE_EQUALS, NOT_EQUALS, LESS_THAN, GREATER_THAN, LESS_EQUALS, GREATER_EQUALS,
    LPAREN, RPAREN, LBRACE, RBRACE, LBRACKET, RBRACKET,
    COMMA, SEMICOLON,
    EOF_TOKEN, INVALID
};

struct Token {
    TokenType type;
    string value;
    int line;
};

class Lexer {
private:
    string src;
    size_t index = 0;
    int line = 1;
    
    char peek() const {
        if (index >= src.size()) return '\0';
        return src[index];
    }
    
    char get() {
        if (index >= src.size()) return '\0';
        char c = src[index++];
        if (c == '\n') line++;
        return c;
    }
public:
    Lexer(string src) : src(src) {}
    
    vector<Token> tokenize() {
        vector<Token> tokens;
        while (index < src.size()) {
            char c = peek();
            if (isspace(c)) {
                get();
                continue;
            }
            
            // Comment handling
            if (c == '/' && index + 1 < src.size() && src[index+1] == '/') {
                while (peek() != '\n' && peek() != '\0') get();
                continue;
            }
            
            // Numbers
            if (isdigit(c)) {
                string val = "";
                while (isdigit(peek())) val += get();
                tokens.push_back({TokenType::NUMBER, val, line});
                continue;
            }
            
            // Identifiers / Keywords
            if (isalpha(c) || c == '_') {
                string val = "";
                while (isalnum(peek()) || peek() == '_') val += get();
                
                TokenType type = TokenType::IDENTIFIER;
                if (val == "function") type = TokenType::FUNCTION;
                else if (val == "let") type = TokenType::LET;
                else if (val == "for") type = TokenType::FOR;
                else if (val == "from") type = TokenType::FROM;
                else if (val == "to") type = TokenType::TO;
                else if (val == "while") type = TokenType::WHILE;
                else if (val == "if") type = TokenType::IF;
                else if (val == "else") type = TokenType::ELSE;
                else if (val == "return") type = TokenType::RETURN;
                
                tokens.push_back({type, val, line});
                continue;
            }
            
            // Operators and punctuation
            char first = get();
            if (first == '(') tokens.push_back({TokenType::LPAREN, "(", line});
            else if (first == ')') tokens.push_back({TokenType::RPAREN, ")", line});
            else if (first == '{') tokens.push_back({TokenType::LBRACE, "{", line});
            else if (first == '}') tokens.push_back({TokenType::RBRACE, "}", line});
            else if (first == '[') tokens.push_back({TokenType::LBRACKET, "[", line});
            else if (first == ']') tokens.push_back({TokenType::RBRACKET, "]", line});
            else if (first == ',') tokens.push_back({TokenType::COMMA, ",", line});
            else if (first == ';') tokens.push_back({TokenType::SEMICOLON, ";", line});
            else if (first == '+') tokens.push_back({TokenType::PLUS, "+", line});
            else if (first == '-') tokens.push_back({TokenType::MINUS, "-", line});
            else if (first == '*') tokens.push_back({TokenType::MULTIPLY, "*", line});
            else if (first == '/') tokens.push_back({TokenType::DIVIDE, "/", line});
            else if (first == '%') tokens.push_back({TokenType::MODULO, "%", line});
            else if (first == '=') {
                if (peek() == '=') {
                    get();
                    tokens.push_back({TokenType::DOUBLE_EQUALS, "==", line});
                } else {
                    tokens.push_back({TokenType::EQUALS, "=", line});
                }
            }
            else if (first == '!') {
                if (peek() == '=') {
                    get();
                    tokens.push_back({TokenType::NOT_EQUALS, "!=", line});
                } else {
                    tokens.push_back({TokenType::INVALID, "!", line});
                }
            }
            else if (first == '<') {
                if (peek() == '=') {
                    get();
                    tokens.push_back({TokenType::LESS_EQUALS, "<=", line});
                } else {
                    tokens.push_back({TokenType::LESS_THAN, "<", line});
                }
            }
            else if (first == '>') {
                if (peek() == '=') {
                    get();
                    tokens.push_back({TokenType::GREATER_EQUALS, ">=", line});
                } else {
                    tokens.push_back({TokenType::GREATER_THAN, ">", line});
                }
            }
            else {
                string s(1, first);
                tokens.push_back({TokenType::INVALID, s, line});
            }
        }
        tokens.push_back({TokenType::EOF_TOKEN, "", line});
        return tokens;
    }
};

struct ASTNode {
    virtual ~ASTNode() = default;
    virtual string generate() const = 0;
};

struct ExprNode : public ASTNode {};

struct NumberNode : public ExprNode {
    string val;
    NumberNode(string val) : val(val) {}
    string generate() const override { return val; }
};

struct IdentifierNode : public ExprNode {
    string name;
    IdentifierNode(string name) : name(name) {}
    string generate() const override { return name; }
};

struct BinaryOpNode : public ExprNode {
    string op;
    shared_ptr<ExprNode> left;
    shared_ptr<ExprNode> right;
    BinaryOpNode(string op, shared_ptr<ExprNode> left, shared_ptr<ExprNode> right)
        : op(op), left(left), right(right) {}

    static int precedence(const string& op) {
        if (op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">=") {
            return 1;
        }
        if (op == "+" || op == "-") {
            return 2;
        }
        if (op == "*" || op == "/" || op == "%") {
            return 3;
        }
        return 0;
    }

    static bool isBinary(const shared_ptr<ExprNode>& node) {
        return dynamic_cast<BinaryOpNode*>(node.get()) != nullptr;
    }

    string generate() const override {
        auto formatLeft = left->generate();
        auto formatRight = right->generate();

        if (isBinary(left) && precedence(op) > precedence(dynamic_cast<BinaryOpNode*>(left.get())->op)) {
            formatLeft = "(" + formatLeft + ")";
        }

        if (isBinary(right) && precedence(op) >= precedence(dynamic_cast<BinaryOpNode*>(right.get())->op)) {
            formatRight = "(" + formatRight + ")";
        }

        return "(" + formatLeft + " " + op + " " + formatRight + ")";
    }
};

struct ArrayAccessNode : public ExprNode {
    string name;
    shared_ptr<ExprNode> index;
    ArrayAccessNode(string name, shared_ptr<ExprNode> index) : name(name), index(index) {}
    string generate() const override {
        return name + "[" + index->generate() + "]";
    }
};

struct FunctionCallNode : public ExprNode {
    string name;
    vector<shared_ptr<ExprNode>> args;
    FunctionCallNode(string name, vector<shared_ptr<ExprNode>> args) : name(name), args(args) {}
    string generate() const override {
        string res = name + "(";
        for(size_t i = 0; i < args.size(); i++) {
            if(i) res += ", ";
            res += args[i]->generate();
        }
        res += ")";
        return res;
    }
};

struct StmtNode : public ASTNode {};

struct BlockNode : public StmtNode {
    vector<shared_ptr<StmtNode>> statements;
    string generate() const override {
        string res = "{\n";
        for (const auto& stmt : statements) {
            res += "    " + stmt->generate() + "\n";
        }
        res += "}";
        return res;
    }
};

struct VarDeclNode : public StmtNode {
    string name;
    shared_ptr<ExprNode> initializer;
    VarDeclNode(string name, shared_ptr<ExprNode> initializer) : name(name), initializer(initializer) {}
    string generate() const override {
        return "auto " + name + " = " + initializer->generate() + ";";
    }
};

struct AssignNode : public StmtNode {
    shared_ptr<ExprNode> lhs;
    shared_ptr<ExprNode> rhs;
    AssignNode(shared_ptr<ExprNode> lhs, shared_ptr<ExprNode> rhs) : lhs(lhs), rhs(rhs) {}
    string generate() const override {
        return lhs->generate() + " = " + rhs->generate() + ";";
    }
};

struct ForNode : public StmtNode {
    string var;
    shared_ptr<ExprNode> start;
    shared_ptr<ExprNode> end;
    shared_ptr<BlockNode> body;
    ForNode(string var, shared_ptr<ExprNode> start, shared_ptr<ExprNode> end, shared_ptr<BlockNode> body)
        : var(var), start(start), end(end), body(body) {}
    string generate() const override {
        string loop = "for (int " + var + " = " + start->generate() + "; " + var + " <= " + end->generate() + "; " + var + "++) ";
        loop += body->generate();
        return loop;
    }
};

struct WhileNode : public StmtNode {
    shared_ptr<ExprNode> condition;
    shared_ptr<BlockNode> body;
    WhileNode(shared_ptr<ExprNode> condition, shared_ptr<BlockNode> body) : condition(condition), body(body) {}
    string generate() const override {
        return "while (" + condition->generate() + ") " + body->generate();
    }
};

struct IfNode : public StmtNode {
    shared_ptr<ExprNode> condition;
    shared_ptr<BlockNode> thenBlock;
    shared_ptr<BlockNode> elseBlock;
    IfNode(shared_ptr<ExprNode> condition, shared_ptr<BlockNode> thenBlock, shared_ptr<BlockNode> elseBlock = nullptr)
        : condition(condition), thenBlock(thenBlock), elseBlock(elseBlock) {}
    string generate() const override {
        string res = "if (" + condition->generate() + ") " + thenBlock->generate();
        if (elseBlock) {
            res += " else " + elseBlock->generate();
        }
        return res;
    }
};

struct ReturnNode : public StmtNode {
    shared_ptr<ExprNode> val;
    ReturnNode(shared_ptr<ExprNode> val) : val(val) {}
    string generate() const override {
        return "return " + val->generate() + ";";
    }
};

struct ExprStmtNode : public StmtNode {
    shared_ptr<ExprNode> expr;
    ExprStmtNode(shared_ptr<ExprNode> expr) : expr(expr) {}
    string generate() const override {
        return expr->generate() + ";";
    }
};

struct FunctionNode : public ASTNode {
    string name;
    vector<string> params;
    shared_ptr<BlockNode> body;
    FunctionNode(string name, vector<string> params, shared_ptr<BlockNode> body)
        : name(name), params(params), body(body) {}
    
    string generate() const override {
        string res = "";
        if (!params.empty()) {
            res += "template<";
            for(size_t i = 0; i < params.size(); i++) {
                if(i) res += ", ";
                res += "typename T_" + params[i];
            }
            res += ">\n";
        }
        res += "auto " + name + "(";
        for(size_t i = 0; i < params.size(); i++) {
            if (i) res += ", ";
            res += "T_" + params[i] + " " + params[i];
        }
        res += ") ";
        res += body->generate();
        return res;
    }
};

class Parser {
private:
    vector<Token> tokens;
    size_t index = 0;
    
    Token peek() const {
        if (index >= tokens.size()) return {TokenType::EOF_TOKEN, "", 0};
        return tokens[index];
    }
    
    Token consume(TokenType expected) {
        Token t = peek();
        if (t.type != expected) {
            throw runtime_error("Expected token of type " + to_string(static_cast<int>(expected)) + " but got '" + t.value + "' at line " + to_string(t.line));
        }
        index++;
        return t;
    }
    
    bool match(TokenType type) {
        if (peek().type == type) {
            index++;
            return true;
        }
        return false;
    }

    shared_ptr<ExprNode> parsePrimary() {
        if (match(TokenType::NUMBER)) {
            return make_shared<NumberNode>(tokens[index - 1].value);
        }
        if (match(TokenType::LPAREN)) {
            auto expr = parseExpression();
            consume(TokenType::RPAREN);
            return expr;
        }
        if (match(TokenType::IDENTIFIER)) {
            string name = tokens[index - 1].value;
            if (match(TokenType::LBRACKET)) {
                auto indexExpr = parseExpression();
                consume(TokenType::RBRACKET);
                return make_shared<ArrayAccessNode>(name, indexExpr);
            }
            if (match(TokenType::LPAREN)) {
                vector<shared_ptr<ExprNode>> args;
                if (peek().type != TokenType::RPAREN) {
                    do {
                        args.push_back(parseExpression());
                    } while (match(TokenType::COMMA));
                }
                consume(TokenType::RPAREN);
                return make_shared<FunctionCallNode>(name, args);
            }
            return make_shared<IdentifierNode>(name);
        }
        throw runtime_error("Unexpected token '" + peek().value + "' at line " + to_string(peek().line));
    }

    shared_ptr<ExprNode> parseMultiplicative() {
        auto left = parsePrimary();
        while (peek().type == TokenType::MULTIPLY || peek().type == TokenType::DIVIDE || peek().type == TokenType::MODULO) {
            Token opToken = peek();
            index++;
            auto right = parsePrimary();
            left = make_shared<BinaryOpNode>(opToken.value, left, right);
        }
        return left;
    }

    shared_ptr<ExprNode> parseAdditive() {
        auto left = parseMultiplicative();
        while (peek().type == TokenType::PLUS || peek().type == TokenType::MINUS) {
            Token opToken = peek();
            index++;
            auto right = parseMultiplicative();
            left = make_shared<BinaryOpNode>(opToken.value, left, right);
        }
        return left;
    }

    shared_ptr<ExprNode> parseComparison() {
        auto left = parseAdditive();
        while (peek().type == TokenType::DOUBLE_EQUALS || peek().type == TokenType::NOT_EQUALS ||
               peek().type == TokenType::LESS_THAN || peek().type == TokenType::GREATER_THAN ||
               peek().type == TokenType::LESS_EQUALS || peek().type == TokenType::GREATER_EQUALS) {
            Token opToken = peek();
            index++;
            auto right = parseAdditive();
            left = make_shared<BinaryOpNode>(opToken.value, left, right);
        }
        return left;
    }

    shared_ptr<ExprNode> parseExpression() {
        return parseComparison();
    }

    shared_ptr<BlockNode> parseBlock() {
        consume(TokenType::LBRACE);
        auto block = make_shared<BlockNode>();
        while (peek().type != TokenType::RBRACE && peek().type != TokenType::EOF_TOKEN) {
            block->statements.push_back(parseStatement());
        }
        consume(TokenType::RBRACE);
        return block;
    }

    shared_ptr<StmtNode> parseStatement() {
        if (match(TokenType::LET)) {
            Token id = consume(TokenType::IDENTIFIER);
            consume(TokenType::EQUALS);
            auto expr = parseExpression();
            return make_shared<VarDeclNode>(id.value, expr);
        }
        if (match(TokenType::RETURN)) {
            auto expr = parseExpression();
            return make_shared<ReturnNode>(expr);
        }
        if (match(TokenType::IF)) {
            consume(TokenType::LPAREN);
            auto cond = parseExpression();
            consume(TokenType::RPAREN);
            auto thenBlock = parseBlock();
            shared_ptr<BlockNode> elseBlock = nullptr;
            if (match(TokenType::ELSE)) {
                elseBlock = parseBlock();
            }
            return make_shared<IfNode>(cond, thenBlock, elseBlock);
        }
        if (match(TokenType::WHILE)) {
            consume(TokenType::LPAREN);
            auto cond = parseExpression();
            consume(TokenType::RPAREN);
            auto body = parseBlock();
            return make_shared<WhileNode>(cond, body);
        }
        if (match(TokenType::FOR)) {
            Token var = consume(TokenType::IDENTIFIER);
            consume(TokenType::FROM);
            auto start = parseExpression();
            consume(TokenType::TO);
            auto end = parseExpression();
            auto body = parseBlock();
            return make_shared<ForNode>(var.value, start, end, body);
        }
        
        auto expr = parseExpression();
        if (match(TokenType::EQUALS)) {
            auto rhs = parseExpression();
            return make_shared<AssignNode>(expr, rhs);
        }
        return make_shared<ExprStmtNode>(expr);
    }

    shared_ptr<FunctionNode> parseFunction() {
        consume(TokenType::FUNCTION);
        Token id = consume(TokenType::IDENTIFIER);
        consume(TokenType::LPAREN);
        vector<string> params;
        if (peek().type != TokenType::RPAREN) {
            do {
                Token p = consume(TokenType::IDENTIFIER);
                params.push_back(p.value);
            } while (match(TokenType::COMMA));
        }
        consume(TokenType::RPAREN);
        auto body = parseBlock();
        return make_shared<FunctionNode>(id.value, params, body);
    }

public:
    Parser(vector<Token> tokens) : tokens(tokens) {}
    
    vector<shared_ptr<ASTNode>> parse() {
        vector<shared_ptr<ASTNode>> program;
        while (peek().type != TokenType::EOF_TOKEN) {
            if (peek().type == TokenType::FUNCTION) {
                program.push_back(parseFunction());
            } else {
                program.push_back(parseStatement());
            }
        }
        return program;
    }
};

class TranspilerCore {
public:
    static bool containsStructuredCode(const string& input) {
        return (input.find("function ") != string::npos && input.find("{") != string::npos) ||
               (input.find("let ") != string::npos) ||
               (input.find("for ") != string::npos && input.find("from ") != string::npos);
    }

    static string transpile(const string& pseudocode) {
        try {
            Lexer lexer(pseudocode);
            auto tokens = lexer.tokenize();
            
            for(const auto& t : tokens) {
                if (t.type == TokenType::INVALID) {
                    return "// [Transpilation Error] Invalid token '" + t.value + "' at line " + to_string(t.line) + "\n";
                }
            }
            
            Parser parser(tokens);
            auto ast = parser.parse();
            
            string cppCode = "";
            for (const auto& node : ast) {
                cppCode += node->generate() + "\n";
            }
            return cppCode;
        } catch (const exception& e) {
            return string("// [Transpilation Error] ") + e.what() + "\n";
        }
    }
};

} // namespace transpiler

#endif
