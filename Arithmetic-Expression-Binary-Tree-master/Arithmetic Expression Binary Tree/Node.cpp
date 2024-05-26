#include "Node.h"
#include <sstream>

Node::Node(const std::string& str)
{
    std::string evaluated_str = evaluate_parentheses(str);
    if (evaluated_str.size() == 1 && isdigit(evaluated_str[0]))
    {
        val = std::stoi(evaluated_str);
        return;
    }
    int operat_pos = find_pos_of_min_priority(evaluated_str);
    operation = evaluated_str[operat_pos];
    std::string str_left = divide_str(0, operat_pos, evaluated_str);
    std::string str_right = divide_str(operat_pos + 1, evaluated_str.size(), evaluated_str);
    left = new Node(str_left);
    right = new Node(str_right);
}

int Node::calculate(Node* n)
{
    if (n->operation == '\0')
    {
        return n->val;
    }
    int res;
    if (n->operation == '+')
    {
        res = calculate(n->left) + calculate(n->right);
    }
    if (n->operation == '-')
    {
        res = calculate(n->left) - calculate(n->right);
    }
    if (n->operation == '*')
    {
        res = calculate(n->left) * calculate(n->right);
    }
    if (n->operation == '/')
    {
        res = calculate(n->left) / calculate(n->right);
    }
    return res;
}

bool Node::is_operator(const char& ch) const
{
    std::string operators = "+-*/()";
    return operators.find(ch) != std::string::npos;
}

std::string Node::divide_str(int left_pos, int right_pos, const std::string& str) const
{
    return str.substr(left_pos, right_pos - left_pos);
}

void Node::free_tree(Node* n)
{
    if (n->left)
    {
        free_tree(n->left);
    }
    if (n->right)
    {
        free_tree(n->right);
    }
    delete n;
}

int Node::find_pos_of_min_priority(const std::string& str) const
{
    int pos = -1;
    int min_priority = 5;
    for (int i = 0; i < str.size(); ++i)
    {
        if (is_operator(str[i]))
        {
            if (priority[str[i]] < min_priority)
            {
                pos = i;
                min_priority = priority[str[i]];
            }
        }
    }
    if (pos == -1)
    {
        throw std::logic_error("String doesn't have an operator");
    }
    return pos;
}

std::string Node::evaluate_parentheses(std::string str)
{
    size_t start, end;
    while ((start = str.find_last_of('(')) != std::string::npos)
    {
        end = str.find(')', start);
        if (end == std::string::npos)
        {
            throw std::logic_error("Mismatched parentheses");
        }
        std::string sub_expr = str.substr(start + 1, end - start - 1);
        Node temp_node(sub_expr);
        int sub_result = temp_node.calculate(&temp_node);
        str.replace(start, end - start + 1, std::to_string(sub_result));
    }
    return str;
}
