#include <iterator>
#include "visitSyntaxTree.hpp"
#include "semanticError.hpp"
#include "scopeStack.hpp"

static unordered_map<string, Node_TYPE> snt = {
    {string("int"), Node_TYPE::INT},
    {string("float"), Node_TYPE::FLOAT},
    {string("char"), Node_TYPE::CHAR},
    {string("bool"), Node_TYPE::BOOLEAN},
    {string("wrong"), Node_TYPE::BOOLEAN},
};
static unordered_map<Node_TYPE, string> tns = {
    {Node_TYPE::INT, string("INT")},
    {Node_TYPE::FLOAT, string("FLOAT")},
    {Node_TYPE::CHAR, string("CHAR")},
    {Node_TYPE::BOOLEAN, string("BOOLEAN")},
    {Node_TYPE::WRONG, string("WRONG")},
};

auto getArrayDemensionAndType(Type *_type)
{
    vector<int> demensions;
    Type *tempField = _type;
    while (tempField != nullptr && tempField->type.index() == ARRAY_POINTER_VALUE)
    {
        auto tempArray = std::get<Array *>(tempField->type);
        tempField = tempArray->base;
        demensions.push_back(tempArray->size);
    }
    return std::tuple(demensions, tempField);
};

string categoryAndTypeNameFromType(Type *type)
{
    static const unordered_map<CATEGORY, string> ca_st = {
        {CATEGORY::PRIMITIVE, ""},
        {CATEGORY::ARRAY, "array"},
        {CATEGORY::STRUCTURE, "struct"},
        {CATEGORY::FUNCTION, "function"}};
    const string &categoryStr = ca_st.at(type->category);
    string typeName;
    switch (type->category)
    {
    case CATEGORY::PRIMITIVE:
    {
        typeName = tns[std::get<Node_TYPE>(type->type)];
        break;
    }
    case CATEGORY::ARRAY:
    case CATEGORY::STRUCTURE:
    case CATEGORY::FUNCTION:
    {
        typeName = scopeStack.lookup(type->name)->name;
        // typeName = symbolTable[type->name]->name;
        break;
    }
    }
    return string("").append(categoryStr).append(" ").append(typeName);
}

void idToExp(Node *exp, Node *id)
{
    if (exp->name != "Exp" || id->name != "ID")
    {
        return;
    }
    exp->type = scopeStack.lookup(std::get<string>(id->value));
    // exp->type = symbolTable[std::get<string>(id->value)];
}

/*
 * When Bison detect a Def, enter this function
 * */
void defVisit(Node *node)
{
    if (node->get_nodes(0, 0)->nodes.empty())
    {
        defPureTypeVisit(node);
    }
    else
    {
        defStructTypeVisit(node);
    }
}

string getStrValueFromVarDec(Node *varDec)
{
    while (varDec->name == "VarDec")
    {
        varDec = varDec->get_nodes(0);
    }
    return std::get<string>(varDec->value);
}

/*
 * Specifier is Type
DecList
  Dec
    VarDec
      ID: code
 * */
string getStrValueFromDecList(Node *node)
{
    if (node->name == "DecList")
    {
        Node *VarDec = node->get_nodes(0, 0);
        return getStrValueFromVarDec(VarDec);
    }
    else
    {
        std::cerr << "Input Node Wrong\n";
        return "";
    }
}

string getStrValueFromExtDecList(Node *node)
{
    if (node->name == "ExtDecList")
    {
        Node *VarDec = node->get_nodes(0);
        return getStrValueFromVarDec(VarDec);
    }
    else
    {
        std::cerr << "Input Node Wrong\n";
        return "";
    }
}

/*
 * Specifier is Type
Def
  Specifier
    TYPE: Node_Type::
  DecList
    Dec
      VarDec
        ID: code
  SEMI
  // DO not forget VarDec can contain array
 * */

void defPureTypeVisit(Node *node)
{
    Node *decList = node->get_nodes(1);
    string name = getStrValueFromDecList(decList);
    auto _type = snt[std::get<string>(node->get_nodes(0, 0)->value)];
    do
    {
        // if (symbolTable.count(name) != 0)
        if (scopeStack.lookup(name) != 0)
        {
            variableRedefined(std::get<int>(node->value), name);
        }
        const auto &PrimitiveType = Type::getPrimitiveType(_type);
        if (decList->get_nodes(0, 0)->nodes.size() == 1)
        {
            scopeStack.scopes.back()[name] = PrimitiveType;
            // symbolTable[name] = PrimitiveType;
            if (decList->get_nodes(0)->nodes.size() == 3)
            {
                // checkTypeMatchType(symbolTable[std::get<string>(decList->get_nodes(0, 0, 0)->value)],
                //                    decList->get_nodes(0, 2)->type, std::get<int>(node->value), nonMatchTypeBothSide);
                checkTypeMatchType(scopeStack.lookup(std::get<string>(decList->get_nodes(0, 0, 0)->value)),
                                   decList->get_nodes(0, 2)->type, std::get<int>(node->value), nonMatchTypeBothSide);
            }
        }
        else
        {
            scopeStack.scopes.back()[name] = new Type(name, CATEGORY::ARRAY,
                                                      getArrayFromVarDec(decList->get_nodes(0, 0), PrimitiveType));
            // symbolTable[name] = new Type(name, CATEGORY::ARRAY,
            //                              getArrayFromVarDec(decList->get_nodes(0, 0), PrimitiveType));
            if (decList->get_nodes(0)->nodes.size() == 3)
            {
                nonMatchTypeBothSide(std::get<int>(decList->value));
            }
        }
        if (decList->nodes.size() == 1)
        {
            break;
        }
        decList = decList->get_nodes(2);
        name = getStrValueFromDecList(decList);
    } while (true);
}

