#include "translate.hpp"
#include "scopeStack.hpp"

using std::string;
using std::unordered_map;
inline static constexpr int32_t begin_sign = 0;

template <typename T>
inline static void nodeInterCodeMerge(T f, T s)
{
    for (const auto &item : s->intercodes)
    {
        f->intercodes.push_back(item);
    }
}

template <typename First>
inline static void nodeInterCodeMerge(First f, vector<First> s)
{
    for (const auto &item : s)
    {
        nodeInterCodeMerge(f, item);
    }
}

template <typename First, typename... T>
inline static void nodeInterCodeMerge(First f, First s, T... args)
{
    nodeInterCodeMerge(f, s);
    if constexpr (sizeof...(args) > 0)
    {
        nodeInterCodeMerge(f, args...);
    }
}

static const unordered_map<Node *, InterCodeType> BioOpNodes = []
{
    static const unordered_map<Node *, InterCodeType> init{
        {Node::getSingleNameNodePointer("PLUS"), InterCodeType::ADD},
        {Node::getSingleNameNodePointer("MINUS"), InterCodeType::SUB},
        {Node::getSingleNameNodePointer("MUL"), InterCodeType::MUL},
        {Node::getSingleNameNodePointer("DIV"), InterCodeType::DIV},
        {Node::getSingleNameNodePointer("MOD"), InterCodeType::MOD},
        {Node::getSingleNameNodePointer("BOR"), InterCodeType::BOR},
        {Node::getSingleNameNodePointer("BAND"), InterCodeType::BAND},
        {Node::getSingleNameNodePointer("XOR"), InterCodeType::XOR},
    };
    return init;
}();
static const unordered_map<Node *, Node *> CompAssignNodes = []
{
    static const unordered_map<Node *, Node *> init{
        {Node::getSingleNameNodePointer("PLUS_ASSIGN"), Node::getSingleNameNodePointer("PLUS")},
        {Node::getSingleNameNodePointer("MINUS_ASSIGN"), Node::getSingleNameNodePointer("MINUS")},
        {Node::getSingleNameNodePointer("MUL_ASSIGN"), Node::getSingleNameNodePointer("MUL")},
        {Node::getSingleNameNodePointer("DIV_ASSIGN"), Node::getSingleNameNodePointer("DIV")},
        {Node::getSingleNameNodePointer("MOD_ASSIGN"), Node::getSingleNameNodePointer("MOD")},
        {Node::getSingleNameNodePointer("BOR_ASSIGN"), Node::getSingleNameNodePointer("BOR")},
        {Node::getSingleNameNodePointer("BAND_ASSIGN"), Node::getSingleNameNodePointer("BAND")},
        {Node::getSingleNameNodePointer("XOR_ASSIGN"), Node::getSingleNameNodePointer("XOR")},
    };
    return init;
}();

static string new_temp()
{
    static int tempValueTemp = begin_sign;
    return string("t").append(std::to_string(tempValueTemp++));
}

static string new_label()
{
    static int tempValueLabel = begin_sign + 1;
    return string("label").append(std::to_string(tempValueLabel++));
}

InterCode *translate_Exp(Node *exp, const string &place)
{
    auto *will_return = static_cast<InterCode *>(nullptr);
    switch (exp->nodes.size())
    {
    case 1:
    {
        if (exp->get_nodes(0)->name == "INT")
        {
            will_return = translate_Exp_INT(exp);
        }
        else
        {
            will_return = translate_Exp_RightElement(exp, place);
        }
        break;
    }
    case 3:
    {
        if (exp->get_nodes(0)->name == "Exp" && exp->get_nodes(2)->name == "Exp")
        {
            auto *const middleSign = exp->get_nodes(1);
            if (middleSign == Node::getSingleNameNodePointer("ASSIGN"))
            {
                will_return = translate_Exp_Assign_Exp(exp);
            }
            else if (CompAssignNodes.count(middleSign) != 0)
            {
                will_return = translate_Exp_Comp_Assign_Exp(exp);
            }
            else if (BioOpNodes.count(middleSign) != 0)
            {
                will_return = translate_Exp_Bio_Exp(exp);
            }
        }
        break;
    }
    }
    std::cout.flush();
    return will_return;
}

