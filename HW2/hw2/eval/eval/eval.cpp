//
//  eval.cpp
//  eval
//
//  Created by Jeffrey Ding on 1/31/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

bool isInfixValid(string infix)
{
    char currentCharacter;          //tracks current character
    int numLeftParentheses = 0;     //tracks number of ('s
    int numRightParentheses = 0;    //tracks number of )'s
    int numOperators = 0;           //tracks number of mathematical operators
    int numChars = 0;               //tracks number of characters
    
    //iterate through the infix and check if syntax is numerically correct
    for (int x = 0; x < infix.size(); x++) {
        currentCharacter = infix[x];
        
        if (isalpha(currentCharacter) && isupper(currentCharacter)) {   //if current character is uppercase, infix is invalid
            return false;
        }
        
        //if current character is (, move on to next character
        if (currentCharacter == '(') {
            numLeftParentheses++;
            continue;
        }
        
        //if current character is ), move on to next character
        if (currentCharacter == ')') {
            numRightParentheses++;
            continue;
        }
        
        //if current character is a mathematical operator, move on to next character
        if (currentCharacter == '+' || currentCharacter == '-' || currentCharacter == '*' || currentCharacter == '/') {
            numOperators++;
            continue;
        }
        
        //at this point, if current character isn't a character, then infix isn't legal
        if (!isalpha(currentCharacter)) {
            return false;
        }
        
        numChars++;
    }
    
    if (numLeftParentheses != numRightParentheses) {    //infix isn't legal if number of ('s and )'s aren't equal
        return false;
    }
    if (numChars-1 != numOperators) {                   //infix isn't legal if number of operators isn't one less than number of characters
        return false;
    }
    
    char nextCharacter; //holds next character
    
    //iterate through infix to second to last character
    for (int x = 0; x < infix.size()-1; x++) {
        currentCharacter = infix[x];
        nextCharacter = infix[x+1];
        
        //if the current character is a character, the next character has to be a mathematical operator or )
        if (isalpha(currentCharacter) && (nextCharacter == '+' || nextCharacter == '-' || nextCharacter == '*' || nextCharacter == '/' || nextCharacter == ')')) {
            continue;
        }
        //if the current character is a mathematical operator, the next character has to be a character or (
        if ((currentCharacter == '+' || currentCharacter == '-' || currentCharacter == '*' || currentCharacter == '/') && (isalpha(nextCharacter) || nextCharacter == '(')) {
            continue;
        }
        //if the current character is a (, the next character has to be a character or (
        if (currentCharacter == '(' && (isalpha(nextCharacter) || nextCharacter == '(')) {
            continue;
        }
        //if the current character is a ), the next character has to be a mathematical operator or )
        if (currentCharacter == ')' && (nextCharacter == '+' || nextCharacter == '-' || nextCharacter == '*' || nextCharacter == '/' || nextCharacter == ')')) {
            continue;
        }
        
        //at this point, the infix should be invalid
        return false;
    }
    
    //at this point, the infix should be valid
    return true;
}

bool containsMapExclusive(string infix, const Map& values)
{
    char currentCharacter;
    //iterate through infix
    for (int x = 0; x < infix.size(); x++) {
        currentCharacter = infix[x];
        //if the current character is a character and Map values doesn't contain it, return false
        if (isalpha(currentCharacter)) {
            if (!values.contains(currentCharacter)) {
                return false;
            }
        }
    }
    
    //at this point, infix's characters are in Map values
    return true;
}

//returns true if ch is less or equal precdence as charTop, false otherwise
bool isLessPrecedent(char ch, char charTop)
{
    if ((ch == '*' || ch == '/') && (charTop == '+' || charTop == '-')) {
        return false;
    }
    return true;
}