/*
 * Specifier is StructSpecifier
Def (9)
  Specifier (9)
    StructSpecifier (9)
      STRUCT
      ID: my_struct
  DecList (9)
    Dec (9)
      VarDec (9)
        ID: obj
  SEMI
 * */
void defStructTypeVisit(Node *node)
{
    Node *decList = node->get_nodes(1);
    string variableName = getStrValueFromDecList(decList);
    string structName = std::get<string>(node->get_nodes(0, 0, 1)->value);

    if (scopeStack.lookup(structName) == nullptr)
    // if (symbolTable.count(structName) == 0)
    {
        structNoDefinition(std::get<int>(node->value), structName);
        // structNotDefine Do not need to consider
    }
    else
    {
        do
        {
            // if (symbolTable.count(variableName) != 0)
            if (scopeStack.lookup(variableName) != nullptr)
            {
                // We need to add another scope for struct
                variableRedefined(std::get<int>(node->value), variableName);
            }
            if (decList->get_nodes(0, 0)->nodes.size() == 1)
            {
                // Type* temp = scopeStack.lookup(structName);
                scopeStack.scopes.back()[variableName] = scopeStack.lookup(structName);
                // symbolTable[variableName] = symbolTable[structName];
                // struct Variable without array
            }
            else
            {
                // struct Variable with array
                scopeStack.scopes.back()[variableName] = new Type(variableName, CATEGORY::ARRAY,
                                                                  getArrayFromVarDec(decList->get_nodes(0, 0),
                                                                                     scopeStack.lookup(structName)));
                // symbolTable[variableName] = new Type(variableName, CATEGORY::ARRAY,
                //                                      getArrayFromVarDec(decList->get_nodes(0, 0),
                //                                                         symbolTable[structName]));
            }
            if (decList->get_nodes(0)->nodes.size() == 3)
            {
                // checkTypeMatchType(symbolTable[variableName], decList->get_nodes(0, 2)->type,
                //                    std::get<int>(decList->value),
                //                    nonMatchTypeBothSide);
                checkTypeMatchType(scopeStack.lookup(variableName), decList->get_nodes(0, 2)->type,
                                   std::get<int>(decList->value),
                                   nonMatchTypeBothSide);
            }
            if (decList->nodes.size() == 1)
            {
                return;
            }
            decList = decList->get_nodes(2);
            variableName = getStrValueFromDecList(decList);
        } while (true);
    }
}

Array *getArrayFromVarDec(Node *node, Type *type)
{
    if (node == nullptr || node->name != "VarDec")
    {
        return nullptr;
    }
    else
    {
        int size = std::get<int>(node->get_nodes(2)->value);
#ifdef DEBUG
        node->print();
#endif
        if (node->get_nodes(0)->nodes.size() == 1)
        {
            return new Array(type, size);
        }
        else
        {
            return new Array(new Type("", CATEGORY::ARRAY,
                                      getArrayFromVarDec(node->get_nodes(0),
                                                         type)),
                             size);
        }
    }
}

/*
ExtDef
  Specifier // this can be type or structSpecifier
    TYPE: int
  ExtDecList
    VarDec
      ID: global
  SEMI*/
void extDefVisit_SES(Node *node)
{
    if (node->get_nodes(0, 0)->nodes.empty())
    {
        // global puretype variables
        extDefVisit_SES_PureType(node);
    }
    else
    {
        // global struct def and varis
        extDefVisit_SES_StructType(node);
        // inside is StructSpecifier
    }
#ifdef DEBUG
    node->print(0);
#endif
}