string getNameFromANode(Node *exp)
{
    if (exp->interCode != nullptr)
    {
        if (exp->get_nodes(0)->name == "INT")
            return std::string("#") + std::to_string(exp->interCode->SingleElement->value);
        return exp->interCode->assign.left->variName;
    }
    if (!exp->nodes.empty() && exp->get_nodes(0)->name == "ID")
    {
        return std::get<string>(exp->get_nodes(0)->value);
    }
    return "";
}

InterCode *translate_Ternary(Node *exp)
{
    const auto newLabel1 = new_label();
    const auto newLabel2 = new_label();
    auto *const leftNode = exp->get_nodes(2);
    auto *const rightNode = exp->get_nodes(4);
    const auto leftExpName = getNameFromANode(leftNode);
    const auto rightExpName = getNameFromANode(rightNode);
    auto *const will_return = new InterCode(InterCodeType::TERNARY);
    auto *const will_return_result = new Operand(OperandType::VARIABLE, new_temp());
    will_return->SingleElement = will_return_result;
    auto *const exp_value_left = new Operand(OperandType::VARIABLE, leftExpName);
    auto *const exp_value_right = new Operand(OperandType::VARIABLE, rightExpName);
    auto *const assign_left = new InterCode(InterCodeType::ASSIGN);
    auto *const assign_right = new InterCode(InterCodeType::ASSIGN);
    assign_left->assign = {will_return_result, exp_value_left};
    assign_right->assign = {will_return_result, exp_value_right};
    translate_Cond(exp->get_nodes(0), newLabel1, newLabel2);
    nodeInterCodeMerge(exp, exp->get_nodes(0));
    insertAJumpLabelToExpNode(exp, newLabel1);
    exp->intercodes.push_back(assign_left);
    insertAJumpLabelToExpNode(exp, newLabel2);
    exp->intercodes.push_back(assign_right);
    exp->interCode = will_return;
    return nullptr;
}

InterCode *translate_Exp_Bio_Exp(Node *exp)
{
    auto *const leftNode = exp->get_nodes(0);
    auto *const bioOp = exp->get_nodes(1);
    auto *const rightNode = exp->get_nodes(2);
    const auto leftVariName = getNameFromANode(leftNode);
    const auto rightExpLeftName = getNameFromANode(rightNode);
    auto *const will_return = new InterCode(BioOpNodes.at(bioOp));
    auto *const will_return_result = new Operand(OperandType::VARIABLE, new_temp());
    auto *const will_return_op2 = new Operand(OperandType::VARIABLE, leftVariName);
    auto *const will_return_op1 = new Operand(OperandType::VARIABLE, rightExpLeftName);
    will_return->bioOp = {will_return_result, will_return_op2, will_return_op1};
    exp->interCode = will_return;
    nodeInterCodeMerge(exp, leftNode, rightNode);
    exp->intercodes.push_back(will_return);
    return will_return;
}

InterCode *translate_Exp_Comp_Bio_Exp(Node *exp)
{
    auto *const leftNode = exp->get_nodes(0);
    auto *const bioOp = CompAssignNodes.at(exp->get_nodes(1));
    auto *const rightNode = exp->get_nodes(2);
    const auto leftVariName = getNameFromANode(leftNode);
    const auto rightExpLeftName = getNameFromANode(rightNode);
    auto *const will_return = new InterCode(BioOpNodes.at(bioOp));
    auto *const will_return_result = new Operand(OperandType::VARIABLE, new_temp());
    auto *const will_return_op2 = new Operand(OperandType::VARIABLE, leftVariName);
    auto *const will_return_op1 = new Operand(OperandType::VARIABLE, rightExpLeftName);
    will_return->bioOp = {will_return_result, will_return_op2, will_return_op1};
    exp->interCode = will_return;
    nodeInterCodeMerge(exp, leftNode, rightNode);
    exp->intercodes.push_back(will_return);
    return will_return;
}

InterCode *translate_Exp_INT(Node *exp)
{
    auto *const intExp = exp->get_nodes(0);
    int intExpValue = std::get<int>(intExp->value);
    auto *const constValue = new Operand(OperandType::CONSTANT, intExpValue);
    auto *const will_return = new InterCode(InterCodeType::CONSTANT);
    will_return->SingleElement = constValue;
    exp->interCode = will_return;
    return will_return;
}