//converts infix to postfix
void convertToPostfix(string infix, string& postfix)
{
    postfix = "";               //Initialize postfix to empty
    stack<char> inToPostStack;  //Initialize the operator stack to empty
    
    //For each character ch in the infix string
    char ch;
    for (int x = 0; x < infix.size(); x++) {
        ch = infix[x];
        if (isalpha(ch)) {  //if ch is a operand
            postfix += ch;  //append ch to end of postfix
            continue;
        }
        switch (ch) {
            case '(':
                inToPostStack.push(ch); //push ch onto the operator stack
                break;
            case ')':
                //pop stack until matching '('
                while (inToPostStack.top() != '(') {    //While stack top is not '('
                    postfix += inToPostStack.top();     //append the stack top to postfix
                    inToPostStack.pop();                //pop the stack
                }
                inToPostStack.pop();                    //pop the stack and remove the '('
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                //While the stack is not empty and the stack top is not '(' and precedence of ch <= precedence of stack top
                while (!inToPostStack.empty() && inToPostStack.top() != '(' && isLessPrecedent(ch, inToPostStack.top())) {
                    postfix += inToPostStack.top(); //append the stack top to postfix
                    inToPostStack.pop();            //pop the stack
                }
                inToPostStack.push(ch);             //push ch onto the stack
                break;
        }
    }
    while (!inToPostStack.empty()) {    //While the stack is not empty
        postfix += inToPostStack.top(); //append the stack top to postfix
        inToPostStack.pop();            //pop the stack
    }
}

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
int evaluate(string infix, const Map& values, string& postfix, int& result)
{
    //convert infix to an indentical string but with no whitespace
    string infixNoSpace = "";
    for (int x = 0; x < infix.size(); x++) {
        if (!isspace(infix[x])) {
            infixNoSpace += infix[x];
        }
    }
    
    //if the infix has invalid syntax, return 1
    if (!isInfixValid(infixNoSpace)) {
        return 1;
    }
    
    convertToPostfix(infixNoSpace, postfix);
    
    //if the infix contains letter operands that aren't in Map values, return 2
    if (!containsMapExclusive(infixNoSpace, values)) {
        return 2;
    }
    
    stack<char> evaluateStack;  //Initialize the operand stack to empty
    char ch;
    int postfixValue;
    for (int x = 0; x < postfix.size(); x++) {  //For each character ch in the postfix string
        ch = postfix[x];
        if (isalpha(ch)) {                      //if ch is an operand
            values.get(ch, postfixValue);       //store the value that ch represents into postfixValue
            evaluateStack.push(postfixValue);   //push the value that ch represents onto the operand stack
        }
        else {  //ch is a binary operator
            int operand2 = evaluateStack.top(); //set operand2 to the top of the operand stack
            evaluateStack.pop();                //pop the stack
            int operand1 = evaluateStack.top(); //set operand1 to the top of the operand stack
            evaluateStack.pop();                //pop the stack
            switch (ch) {                       //apply the operation that ch represents to operand1 and operand2, and push the result onto the stack
                case '+':
                    evaluateStack.push(operand1 + operand2);
                    break;
                case '-':
                    evaluateStack.push(operand1 - operand2);
                    break;
                case '*':
                    evaluateStack.push(operand1 * operand2);
                    break;
                case '/':
                    if (operand2 == 0) {        //check if not dividing by zero
                        return 3;
                    }
                    evaluateStack.push(operand1 / operand2);
                    break;
            }
        }
    }
    
    //When the loop is finished, the operand stack will contain one item, the result of evaluating the expression
    result = evaluateStack.top();
    
    return 0;
}

int main()
{
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
        m.insert(vars[k], vals[k]);
    string pf;
    int answer;
    assert(evaluate("a+ e", m, pf, answer) == 0  &&
           pf == "ae+"  &&  answer == -6);
    answer = 999;
    assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
    // unary operators not allowed:
    assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
    assert(evaluate("a*b", m, pf, answer) == 2  &&
           pf == "ab*"  &&  answer == 999);
    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
           pf == "yoau-*+"  &&  answer == -1);
    answer = 999;
    assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
           pf == "oyy-/"  &&  answer == 999);
    assert(evaluate(" a  ", m, pf, answer) == 0  &&
           pf == "a"  &&  answer == 3);
    assert(evaluate("((a))", m, pf, answer) == 0  &&
           pf == "a"  &&  answer == 3);
    cout << "Passed all tests" << endl;
}