void extDefVisit_SES_PureType(Node *node)
{
    Node *extDecList = node->get_nodes(1);
    string name = getStrValueFromExtDecList(extDecList);
    auto _type = snt[std::get<string>(node->get_nodes(0, 0)->value)];
    do
    {
        // if (symbolTable.count(name) != 0)
        if (scopeStack.lookup(name) != nullptr)
        {
            variableRedefined(std::get<int>(node->value), name);
        }
        const auto &PrimitiveType = Type::getPrimitiveType(_type);
        if (extDecList->get_nodes(0, 0)->nodes.empty())
        {
            scopeStack.scopes.back()[name] = PrimitiveType;
            // symbolTable[name] = PrimitiveType;
        }
        else
        {

            scopeStack.scopes.back()[name] = new Type(name, CATEGORY::ARRAY,
                                                      getArrayFromVarDec(extDecList->get_nodes(0),
                                                                         PrimitiveType));
            // symbolTable[name] = new Type(name, CATEGORY::ARRAY,
            //                              getArrayFromVarDec(extDecList->get_nodes(0),
            //                                                 PrimitiveType));
        }
        if (extDecList->nodes.size() == 1)
        {
            break;
        }
        extDecList = extDecList->get_nodes(2);
        name = getStrValueFromExtDecList(extDecList);
    } while (true);
}

void extDefVisit_SES_StructType(Node *node)
{
    string structName = std::get<string>(node->get_nodes(0, 0, 1)->value);
    Node *extDecList = node->get_nodes(1);
    string variableName = getStrValueFromExtDecList(extDecList);

    extDefVisit_SS(node);

    // if (symbolTable.count(structName) == 0)
    if (scopeStack.lookup(structName) == nullptr)
    {
        structNoDefinition(std::get<int>(node->value), structName);
        // but this do not need to print, it use to happen is extDefVisit_SS;
        // do not match there
        // structRedefined(std::get<int>(node->value), structName);
    }
    else
    {
        do
        {
            // if (symbolTable.count(variableName) != 0)
            if (scopeStack.lookup(variableName) != 0)
            {
                variableRedefined(std::get<int>(node->value), variableName);
            }
            if (extDecList->get_nodes(0)->nodes.size() == 1)
            {
                // Struct with variable definition
                scopeStack.scopes.back()[variableName] = scopeStack.lookup(structName);
                // symbolTable[variableName] = symbolTable[structName];
            }
            else
            {
                // Struct with variable definition - with Array
                // symbolTable[variableName] = new Type(variableName, CATEGORY::ARRAY,
                //                                      getArrayFromVarDec(extDecList->get_nodes(0),
                //                                                         symbolTable[structName]));
                scopeStack.scopes.back()[variableName] = new Type(variableName, CATEGORY::ARRAY,
                                                                  getArrayFromVarDec(extDecList->get_nodes(0),
                                                                                     scopeStack.lookup(structName)));
            }
            if (extDecList->nodes.size() == 1)
            {
                return;
            }
            extDecList = extDecList->get_nodes(2);
            variableName = getStrValueFromExtDecList(extDecList);
        } while (true);
    }
}

FieldList *getFiledListFromNodesVector(const vector<Node *> &vec)
{
    if (vec.empty())
    {
        return nullptr;
    }
    vector<FieldList *> fieldVec;
    for (const auto &item : vec)
    {
        const auto name = getStrValueFromDecList(item);

        // fieldVec.push_back(new FieldList{name, symbolTable[name], nullptr});
        fieldVec.push_back(new FieldList{name, scopeStack.scopes.back()[name], nullptr});

        // symbolTable.erase(name);
        scopeStack.scopes.back().erase(name);
    }
    for (auto i = static_cast<size_t>(0); i < vec.size() - 1; ++i)
    {
        fieldVec[i]->next = fieldVec[i + 1];
    }
    return fieldVec.front();
}

/*
ExtDef (2)
  Specifier (2)
    StructSpecifier (2)
      STRUCT
      ID: my_struct
      LC
      DefList (4)
        Def (4)
          Specifier (4)
            TYPE: int
          DecList (4)
            Dec (4)
              VarDec (4)
                ID: code
          SEMI
      RC
  SEMI
*/
void extDefVisit_SS(Node *node)
{
    // definition of Struct
    // std::cout << "SS\n";
    if (node->get_nodes(0, 0)->name == "TYPE")
    {
        // ignore the pureType's def likt `float;`
        return;
    }
    string name = std::get<string>(node->get_nodes(0, 0, 1)->value); // this is structName
    vector<Node *> namesofFileds;
    getNamesOfDefList(node, namesofFileds);
    auto fieldListOfType = getFiledListFromNodesVector(namesofFileds);
    // if (symbolTable.count(name) != 0)
    if (scopeStack.lookup(name) != nullptr)

    {
        structRedefined(std::get<int>(node->value), name);
    }
    else
    {
        scopeStack.scopes.back()[name] = new Type{name, CATEGORY::STRUCTURE, fieldListOfType};
        // symbolTable[name] = new Type{name, CATEGORY::STRUCTURE, fieldListOfType};
    }
#ifdef DEBUG
    node->print(0);
#endif
}