InterCode *translate_Exp_RightElement(Node *exp, const string &place)
{
    // 先只考虑进来的exp就是ID的情况
    const auto stringOfVari = std::get<string>(exp->get_nodes(0)->value);
    if (stringOfVari == "read")
    {
        auto *will_return = new InterCode(InterCodeType::READ);
        auto *readParam = new Operand(OperandType::VARIABLE);
        readParam->variName = place;
        will_return->SingleElement = readParam;
        return will_return;
    }
    // auto variable = symbolTable[stringOfVari];
    auto *const will_return = new InterCode(InterCodeType::ASSIGN);
    auto *const leftPlace = new Operand(OperandType::VARIABLE);
    leftPlace->variName = place;
    auto *const rightValue = new Operand(OperandType::VARIABLE);
    rightValue->variName = stringOfVari;
    will_return->assign.left = leftPlace;
    will_return->assign.right = rightValue;
    return will_return;
}

InterCode *translate_Exp_Assign_Exp(Node *const exp)
{
    Node *const subnodes[3]{exp->get_nodes(0), exp->get_nodes(1), exp->get_nodes(2)};
    auto *const leftNode = subnodes[0];
    auto *const rightNode = subnodes[2];
    auto leftVariName = std::get<string>(leftNode->get_nodes(0)->value);
    auto rightExpLeftName = getNameFromANode(rightNode);
    if (rightNode->interCode != nullptr && rightNode->interCode->interCodeType == InterCodeType::READ)
    {
        auto *will_return = new InterCode(InterCodeType::READ);
        will_return->SingleElement = new Operand(OperandType::VARIABLE, leftVariName);
        exp->interCode = will_return;
        exp->intercodes.push_back(will_return);
        return will_return;
    }
    auto *const will_return = new InterCode(InterCodeType::ASSIGN);
    auto *const will_return_leftVari = new Operand(OperandType::VARIABLE);
    will_return_leftVari->variName = leftVariName;
    auto *const will_return_rightVari = new Operand(OperandType::VARIABLE);
    will_return_rightVari->variName = rightExpLeftName;
    will_return->assign = {will_return_leftVari, will_return_rightVari};
    if (!(rightNode->interCode != nullptr && rightNode->interCode->interCodeType == InterCodeType::CALL))
        exp->interCode = will_return;
    nodeInterCodeMerge(exp, leftNode, rightNode);
    exp->intercodes.push_back(will_return);
    return will_return;
}

InterCode *translate_Exp_Comp_Assign_Exp(Node *const exp)
{
    Node *const subnodes[3]{exp->get_nodes(0), exp->get_nodes(1), exp->get_nodes(2)};
    auto *const leftNode = subnodes[0];
    auto *const rightNode = subnodes[2];
    auto leftVariName = std::get<string>(leftNode->get_nodes(0)->value);
    auto rightExpLeftName = getNameFromANode(rightNode);
    auto *const assignNode = translate_Exp_Comp_Bio_Exp(exp);
    auto *const will_return = new InterCode(InterCodeType::ASSIGN);
    auto *const will_return_leftVari = new Operand(OperandType::VARIABLE);
    will_return_leftVari->variName = leftVariName;
    auto *const will_return_rightVari = assignNode->bioOp.result;
    will_return->assign = {will_return_leftVari, will_return_rightVari};
    if (!(rightNode->interCode != nullptr && rightNode->interCode->interCodeType == InterCodeType::CALL))
        exp->interCode = will_return;
    nodeInterCodeMerge(exp, leftNode, rightNode);
    exp->intercodes.push_back(will_return);
    return will_return;
}

InterCode *translate_varDecAssign(Node *const dec)
{
    return translate_Exp_Assign_Exp(dec);
}

void translate_DecListMerge(Node *const decList)
{
    nodeInterCodeMerge(decList, decList->get_nodes(0), decList->get_nodes(2));
}

