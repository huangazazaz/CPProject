
#ifndef TYPE_HPP
#define TYPE_HPP
#include <string>
#include <variant>
#include <vector>
#include "node.hpp"

using std::string;
using std::variant;
using std::vector;

enum class CATEGORY
{
    PRIMITIVE,
    ARRAY,
    STRUCTURE,
    FUNCTION
};
enum PRIMI_VALUE
{
    Node_TYPE_VALUE = 0,
    ARRAY_POINTER_VALUE = 1,
    FieldList_POINTER_VALUE = 2
};

class Array;

class FieldList;

class Type
{
    using PRIMI = std::variant<Node_TYPE, Array *, FieldList *>;

public:
    string name;
    CATEGORY category = CATEGORY::PRIMITIVE;
    PRIMI type;
    Type *returnType = nullptr; // 存储返回值的类型
    // vector<Type *> parms;
    static Type *getPrimitiveType(Node_TYPE type);

    static Type *getPrimitiveINT();

    static Type *getPrimitiveFLOAT();

    static Type *getPrimitiveCHAR();

    static Type *getPrimitiveBOOLEAN();

    static Type *getPrimitiveWRONG();

    Type() = default;

    Type(string _name, CATEGORY _category, PRIMI _type);
};

class Array
{
public:
    Type *base;
    int size;

    Array(Type *base, int size);
};

class FieldList
{
public:
    string name;
    Type *type = nullptr;
    FieldList *next = nullptr;

    FieldList() = default;

    FieldList(string name, Type *type, FieldList *next);
};

#endif