void getNamesOfDefList(Node *node, vector<Node *> &namesofFileds)
{
    if (!node->get_nodes(0, 0, 3)->nodes.empty())
    {
        auto nodeofField = node->get_nodes(0, 0, 3);
        while (nodeofField != nullptr && !nodeofField->nodes.empty() && nodeofField->name == "DefList")
        {
            auto declistNode = nodeofField->get_nodes(0, 1);
            while (declistNode != nullptr && declistNode->name == "DecList")
            {
                namesofFileds.push_back(declistNode);
                if (declistNode->nodes.size() == 3)
                {
                    declistNode = declistNode->get_nodes(2);
                }
                else
                {
                    break;
                }
            }
            nodeofField = nodeofField->get_nodes(1);
        };
        // std::for_each(std::cbegin(namesofFileds), std::cend(namesofFileds), [](auto item)
        //               {
        //                   // std::cout << getStrValueFromDecList(item) << " ";
        //               });
        // std::cout << '\n';
    }
}

// input is a Specifier Node
// Return is its Type's string
Type *getSpecifierType(Node *node)
{
    if (node->name != "Specifier")
    {
        return nullptr;
    }
    if (node->get_nodes(0)->nodes.empty())
    {
        const string &pureTypeName = std::get<string>(node->get_nodes(0)->value);
        return Type::getPrimitiveType(snt[pureTypeName]);
    }
    else
    {
        return scopeStack.lookup(std::get<string>(node->get_nodes(0, 1)->value));
        // return symbolTable[std::get<string>(node->get_nodes(0, 1)->value)];
    }
}

void Specifier_FunDec_Recv_SF(Node *node)
{
    auto name = std::get<string>(node->get_nodes(1, 0)->value);
    // Type *functionType = symbolTable[name];
    Type *functionType = scopeStack.lookup(name);

    Node *specifier = node->get_nodes(0);
    auto specifierType = getSpecifierType(specifier);
    functionType->returnType = specifierType;
}

void extDefVisit_SFC(Node *node)
{
#ifdef DEBUG
    node->print(0);
#endif
    checkReturnValueMatchDeclaredType(node);
}

// void expVisit(Node *node) {
// #ifdef DEBUG
//     node->print(0);
// #endif
// }

FieldList *getFiledListFromDefList(Node *node)
{
    if (node == nullptr || node->nodes.empty() || node->name != "DefList")
    {
        return nullptr;
    }
    string name = getStrValueFromDecList(node->get_nodes(0, 1));
    return new FieldList(name, scopeStack.lookup(name), getFiledListFromDefList(node->get_nodes(1)));

    // return new FieldList(name, symbolTable[name], getFiledListFromDefList(node->get_nodes(1)));
}

void checkRvalueInLeftSide(Node *node)
{
    if (node->name != "Exp")
    {
        // error
    }
    Node *leftExpNode = node->get_nodes(0);
    switch (leftExpNode->nodes.size())
    {
    case 1:
    {
        if (leftExpNode->get_nodes(0)->name == "ID")
        {
            return;
        }
        break;
    }
    case 3:
    {
        if (leftExpNode->get_nodes(0)->name == "Exp" && leftExpNode->get_nodes(2)->name == "ID" &&
            leftExpNode->get_nodes(1)->name == "DOT")
        {
            return;
        }
        break;
    }
    case 4:
    {
        if (leftExpNode->get_nodes(0)->name == "Exp" && leftExpNode->get_nodes(2)->name == "Exp" &&
            leftExpNode->get_nodes(1)->name == "LB" && leftExpNode->get_nodes(3)->name == "RB")
        {
            return;
        }
        break;
    }
    }
    rvalueLeftSetError(std::get<int>(node->value));
}

void checkIdExists(Node *node, int lineNum)
{
    if (node->name != "ID")
    {
        return;
    }
    string idName = std::get<string>(node->value);
    // if (symbolTable.count(idName) == 0)
    if (scopeStack.lookup(idName) == nullptr || scopeStack.lookup(idName) == Type::getPrimitiveType(Node_TYPE::WRONG))
    {
        scopeStack.scopes.back()[idName] = Type::getPrimitiveType(Node_TYPE::WRONG);

        variableNoDefinition(lineNum, idName);
    }
}