// maybe include read
InterCode *translate_functionInvoke(Node *stmt)
{
    const std::array<Node *, 3> subnodes{stmt->get_nodes(0), stmt->get_nodes(1), stmt->get_nodes(2)};
    const auto functionName = std::get<string>(subnodes[0]->value);
    auto *will_return = new InterCode();
    if (functionName == "read")
    {
        will_return->interCodeType = InterCodeType::READ;
        stmt->interCode = will_return;
        stmt->interCode->SingleElement = new Operand(OperandType::VARIABLE);
    }
    else
    {
        will_return->interCodeType = InterCodeType::CALL;
        stmt->interCode = will_return;
        stmt->interCode->assign = {
            new Operand(OperandType::VARIABLE, new_temp()),
            new Operand(OperandType::VARIABLE, functionName)};
        //        stmt->interCode->SingleElement = new Operand(OperandType::VARIABLE);
    };
    return will_return;
}

// maybe include write
InterCode *translate_functionWithParamInvoke(Node *stmt)
{
    static auto getNameFromArgNode = [](Node *exp)
    {
        if (exp->interCode != nullptr)
        {
            if (exp->get_nodes(0)->name == "INT")
                return std::string("#") + std::to_string(exp->interCode->SingleElement->value);
            return exp->interCode->assign.left->variName;
        }
        else
        {
            return std::get<string>(exp->get_nodes(0)->value);
        }
    };
    const auto functionName = std::get<string>(stmt->get_nodes(0)->value);
    auto *argExp = stmt->get_nodes(2, 0);
    const auto paramName = getNameFromArgNode(argExp);
    auto *const will_return = new InterCode();
    if (functionName == "write")
    {
        will_return->interCodeType = InterCodeType::WRITE;
        will_return->SingleElement = new Operand(OperandType::VARIABLE, paramName);
        stmt->interCode = will_return;
        nodeInterCodeMerge(stmt, stmt->get_nodes(2));
        stmt->intercodes.push_back(will_return);
        return will_return;
    };
    vector<InterCode *> tempIntercodes;
    do
    {
        const auto argName = getNameFromArgNode(argExp);
        auto *const arg_InterCode = new InterCode(InterCodeType::ARG);
        arg_InterCode->SingleElement = new Operand(OperandType::VARIABLE, argName);
        argExp->interCode = arg_InterCode;
        // arg_InterCode->print();
        nodeInterCodeMerge(stmt, argExp->get_nodes(0));
        tempIntercodes.push_back(arg_InterCode);
        if (argExp->nodes.size() == 1)
        {
            break;
        }
        argExp = argExp->get_nodes(2);
    } while (argExp != nullptr);
    std::for_each(tempIntercodes.crbegin(), tempIntercodes.crend(),
                  [&stmt](InterCode *ic)
                  { stmt->intercodes.push_back(ic); });
    will_return->interCodeType = InterCodeType::CALL;
    stmt->interCode = will_return;
    stmt->interCode->assign = {
        new Operand(OperandType::VARIABLE, new_temp()),
        new Operand(OperandType::VARIABLE, functionName)};
    stmt->intercodes.push_back(will_return);
    return will_return;
}

void translate_functionBodyDefine(Node *stmt, Node *Specifier_FunDec_Recv, Node *CompSt)
{
    nodeInterCodeMerge(stmt, Specifier_FunDec_Recv, CompSt);
}

void translate_CompstMerge(Node *CompSt, Node *CompList)
{
    nodeInterCodeMerge(CompSt, CompList);
}

InterCode *translate_enterFunction(Node *const stmt)
{
    const auto functionName = std::get<string>(stmt->get_nodes(1, 0)->value);
    auto *const functionInterCode = new InterCode(InterCodeType::FUNCTION);
    functionInterCode->labelElement = new Operand(OperandType::JUMP_LABEL, functionName);
    stmt->interCode = functionInterCode;
    stmt->intercodes.push_back(functionInterCode);
    auto *const functionType = scopeStack.lookup(functionName);
    auto *list = std::get<FieldList *>(functionType->type);
    while (list != nullptr)
    {
        auto *const will_return = new InterCode(InterCodeType::PARAM);
        will_return->SingleElement = new Operand(OperandType::VARIABLE);
        will_return->SingleElement->variName = list->name;
        stmt->intercodes.push_back(will_return);
        list = list->next;
    }
    // TODO ,add Params
    return functionInterCode;
}

