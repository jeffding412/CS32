// eval.cpp

#include "Map.h"  // mapping char to int
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

const int RET_OK_EVALUATION      = 0;
const int RET_INVALID_EXPRESSION = 1;
const int RET_UNDEFINED_VARIABLE = 2;
const int RET_DIVISION_BY_ZERO   = 3;

inline
bool isLowerOrCloseParen(char ch)
{
    return islower(ch) || ch == ')';
}

inline
int precedence(char ch)
  //  Precondition:  ch is in "+-*/("
{
    static string ops = "+-*/(";
    static int prec[5] = { 1, 1, 2, 2, 0 };
    int pos = ops.find(ch);
    assert(pos != string::npos);  // must be found!
    return prec[pos];
}

bool convertInfixToPostfix(const string& infix, string& postfix)
  // Converts an integer arithmetic expression to postfix
  //   If infix is not a syntactically valid infix integer arithmetic
  //   expression, the function returns false.  (postfix may or may not
  //   be changed.)  Otherwise, postfix is set to the postfix form of
  //   that expression, and the function returns true.
{
    postfix = "";
    stack<char> operatorStack;
    char prevch = '+';  // pretend previous character was an operator

    for (size_t k = 0; k != infix.size(); k++)
    {
        char ch = infix[k];
        if (islower(ch))
        {
            if (isLowerOrCloseParen(prevch))
                return false;  // invalid expression
            postfix += ch;
        }
        else
        {
            switch(ch)
            {
              case ' ':
                continue;  // do not set prevch to this char

              case '(':
                if (isLowerOrCloseParen(prevch))
                    return false;  // invalid expression
                operatorStack.push(ch);
                break;

              case ')':
                if ( ! isLowerOrCloseParen(prevch))
                    return false;  // invalid expression
                for (;;)
                {
                    if (operatorStack.empty())
                        return false;  // invalid expression (too many ')')
                    char c = operatorStack.top();
                    operatorStack.pop();
                    if (c == '(')
                        break;
                    postfix += c;
                }
                break;

              case '+':
              case '-':
              case '*':
              case '/':
                if ( ! isLowerOrCloseParen(prevch))
                    return false;  // invalid expression
                while ( ! operatorStack.empty()  &&
                           precedence(ch) <= precedence(operatorStack.top()) )
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(ch);
                break;

              default:  // bad char
                return false;  // invalid expression
            }
        }
        prevch = ch;
    }

      // end of expression; pop remaining operators

    if ( ! isLowerOrCloseParen(prevch))
        return false;  // invalid expression
    while ( ! operatorStack.empty())
    {
        char c = operatorStack.top();
        operatorStack.pop();
        if (c == '(')
            return false;  // invalid expression (too many '(')
        postfix += c;
    }
    if (postfix.empty())
        return false;  // invalid expression (empty)

    return true;
}

int evaluate(const string& infix, const Map& values, string& postfix, int& result)
  // Evaluates an integer arithmetic expression
  //   If infix is a syntactically valid infix integer expression whose
  //   only operands are single lower case letters (whether or not they
  //   appear in the values map), then postfix is set to the postfix
  //   form of the expression; otherwise postfix may or may not be
  //   changed, result is unchanged, and the function returns 1.  If
  //   infix is syntactically valid but contains at least one lower
  //   case letter operand that does not appear in the values map, then
  //   result is unchanged and the function returns 2.  If infix is
  //   syntactically valid and all its lower case operand letters
  //   appear in the values map, then if evaluating the expression
  //   (using for each letter in the expression the value in the map
  //   that corresponds to it) attempts to divide by zero, then result
  //   is unchanged and the function returns 3; otherwise, result is
  //   set to the value of the expression and the function returns 0.
{
      // First convert infix to postfix

    if ( ! convertInfixToPostfix(infix, postfix))
        return RET_INVALID_EXPRESSION;

      // Now evaluate the postfix expression

    stack<int> operandStack;
    for (size_t k = 0; k != postfix.size(); k++)
    {
       char ch = postfix[k];
       if (islower(ch))
       {
           int val;
           if ( ! values.get(ch, val))
               return RET_UNDEFINED_VARIABLE;
           operandStack.push(val);
       }
       else
       {
           int opd2 = operandStack.top();
           operandStack.pop();
           int opd1 = operandStack.top();
           operandStack.pop();
           switch (ch)
           {
               case '+':
                   operandStack.push(opd1 + opd2);
                   break;
               case '-':
                   operandStack.push(opd1 - opd2);
                   break;
               case '*':
                   operandStack.push(opd1 * opd2);
                   break;
               case '/':
                   if (opd2 == 0)
                       return RET_DIVISION_BY_ZERO;  // divide by zero
                   operandStack.push(opd1 / opd2);
                   break;
               default:  // Impossible for valid postfix string!
                   return RET_INVALID_EXPRESSION;  // pretend it's an invalid expression
           }
       }
    }
    if (operandStack.size() != 1)  // Impossible for valid postfix string!
        return RET_INVALID_EXPRESSION;  // pretend it's an invalid expression
    result = operandStack.top();
    
    return RET_OK_EVALUATION;
}