void funDecVisit(Node *funDec)
{
    Type *functionType = new Type();
    functionType->category = CATEGORY::FUNCTION;
    functionType->name = std::get<string>(funDec->get_nodes(0)->value);
    // if (symbolTable.count(functionType->name) != 0)
    scopeStack.enterScope(std::unordered_map<std::string, Type *>());
    bool err = scopeStack.lookup(functionType->name) != nullptr;
    // std::cout << "Entering scope via funDecVisit" << std::endl;

    if (funDec->nodes.size() == 3)
    {
        functionType->type = static_cast<FieldList *>(nullptr);
    }
    else
    {
        Node *varList = funDec->get_nodes(2);

        do
        {
            Node *specifier = varList->get_nodes(0, 0);
            auto specifierType = getSpecifierType(specifier);
            auto varDec = varList->get_nodes(0, 1);
            string paramName = getStrValueFromVarDec(varDec);
            // string paramName = std::get<string>(varList->get_nodes(0, 1, 0)->value);
            // if (symbolTable.count(paramName) != 0)
            if (scopeStack.lookup(paramName) != nullptr)
            {
                variableRedefined(std::get<int>(varList->value), paramName);
            }

            if (varDec->nodes.size() == 1)
            {
                scopeStack.scopes.back()[paramName] = specifierType;
                // symbolTable[paramName] = specifierType;
            }
            else
            {
                // Struct with variable definition - with Array
                scopeStack.scopes.back()[paramName] = new Type(paramName, CATEGORY::ARRAY,
                                                               getArrayFromVarDec(varDec, specifierType));
                // symbolTable[paramName] = new Type(paramName, CATEGORY::ARRAY,
                //                                   getArrayFromVarDec(varDec, specifierType));
            }
            if (varList->nodes.size() == 1)
            {
                break;
            }
            varList = varList->get_nodes(2);
        } while (true);
        varList = funDec->get_nodes(2);
        FieldList fieldList;
        fieldList.next = new FieldList();
        FieldList *fieldListPtr = fieldList.next;
        functionType->type = fieldList.next;
        do
        {
            string paramName = getStrValueFromVarDec(varList->get_nodes(0, 1));
            fieldListPtr->name = paramName;
            // fieldListPtr->type = symbolTable[paramName];

            fieldListPtr->type = scopeStack.lookup(paramName);

            if (varList->nodes.size() == 1)
            {
                break;
            }
            varList = varList->get_nodes(2);
            fieldListPtr->next = new FieldList();
            fieldListPtr = fieldListPtr->next;
        } while (true);
    }

    scopeStack.scopes[scopeStack.current_scope_level - 1][functionType->name] = functionType;
    if (err)
    {
        functionRedefined(std::get<int>(funDec->value), functionType->name);
    }

    // symbolTable[functionType->name] = functionType;
}

void checkNoSuchMember(Node *node)
{
    /* Exp
     *   Exp
     *   DOT
     *   ID
     */
    if (node->name != "Exp")
    {
        return;
    }
    if (node->get_nodes(0)->type == nullptr)
    {
        return;
    }
    if (node->get_nodes(0)->type->category != CATEGORY::STRUCTURE)
    {
        nonStructFVariable(std::get<int>(node->value));
    }
}

void searchAndPutTypeOfDot(Node *expOut, Node *expIn, Node *ID)
{
    if (expIn->type == nullptr)
    {
        nonStructFVariable(std::get<int>(expIn->value));
        return;
    }
    if (expIn->type->type.index() != FieldList_POINTER_VALUE)
    {
        return;
    }
    FieldList *fieldList = std::get<FieldList *>(expIn->type->type);
    string idName = std::get<string>(ID->value);
    while (fieldList != nullptr)
    {
        if (fieldList->name == idName)
        {
            expOut->type = fieldList->type;
            return;
        }
        fieldList = fieldList->next;
    }
    expOut->type = Type::getPrimitiveWRONG();
    noSuchMember(std::get<int>(expOut->value), idName);
}

void checkInvokeExist(Node *node, int lineNum)
{
    string functionName = std::get<string>(node->value);
    // if (symbolTable.count(functionName) == 0)
    if (scopeStack.lookup(functionName) == nullptr)

    {
        functionNoDefinition(lineNum, functionName);
    }
    // else if (symbolTable[functionName]->category != CATEGORY::FUNCTION)
    else if (scopeStack.lookup(functionName)->category != CATEGORY::FUNCTION)

    {
        invokeNonFunctionVariable(lineNum, functionName);
    }
}

void getReturnTypeOfFunction(Node *expOut, Node *ID)
{
    string functionName = std::get<string>(ID->value);
    // if (symbolTable.count(functionName) == 0 || symbolTable[functionName]->category != CATEGORY::FUNCTION)
    if (scopeStack.lookup(functionName) == nullptr || scopeStack.lookup(functionName)->category != CATEGORY::FUNCTION)

    {
        return;
    }
    Type *returnType = scopeStack.lookup(functionName)->returnType;
    expOut->type = returnType;
}