InterCode *translate_Return(Node *stmt)
{
    const auto returnName = getNameFromANode(stmt->get_nodes(1));
    auto *const will_return = new InterCode(InterCodeType::RETURN);
    will_return->SingleElement = new Operand(OperandType::VARIABLE, returnName);
    stmt->interCode = will_return;
    for (const auto &item : stmt->get_nodes(1)->intercodes)
    {
        stmt->intercodes.push_back(item);
    }
    stmt->intercodes.push_back(will_return);
    return nullptr;
}

void translate_StmtlistMerge(Node *StmtList)
{
    nodeInterCodeMerge(StmtList, StmtList->nodes);
}

void translate_DeflistMerge(Node *Deflist)
{
    nodeInterCodeMerge(Deflist, Deflist->nodes);
}

void translate_StmtMergeExp(Node *Stmt)
{
    nodeInterCodeMerge(Stmt, Stmt->nodes[0]);
}

void translate_if(Node *const stmt)
{
    const auto newLabel1 = new_label();
    const auto newLabel2 = new_label();
    translate_Cond(stmt->get_nodes(2), newLabel1, newLabel2);
    nodeInterCodeMerge(stmt, stmt->get_nodes(2));
    insertAJumpLabelToExpNode(stmt, newLabel1);
    nodeInterCodeMerge(stmt, stmt->get_nodes(4, 0)); // code2
    insertAJumpLabelToExpNode(stmt, newLabel2);
}

static const unordered_map<Node *, string> relopNameMap = []
{
    unordered_map<Node *, string> init{
        {Node::getSingleNameNodePointer("LT"), "<"},
        {Node::getSingleNameNodePointer("LE"), "<="},
        {Node::getSingleNameNodePointer("GT"), ">"},
        {Node::getSingleNameNodePointer("GE"), ">="},
        {Node::getSingleNameNodePointer("NE"), "!="},
        {Node::getSingleNameNodePointer("EQ"), "=="}};
    return init;
}();

void translate_Cond(Node *const stmt, string label_true, const string &label_false)
{
    if (relopNameMap.count(stmt->get_nodes(1)) != 0)
    {
        translate_relop(stmt, std::move(label_true), label_false);
    }
    else if (stmt->get_nodes(1) == Node::getSingleNameNodePointer("OR"))
    {
        translate_exp_or_exp(stmt, label_true, label_false);
    }
}

void translate_ifelse(Node *const stmt)
{
    const auto newLabel1 = new_label();
    const auto newLabel2 = new_label();
    const auto newLabel3 = new_label();
    translate_Cond(stmt->get_nodes(2), newLabel1, newLabel2);
    nodeInterCodeMerge(stmt, stmt->get_nodes(2));
    insertAJumpLabelToExpNode(stmt, newLabel1);
    nodeInterCodeMerge(stmt, stmt->get_nodes(4)); // code2
    insertAGotoLabelToExpNode(stmt, newLabel3);
    insertAJumpLabelToExpNode(stmt, newLabel2);
    nodeInterCodeMerge(stmt, stmt->get_nodes(6));
    insertAJumpLabelToExpNode(stmt, newLabel3);
}

void translate_while(Node *const stmt)
{
    const auto newLabel1 = new_label();
    const auto newLabel2 = new_label();
    const auto newLabel3 = new_label();
    translate_Cond(stmt->get_nodes(2), newLabel2, newLabel3);
    insertAJumpLabelToExpNode(stmt, newLabel1);
    nodeInterCodeMerge(stmt, stmt->get_nodes(2));
    insertAJumpLabelToExpNode(stmt, newLabel2);
    nodeInterCodeMerge(stmt, stmt->get_nodes(4));
    insertAGotoLabelToExpNode(stmt, newLabel1);
    insertAJumpLabelToExpNode(stmt, newLabel3);
}

void translate_while_empty(Node *const stmt)
{
    const auto newLabel1 = new_label();
    insertAJumpLabelToExpNode(stmt, newLabel1);
    nodeInterCodeMerge(stmt, stmt->get_nodes(3));
    insertAGotoLabelToExpNode(stmt, newLabel1);
}

void translate_for000(Node *const stmt)
{
    const auto newLabel1 = new_label();
    insertAJumpLabelToExpNode(stmt, newLabel1);
    nodeInterCodeMerge(stmt, stmt->get_nodes(5));
    insertAGotoLabelToExpNode(stmt, newLabel1);
}

