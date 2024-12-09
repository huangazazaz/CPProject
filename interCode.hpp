
#ifndef CS323_COMPILERS_PROJECT3_INCLUDE_INTERCODE_HPP
#define CS323_COMPILERS_PROJECT3_INCLUDE_INTERCODE_HPP

#include <cstdint>
#include <string>

enum class OperandType
{
    VARIABLE, // v1,t1, etc...
    // RETURN VALUE
    CONSTANT,   // #0,#1, etc...
    ADDRESS,    // &y9,
    POINTER,    // *t9
    JUMP_LABEL, // label,function,GOTO,call
};

class Operand
{
public:
    OperandType operandEnum;

    Operand(OperandType operandEnum, std::string variName);

    Operand(OperandType operandEnum, int32_t value);

    explicit Operand(OperandType operandEnum);

    union
    {
        std::string variName;
        int32_t value{0};
        std::string jumpLabel;
    };

    void print() const;
};

enum class InterCodeType
{
    ASSIGN,
    ASSIGN_ADDRESS,
    ASSIGN_VALUE_IN_ADDRESS,
    COPY_VALUE_TO_ADDRESS,
    CALL,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    BOR,
    BAND,
    XOR,
    LABEL,
    GOTO,
    FUNCTION,
    RETURN,
    PARAM,
    ARG,
    READ,
    WRITE,
    FOR,
    DEC,
    IF_ELSE,
    CONSTANT,
    TERNARY
};

class InterCode
{
public:
    InterCodeType interCodeType;
    union
    {
        struct
        {
            Operand *left;
            Operand *right;
        } assign; // x := y,x := &y,x := *y, *x := y, x := CALL f, relop
        struct
        {
            Operand *result;
            Operand *op1;
            Operand *op2;
        } bioOp;                // x := y `+,-,*,/,%,|,&,^` z
        Operand *labelElement;  // LABEL,FUNCTION,GOTO
        Operand *SingleElement; // RETURN,PARAM,ARG,READ,WRITE,CONSTANT
        struct
        {
            Operand *pointer;
            int32_t size;
        } dec;
        struct
        {
            Operand *left;
            Operand *operation;
            Operand *right;
            Operand *if_label;
            // Operand *else_label;
        } ifElse{nullptr, nullptr, nullptr, nullptr};
    };

    InterCode() = default;

    explicit InterCode(InterCodeType interCodeType);

    ~InterCode() = default;

    void print() const;
};

#endif