void checkFunctionParams(Node *ID, Node *args, int lineNum)
{
    string functionName = std::get<string>(ID->value);
    // if (symbolTable.count(functionName) == 0 || symbolTable[functionName]->category != CATEGORY::FUNCTION)
    if (scopeStack.lookup(functionName) == 0 || scopeStack.lookup(functionName)->category != CATEGORY::FUNCTION)

    {
        return;
    }
    // Type *functionType = symbolTable[functionName];
    Type *functionType = scopeStack.lookup(functionName);
    FieldList *fieldList = functionType->type.index() == Node_TYPE_VALUE ? nullptr : std::get<FieldList *>(functionType->type);
    auto fieldListFunc = [](FieldList *_field)
    {
        int number = 0;
        while (_field != nullptr)
        {
            _field = _field->next;
            number++;
        }
        return number;
    };
    auto argsFunc = [](Node *Args_)
    {
        int number = 1;
        while (Args_->nodes.size() != 1)
        {
            Args_ = Args_->get_nodes(2);
            number++;
        }
        return number;
    };
    if (args == nullptr)
    {
        if (fieldList == nullptr)
        {
            return;
        }
        else
        {
            int except = fieldListFunc(fieldList);
            invalidArgumentNumber(lineNum, functionName, except, 0);
        }
    }
    else if (fieldList == nullptr)
    {
        // check args的参数数量
        int actually = argsFunc(args);
        invalidArgumentNumber(lineNum, functionName, 0, actually);
        return;
    }
    else
    {
        // both check args, but check fieldList
        int except = fieldListFunc(fieldList);
        int actually = argsFunc(args);
        if (except != actually)
        {
            invalidArgumentNumber(lineNum, functionName, except, actually);
            return;
        }
        int count = 0;
        while (count < std::min(except, actually))
        {
            count++;
            Type *paramType = fieldList->type;
            string argsName;
            if (args->get_nodes(0, 0)->value.index() != 0)
            {
                if (((paramType->category != CATEGORY::PRIMITIVE && paramType->category != CATEGORY::STRUCTURE) ||
                     paramType != args->get_nodes(0)->type) &&
                    args->get_nodes(0)->type != Type::getPrimitiveWRONG()
                    // std::get<Node_TYPE>(paramType->type) != args->get_nodes(0, 0)->TYPE
                )
                {
                    invalidArgumentType(lineNum, functionName, categoryAndTypeNameFromType(paramType),
                                        tns[args->get_nodes(0, 0)->TYPE]);
                }
            }
            else
            {
                argsName = std::get<string>(args->get_nodes(0, 0)->value);
            }
            // if (symbolTable.count(argsName) == 0)
            if (scopeStack.lookup(argsName) == nullptr)
            {
            }
            else
            {

                // Type *argsType = symbolTable[argsName];
                Type *argsType = scopeStack.lookup(argsName);

                if (argsType->category == CATEGORY::FUNCTION)
                {
                    argsType = argsType->returnType;
                }
                auto errorOfinvalidArgumentType = [lineNum, functionName, paramType, argsType]
                {
                    if (argsType != Type::getPrimitiveType(Node_TYPE::WRONG))
                    {
                        invalidArgumentType(lineNum, functionName, categoryAndTypeNameFromType(paramType),
                                            categoryAndTypeNameFromType(argsType));
                    }
                };
                if (paramType == nullptr || argsType == nullptr)
                {
                    errorOfinvalidArgumentType();
                }
                else if (paramType->category != argsType->category)
                {
                    errorOfinvalidArgumentType();
                }
                else if (paramType->category == CATEGORY::PRIMITIVE && paramType != argsType)
                {
                    errorOfinvalidArgumentType();
                }
                else if (paramType->category == CATEGORY::STRUCTURE && paramType->name != argsType->name)
                {
                    errorOfinvalidArgumentType();
                }
                else if (paramType->category == CATEGORY::ARRAY)
                {
                    vector<int> levelField, levelArgs;
                    Type *baseTypeOfField, *baseTypeOfArgs;
                    std::tie(levelField, baseTypeOfField) = getArrayDemensionAndType(paramType);
                    std::tie(levelArgs, baseTypeOfArgs) = getArrayDemensionAndType(argsType);
                    if (baseTypeOfField == nullptr || baseTypeOfArgs == nullptr)
                    {
                        errorOfinvalidArgumentType();
                    }
                    else if (levelField.size() != levelArgs.size() ||
                             std::equal(levelField.cbegin(), levelField.cend(), levelArgs.cbegin()) ||
                             baseTypeOfField->category != baseTypeOfArgs->category)
                    {
                        errorOfinvalidArgumentType();
                    }
                    else if (baseTypeOfField->category == CATEGORY::PRIMITIVE && baseTypeOfField != baseTypeOfArgs)
                    {
                        errorOfinvalidArgumentType();
                    }
                    else if (baseTypeOfField->category == CATEGORY::STRUCTURE &&
                             baseTypeOfArgs->name != baseTypeOfField->name)
                    {
                        errorOfinvalidArgumentType();
                    }
                }
            }
            fieldList = fieldList->next;
            args = args->get_nodes(2);
        }
    }
}

void checkArrayExists(Node *Exp)
{
    // Node *temp = Exp;
    if (Exp->nodes.size() == 1)
    {
        string arrayName = std::get<string>(Exp->get_nodes(0)->value);
        // if (symbolTable.count(arrayName) != 0)
        if (scopeStack.lookup(arrayName) != nullptr)

        {
            // Type *arrayType = symbolTable[arrayName];
            Type *arrayType = scopeStack.lookup(arrayName);
            if (arrayType->category != CATEGORY::ARRAY)
            {
                indexOnNonArray(std::get<int>(Exp->value));
            }
        }
        else
        {
            indexOnNonArray(std::get<int>(Exp->value));
        }
    }
    else
    {
        //
        Type *arrayType = Exp->type;
        if (arrayType == nullptr || arrayType->category != CATEGORY::ARRAY)
        {
            indexOnNonArray(std::get<int>(Exp->value));
        }
    }
}