void translate_for001(Node *const stmt)
{
    const auto newLabel1 = new_label();
    insertAJumpLabelToExpNode(stmt, newLabel1);
    nodeInterCodeMerge(stmt, stmt->get_nodes(6));
    nodeInterCodeMerge(stmt, stmt->get_nodes(4));
    insertAGotoLabelToExpNode(stmt, newLabel1);
}

void translate_for010(Node *const stmt)
{
    const auto newLabel1 = new_label();
    const auto newLabel2 = new_label();
    const auto newLabel3 = new_label();
    translate_Cond(stmt->get_nodes(3), newLabel2, newLabel3);
    insertAJumpLabelToExpNode(stmt, newLabel1);
    nodeInterCodeMerge(stmt, stmt->get_nodes(3));
    insertAJumpLabelToExpNode(stmt, newLabel2);
    nodeInterCodeMerge(stmt, stmt->get_nodes(7));
    insertAGotoLabelToExpNode(stmt, newLabel1);
    insertAJumpLabelToExpNode(stmt, newLabel3);
}

void translate_for011(Node *const stmt)
{
    const auto newLabel1 = new_label();
    const auto newLabel2 = new_label();
    const auto newLabel3 = new_label();
    translate_Cond(stmt->get_nodes(3), newLabel2, newLabel3);
    insertAJumpLabelToExpNode(stmt, newLabel1);
    nodeInterCodeMerge(stmt, stmt->get_nodes(3));
    insertAJumpLabelToExpNode(stmt, newLabel2);
    nodeInterCodeMerge(stmt, stmt->get_nodes(7));
    nodeInterCodeMerge(stmt, stmt->get_nodes(5));
    insertAGotoLabelToExpNode(stmt, newLabel1);
    insertAJumpLabelToExpNode(stmt, newLabel3);
}

void translate_for100(Node *const stmt)
{
    const auto newLabel1 = new_label();
    nodeInterCodeMerge(stmt, stmt->get_nodes(2));
    insertAJumpLabelToExpNode(stmt, newLabel1);
    nodeInterCodeMerge(stmt, stmt->get_nodes(5));
    insertAGotoLabelToExpNode(stmt, newLabel1);
}

void translate_for101(Node *const stmt)
{
    const auto newLabel1 = new_label();
    nodeInterCodeMerge(stmt, stmt->get_nodes(2));
    insertAJumpLabelToExpNode(stmt, newLabel1);
    nodeInterCodeMerge(stmt, stmt->get_nodes(6));
    nodeInterCodeMerge(stmt, stmt->get_nodes(4));
    insertAGotoLabelToExpNode(stmt, newLabel1);
}

void translate_for110(Node *const stmt)
{
    const auto newLabel1 = new_label();
    const auto newLabel2 = new_label();
    const auto newLabel3 = new_label();
    translate_Cond(stmt->get_nodes(3), newLabel2, newLabel3);
    nodeInterCodeMerge(stmt, stmt->get_nodes(2));
    insertAJumpLabelToExpNode(stmt, newLabel1);
    nodeInterCodeMerge(stmt, stmt->get_nodes(3));
    insertAJumpLabelToExpNode(stmt, newLabel2);
    nodeInterCodeMerge(stmt, stmt->get_nodes(7));
    insertAGotoLabelToExpNode(stmt, newLabel1);
    insertAJumpLabelToExpNode(stmt, newLabel3);
}

void translate_for111(Node *const stmt)
{
    const auto newLabel1 = new_label();
    const auto newLabel2 = new_label();
    const auto newLabel3 = new_label();
    translate_Cond(stmt->get_nodes(3), newLabel2, newLabel3);
    nodeInterCodeMerge(stmt, stmt->get_nodes(2));
    insertAJumpLabelToExpNode(stmt, newLabel1);
    nodeInterCodeMerge(stmt, stmt->get_nodes(3));
    insertAJumpLabelToExpNode(stmt, newLabel2);
    nodeInterCodeMerge(stmt, stmt->get_nodes(7));
    nodeInterCodeMerge(stmt, stmt->get_nodes(5));
    insertAGotoLabelToExpNode(stmt, newLabel1);
    insertAJumpLabelToExpNode(stmt, newLabel3);
}

