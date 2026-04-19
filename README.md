# C3PO Interpreter

C3PO is a small experimental interpreter for a custom programming language that I'm building from scratch.  
The main goal of this project is to **learn by doing** — to understand the full process of implementing a programming language, from lexing and parsing to AST generation and interpretation.

## Supported Syntax

### Variable Declarations & Arithmetic
```c
var x = 42;
var name = "Alice";
var result = 12 + 6 * 2;
```

### Print Statements
```c
print("Hello World");
print(result);
```

### Mixed Programs
```c
var greeting = "Hello ";
var name = "User";
print(greeting + name);

for {
    var a = 10;
    var b = 20;
    print(a * b);
}
```

## Supported Data Types

- **Integer** - `42`, `100`, `0`
- **String** - `"Hello"`, `"C3PO"`

## Example Output

**Input:**
```c
var a = 12 + 6 * 2;
print("The result is:");
print(a);
```

**Execution Output:**
```text
The result is:
24
```

## Roadmap

**Completed:**
- [x] Variable declarations (int, string)
- [x] String literals support
- [x] For loop blocks
- [x] Lexer and Parser
- [x] Arithmetic expressions (`+`, `-`, `*`, `/`)
- [x] Print statements
- [x] Actual interpretation/execution (Visitor Pattern)
- [x] Basic Symbol table (Variable tracking)

**Planned:**
- [ ] Conditional statements (`if`, `else`)
- [ ] Block scope management
- [ ] Function declarations and calls
- [ ] Arrays and data structures

## Goals

- Explore the internals of interpreters (lexing, parsing, AST, semantic analysis, and execution)
- Build a simple but functional language to experiment with new ideas
- Keep the code modular and easy to extend as the language evolves
- Learn C++ best practices through hands-on implementation

## Building the Project
```bash
mkdir build
cd build
cmake ..
make
./C3PO
```

## License

MIT License - See [LICENSE](LICENSE) file for details