bool checkIntegerType(Node *exp, const std::function<void(int)> &func)
{
    if (exp->type != Type::getPrimitiveINT())
    {
        func(std::get<int>(exp->value));
        return false;
    }
    return true;
}
bool checkBooleanType(Node *exp, const std::function<void(int)> &func)
{
    if (exp->type != Type::getPrimitiveBOOLEAN())
    {
        func(std::get<int>(exp->value));
        return false;
    }
    return true;
}

bool checkIntegerExp(Node *exp)
{
    return checkIntegerType(exp, nonIntegerTypeIndexing);
}

void getArrayType(Node *expOut, Node *expIn, Node *Integer)
{
    bool integerOk = checkIntegerExp(Integer);
    if (!integerOk)
    {
        expOut->type = nullptr;
        return;
    }
    if (expOut->nodes.size() == 1)
    {
        string arrayName = std::get<string>(expOut->get_nodes(0)->value);
        // if (symbolTable.count(arrayName) != 0)
        if (scopeStack.lookup(arrayName) != nullptr)

        {
            // Type *arrayType = symbolTable[arrayName];
            Type *arrayType = scopeStack.lookup(arrayName);
            if (arrayType->category == CATEGORY::ARRAY)
            {
                expOut->type = arrayType;
            }
        }
        else
        {
        }
    }
    else
    {
        //
        Type *arrayType = expIn->type;
        if (arrayType == nullptr)
        {
            expOut->type = static_cast<Type *>(nullptr);
            return;
        }
        if (arrayType->category == CATEGORY::ARRAY)
        {
            expOut->type = std::get<Array *>(arrayType->type)->base;
        }
    }
}

void getComparisonOperatorType(Node *expOut, Node *expIn1, Node *expIn2)
{
    Node_TYPE check1 = checkComparisonOperatorType(expIn1);
    Node_TYPE check2 = checkComparisonOperatorType(expIn2);

    if (check1 == Node_TYPE::LINE || check2 == Node_TYPE::LINE)
    {
    }
    else if ((check1 == Node_TYPE::INT || check1 == Node_TYPE::FLOAT) &&
             (check2 == Node_TYPE::INT || check2 == Node_TYPE::FLOAT))
    {
        expOut->type = Type::getPrimitiveBOOLEAN();
    }
    else
    {
        if (check1 == Node_TYPE::BOOLEAN && check2 == Node_TYPE::BOOLEAN)
        {
            expOut->type = Type::getPrimitiveBOOLEAN();
        }
        else
        {
        }
    }
}

bool checkBoolOperatorType(Node *exp)
{
    return checkBooleanType(exp, unmatchingOperatorNonBoolean);
}

void getBoolOperatorType(Node *expOut, Node *expIn1, Node *expIn2)
{
    bool check1 = checkBoolOperatorType(expIn1);
    bool check2 = checkBoolOperatorType(expIn2);
    if (check1 && check2)
    {
        expOut->type = Type::getPrimitiveBOOLEAN();
    }
}

Node_TYPE checkComparisonOperatorType(Node *exp)
{
    if (exp->type == Type::getPrimitiveWRONG())
    {
        return Node_TYPE::LINE;
    }

    if (exp->type == nullptr)
    {
        unmatchingOperatorNonComparison(std::get<int>(exp->value));
        return Node_TYPE::LINE;
    }
    if (exp->type->category != CATEGORY::PRIMITIVE ||
        (exp->type != Type::getPrimitiveINT() && exp->type != Type::getPrimitiveFLOAT() && exp->type != Type::getPrimitiveBOOLEAN()))
    {
        unmatchingOperatorNonComparison(std::get<int>(exp->value));
        return Node_TYPE::LINE;
    }
    return std::get<Node_TYPE>(exp->type->type);
}

Node_TYPE checkAlrthOperatorType(Node *exp)
{
    if (exp->type == Type::getPrimitiveWRONG())
    {
        return Node_TYPE::LINE;
    }

    if (exp->type == nullptr)
    {
        unmatchingOperatorNonNumber(std::get<int>(exp->value));
        return Node_TYPE::LINE;
    }
    if (exp->type->category != CATEGORY::PRIMITIVE ||
        (exp->type != Type::getPrimitiveINT() && exp->type != Type::getPrimitiveFLOAT()))
    {
        unmatchingOperatorNonNumber(std::get<int>(exp->value));
        return Node_TYPE::LINE;
    }
    return std::get<Node_TYPE>(exp->type->type);
}