InterCode *translate_minus_exp(Node *const exp)
{
    auto *const minus_exp = exp->get_nodes(1);
    const auto minus_exp_name = getNameFromANode(minus_exp);
    const auto newTempName = new_temp();
    auto *const will_return = new InterCode(InterCodeType::SUB);
    will_return->bioOp = {
        new Operand(OperandType::VARIABLE, newTempName),
        new Operand(OperandType::CONSTANT, 0),
        new Operand(OperandType::VARIABLE, minus_exp_name)};
    exp->interCode = will_return;
    nodeInterCodeMerge(exp, exp->get_nodes(1));
    exp->intercodes.push_back(will_return);
    return will_return;
}
InterCode *translate_plus_exp(Node *const exp)
{
    auto *const plus_exp = exp->get_nodes(1);
    const auto plus_exp_name = getNameFromANode(plus_exp);
    const auto newTempName = new_temp();
    auto *const will_return = new InterCode(InterCodeType::ADD);
    will_return->bioOp = {
        new Operand(OperandType::VARIABLE, newTempName),
        new Operand(OperandType::CONSTANT, 0),
        new Operand(OperandType::VARIABLE, plus_exp_name)};
    exp->interCode = will_return;
    nodeInterCodeMerge(exp, exp->get_nodes(1));
    exp->intercodes.push_back(will_return);
    return will_return;
}

InterCode *translate_exp_or_exp(Node *const exp, const string &label_true, const string &label_false)
{
    const std::array<Node *, 3> expSubs{exp->get_nodes(0), exp->get_nodes(1), exp->get_nodes(2)};
    const auto newLabel1 = new_label();
    translate_Cond(expSubs[0], label_true, newLabel1);
    nodeInterCodeMerge(exp, expSubs[0]);
    {
        auto *const label1InterCode = new InterCode(InterCodeType::LABEL);
        label1InterCode->labelElement = new Operand(OperandType::JUMP_LABEL);
        label1InterCode->labelElement->jumpLabel = newLabel1;
        exp->intercodes.push_back(label1InterCode);
    }
    translate_Cond(expSubs[2], label_true, label_false);
    nodeInterCodeMerge(exp, expSubs[2]);
    return nullptr;
}

InterCode *translate_relop(Node *const exp, string label_true, string label_false)
{
    const std::array<Node *, 3> expSubs{exp->get_nodes(0), exp->get_nodes(1), exp->get_nodes(2)};
    const auto tempName1 = getNameFromANode(expSubs[0]);
    const auto &opName = relopNameMap.at(expSubs[1]);
    // const auto op = BioOpNodes.at(expSubs[1]);
    const auto tempName2 = getNameFromANode(expSubs[2]);
    auto *const will_return = new InterCode(InterCodeType::IF_ELSE);
    // nodeInterCodeMerge(exp,expSubs[2]);
    will_return->ifElse = {
        new Operand(OperandType::VARIABLE, tempName1),
        new Operand(OperandType::VARIABLE, opName),
        new Operand(OperandType::VARIABLE, tempName2),
        new Operand(OperandType::JUMP_LABEL, std::move(label_true))};
    exp->interCode = will_return;
    nodeInterCodeMerge(exp, expSubs[0], expSubs[2]);
    exp->intercodes.push_back(will_return);
    auto *const elsePart = new InterCode(InterCodeType::GOTO);
    elsePart->labelElement = new Operand(OperandType::JUMP_LABEL);
    elsePart->labelElement->jumpLabel = std::move(label_false);
    exp->intercodes.push_back(elsePart);
    return will_return;
}

inline void insertAJumpLabelToExpNode(Node *const exp, string labelName)
{
    auto *const label1Intercode = new InterCode(InterCodeType::LABEL);
    label1Intercode->labelElement = new Operand(OperandType::JUMP_LABEL);
    label1Intercode->labelElement->jumpLabel = std::move(labelName);
    exp->intercodes.push_back(label1Intercode);
}

inline void insertAGotoLabelToExpNode(Node *const exp, string labelName)
{
    auto *const gotoLabel3Intercode = new InterCode(InterCodeType::GOTO);
    gotoLabel3Intercode->labelElement = new Operand(OperandType::JUMP_LABEL);
    gotoLabel3Intercode->labelElement->jumpLabel = std::move(labelName);
    exp->intercodes.push_back(gotoLabel3Intercode);
}
