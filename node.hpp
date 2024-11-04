
#ifndef NODE_HPP
#define NODE_HPP
#include <functional>
#include <iostream>
#include <string>
#include <variant>

class Type;

using std::string;

enum class Node_TYPE
{
    LINE,
    NAME,
    STRING,
    CHAR,
    INT,
    FLOAT,
    BOOLEAN,
    NOTHING
};

class Node
{
    using Node_inside_type = std::variant<string, int, char, float, bool>;
    // line num, char_value,int_value,float_value
public:
    string name;
    Node_TYPE TYPE;
    int nodes_num = 0;
    Node_inside_type value;
    std::vector<Node *> nodes;
    Type *type = nullptr;

    // void (*print)(int, Node *);
    Node();

    explicit Node(Node_TYPE type);

    explicit Node(string nam);

    explicit Node(const char *nam);

    explicit Node(float value);

    explicit Node(int value);

    explicit Node(char value);

    explicit Node(bool value);

    Node(string nam, Node_TYPE type);

    Node(string nam, int int_line_value, Node_TYPE type = Node_TYPE::LINE);

    Node(string nam, string str_value, Node_TYPE type = Node_TYPE::STRING);

    ~Node() = default;

    void print(int space = 0);

    void push_back(Node *subnode)
    {
        this->nodes_num++;
        this->nodes.push_back(subnode);
    }

    template <typename T, typename... Args>
    void push_back(T subnode1, Args... rest)
    {
        this->push_back(subnode1);
        this->push_back(rest...);
    }

    Node *&get_nodes(size_t order)
    {
        return this->nodes[order];
    }

    template <typename T = size_t, typename... Args>
    Node *&get_nodes(size_t order, Args... rest)
    {
        return this->nodes[order]->get_nodes(rest...);
    }

private:
    static void print_n_space(int space);

    void print_line(int space);

    Node(string name, Node_TYPE node_type, int nodes_num, Node_inside_type value);
};

#endif