void getAlrthOperatorType(Node *expOut, Node *expIn1, Node *expIn2)
{
    auto check1 = checkAlrthOperatorType(expIn1);
    auto check2 = checkAlrthOperatorType(expIn2);
    if (check1 == Node_TYPE::LINE || check2 == Node_TYPE::LINE)
    {
    }
    else if (check1 == Node_TYPE::FLOAT && check2 == Node_TYPE::FLOAT)
    {
        expOut->type = Type::getPrimitiveFLOAT();
    }
    else if (check1 == Node_TYPE::INT && check2 == Node_TYPE::INT)
    {
        expOut->type = Type::getPrimitiveINT();
    }
    else
    {
        unmatchingOperator(std::get<int>(expOut->value));
        expOut->type = Type::getPrimitiveWRONG();
    }
}

void checkTypeMatchType(Type *leftType, Type *rightType, int lineNum, const std::function<void(int)> &func)
{
    if (leftType == nullptr || rightType == nullptr || leftType == rightType || leftType == Type::getPrimitiveWRONG() || rightType == Type::getPrimitiveWRONG())
        return;

    else if (leftType->category != rightType->category)
    {
        func(lineNum);
    }
    else if (leftType->category == CATEGORY::STRUCTURE &&
             scopeStack.scopes.back()[leftType->name]->name != scopeStack.scopes.back()[rightType->name]->name)
    // else if (leftType->category == CATEGORY::STRUCTURE &&
    //         symbolTable[leftType->name]->name != symbolTable[rightType->name]->name)
    {
        func(lineNum);
    }
    else if (leftType->category == CATEGORY::ARRAY)
    {
        vector<int> demensionLeftArray, demensionRightArray;
        Type *insideLeftType, *insideRightType;
        std::tie(demensionLeftArray, insideLeftType) = getArrayDemensionAndType(leftType);
        std::tie(demensionRightArray, insideRightType) = getArrayDemensionAndType(rightType);
        if (demensionLeftArray.size() != demensionRightArray.size())
        {
            func(lineNum);
        }
        else if (insideLeftType == nullptr || insideRightType == nullptr)
        {
            func(lineNum);
        }
        else if (insideRightType->category != insideLeftType->category)
        {
            func(lineNum);
        }
        else if (insideRightType->category == CATEGORY::PRIMITIVE && insideLeftType != insideRightType)
        {
            func(lineNum);
        }
        else if (insideRightType->category == CATEGORY::STRUCTURE)
        {
            if (insideLeftType->name != insideRightType->name)
            {
                func(lineNum);
            }
        }
    }
    else
    {
        func(lineNum);
    }
}

void checkTypeMatch(Node *left, Node *right, int lineNum)
{
    Type *leftType = left->type;
    Type *rightType = right->type;
    checkTypeMatchType(leftType, rightType, lineNum, nonMatchTypeBothSide);
}

void checkReturnValueMatchDeclaredType(Node *extDefSfc)
{

    // Type *returnType = symbolTable[std::get<string>(extDefSfc->get_nodes(1, 0)->value)]->returnType;
    Type *returnType = scopeStack.lookup(std::get<string>(extDefSfc->get_nodes(1, 0)->value))->returnType;

    Node *compSt = extDefSfc->get_nodes(2);
    checkReturnValueFromCompStmt(returnType, compSt);
}

void checkReturnValueFromStmtList(Type *type, Node *stmtList)
{
    if (stmtList->nodes.empty())
    {
        return;
    }
    else
    {
        checkReturnValueFromStmt(type, stmtList->get_nodes(0));
        checkReturnValueFromStmtList(type, stmtList->get_nodes(1));
    }
}

void checkReturnValueFromCompStmt(Type *type, Node *compStmt)
{
    checkReturnValueFromStmtList(type, compStmt->get_nodes(1));
}

void checkReturnValueFromStmt(Type *type, Node *stmt)
{
    stmt = stmt->get_nodes(0);
    if (stmt->get_nodes(0)->name == "RETURN")
    {
        checkTypeMatchType(type, stmt->get_nodes(1)->type, std::get<int>(stmt->value), returnTypeDisMatch);
    }
    else if (stmt->nodes.size() == 1 && stmt->get_nodes(0)->name == "CompSt")
    {
        checkReturnValueFromCompStmt(type, stmt->get_nodes(0));
    }
    else if (stmt->get_nodes(0)->name == "IF")
    {
        switch (stmt->nodes.size())
        {
        case 5:
        case 6:
        {
            checkReturnValueFromStmt(type, stmt->get_nodes(4));
            break;
        }
        case 7:
        {
            checkReturnValueFromStmt(type, stmt->get_nodes(4));
            checkReturnValueFromStmt(type, stmt->get_nodes(6));
            break;
        }
        }
    }
    else if (stmt->get_nodes(0)->name == "WHILE")
    {
        if (stmt->nodes.size() == 5)
            checkReturnValueFromStmt(type, stmt->get_nodes(4));
        else
            checkReturnValueFromStmt(type, stmt->get_nodes(3));
    }
}
