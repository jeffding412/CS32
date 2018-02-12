You are developing investment portfolio management software for the bizarre and reclusive CEO of NachenGames. Every investment has a name and the price for it was bought. Each type of investment has a distinctive description. Most types of investments are non-fungible, but a few are fungible. (Goods of a particular type are fungible if they are freely interchangeable: One dollar as good as another, one gallon of unleaded gas is as good as another, one share of Amazon stock is as good as another. Non-fungible goods include tickets to a performance (some seats are better than others), apartments (some have better locations, views, fixtures), and sculptures (the original Michelangelo David is not interchangeable with a replica)).

Declare and implement the classes named in the sample program below in such a way that the program compiles, executes, and produces exactly the output shown. Do not change the implementations of display or main.

#include <iostream>
#include <string>
using namespace std;

Your declarations and implementations would go here

void display(const Investment* inv)
{
    cout << inv->name();
    if (inv->fungible())
        cout << " (fungible)";
    cout << ": " << inv->description() << " bought for $" << inv->purchasePrice() << endl;
}

int main()
{
    Investment* portfolio[4];
    portfolio[0] = new Painting("Salvator Mundi", 450300000);
      // Stock holdings have a name, value, and ticker symbol
    portfolio[1] = new Stock("Alphabet", 100000, "GOOGL");
    portfolio[2] = new Stock("Symantec", 50000, "SYMC");
    portfolio[3] = new House("4 Privet Drive", 660000);

    for (int k = 0; k < 4; k++)
        display(portfolio[k]);

      // Clean up the investments before exiting
    cout << "Cleaning up" << endl;
    for (int k = 0; k < 4; k++)
        delete portfolio[k];
}
Output produced:

Salvator Mundi: painting bought for $450300000
Alphabet (fungible): stock trading as GOOGL bought for $100000
Symantec (fungible): stock trading as SYMC bought for $50000
4 Privet Drive: house bought for $660000
Cleaning up
Destroying Salvator Mundi, a painting
Destroying Alphabet, a stock holding
Destroying Symantec, a stock holding
Destroying the house 4 Privet Drive
Decide which function(s) should be pure virtual, which should be non-pure virtual, and which could be non-virtual. Experiment to see what output is produced if you mistakenly make a function non-virtual when it should be virtual instead.

To force you to explore the issues we want you to, we'll put some constraints on your solution:

You must not declare any struct or class other than Investment, Painting, Stock, and House.
The Investment class must not have a default constructor. The only constructor you may declare for Investment must have exactly two parameters. Those parameters must be of a builtin type or of type string, and must be useful parameters.
Although the expression new Stock("Apple", 30000, "AAPL") is fine, the expression new Investment(X, Y), no matter what types X and Y are, must produce compilation errors. (A client can create a particular kind of investment, like a Stock, but is not allowed to create an object that is just a plain Investment.)
Other than constructors and destructors (which can't be const), all member functions must be const member functions.
No two functions with non-empty bodies may have the same implementation, or implementations that have the same effect for a caller. For example, there's a better way to deal with the name() function than to have each kind of file declare and identically implement a name function. (Notice that { return "painting"; } and { return "house"; } do not have the same effect, but { return "painting"; } and { string s("pain"); return s + "ting"; } have the same effect, which is to return "painting".)
No implementation of a name() or purchasePrice() function may call any other function.
All data members must be declared private. You may declare member functions public or private. Your solution must not declare any protected members (which we're not covering in this class).
So that everyone's solutions are more consistent, purchase prices should be of type int.
In a real program, you'd probably have separate Investment.h, Investment.cpp, Painting.h, Painting.cpp, etc., files. For simplicity for this problem, you'll just put everything in one file. What you'll turn in for this problem will be a file named investment.cpp containing the definitions and implementations of the four classes, and nothing more. (In other words, turn in only the program text that replaces Your declarations and implementations would go here.)

The following is a declaration of a function that takes a double and returns true if a particular property of that double is true, and false otherwise. (Such a function is called a predicate.)

	bool somePredicate(double x);
Here is an example of an implementation of the predicate x is negative:

	bool somePredicate(double x)
	{
	    return x < 0;
	}
Here is an example of an implementation of the predicate sin ex is greater than cos x:

	bool somePredicate(double x)
	{
	    return sin(exp(x)) > cos(x); // include <cmath> for std::sin, etc.
	}
Here are five functions, with descriptions of what they are supposed to do. They are incorrectly implemented. The first four take an array of doubles and the number of doubles to examine in the array; the last takes two arrays of doubles and the number of doubles to examine in each:

	  // Return false if the somePredicate function returns false for at
	  // least one of the array elements; return true otherwise.
	bool allTrue(const double a[], int n)
	{
	    return false;  // This is not always correct.
	}

	  // Return the number of elements in the array for which the
	  // somePredicate function returns false.
	int countFalse(const double a[], int n)
	{
	    return -999;  // This is incorrect.
	}

	  // Return the subscript of the first element in the array for which
	  // the somePredicate function returns false.  If there is no such
	  // element, return -1.
	int firstFalse(const double a[], int n)
	{
	    return -999;  // This is incorrect.
	}

	  // Return the subscript of the smallest double in the array (i.e.,
	  // the one whose value is <= the value of all elements).  If more
	  // than one element has the same smallest value, return the smallest
	  // subscript of such an element.  If the array has no elements to
	  // examine, return -1.
	int indexOfMin(const double a[], int n)
	{
	    return -999;  // This is incorrect.
	}

	  // If all n2 elements of a2 appear in the n1 element array a1, in
	  // the same order (though not necessarily consecutively), then
	  // return true; otherwise (i.e., if the array a1 does not include
	  // a2 as a not-necessarily-contiguous subsequence), return false.
	  // (Of course, if a2 is empty (i.e., n2 is 0), return true.)
	  // For example, if a1 is the 7 element array
	  //    10 50 40 20 50 40 30
	  // then the function should return true if a2 is
	  //    50 20 30
	  // or
	  //    50 40 40
	  // and it should return false if a2 is
	  //    50 30 20
	  // or
	  //    10 20 20
	bool includes(const double a1[], int n1, const double a2[], int n2)
	{
	    return false;  // This is not always correct.
	}
Your implementations of those first three functions must call the function named somePredicate where appropriate instead of hardcoding a particular expression like x < 0 or sin(exp(x)) > cos(x). (When you test your code, we don't care what predicate you have the function named somePredicate implement: x < 0 or x == 42 or sqrt(log(x*x+1)) > 2 or whatever, is fine.)

Replace the incorrect implementations of these functions with correct ones that use recursion in a useful way; your solution must not use the keywords while, for, or goto. You must not use global variables or variables declared with the keyword static, and you must not modify the function parameter lists. You must not use any references or pointers as parameters except for the parameters representing arrays. (Remember that a function parameter x declared T x[] for any type T means exactly the same thing as if it had been declared T* x.) If any of the parameters n, n1, or n2 is negative, act as if it were zero.

Here is an example of an implementation of allTrue that does not satisfy these requirements because it doesn't use recursion and it uses the keyword for:

	bool allTrue(const double a[], int n)
	{
	    for (int k = 0; k < n; k++)
	    {
	        if ( ! somePredicate(a[k]))
	            return false;
	    }
	    return true;
	}
You will not receive full credit if the allTrue, countFalse, or firstFalse functions cause each value somePredicate returns to be examined more than once. Consider all operations that a function performs that compares two doubles (e.g. <=, ==, etc.). You will not receive full credit if for nonnegative n, the indexOfMin function causes operations like these to be performed more than n times, or the includes function causes them to be performed more than n1 times. For example, this non-recursive (and thus unacceptable for this problem) implementation of indexOfMin performs a <= comparison of two doubles many, many more than n times, which is also unacceptable:

	int indexOfMin(const double a[], int n)
	{
	    for (int k1 = 0; k1 < n; k1++)
	    {
	        int k2;
	        for (k2 = 0; k2 < n && a[k1] <= a[k2]; k2++)
	            ;
		if (k2 == n)
	            return k1;
	    }
	    return -1;
	}
Each of these functions can be implemented in a way that meets the spec without calling any of the other four functions. (If you implement a function so that it does call one of the other functions, then it will probably not meet the limit stated in the previous paragraph.)

For this part of the homework, you will turn in one file named linear.cpp that contains the five functions and nothing more: no implementation of somePredicate and no main routine. (Our test framework will precede the functions with an implementation of a function named somePredicate that takes a double and returns a bool.)

Replace the implementation of pathExists from Homework 2 with one that does not use an auxiliary data structure like a stack or queue, but instead uses recursion in a useful way. Here is pseudocode for a solution:

	If the start location is equal to the ending location, then we've
	    solved the maze, so return true.
	Mark the start location as visted.
	For each of the four directions,
	    If the location one step in that direction (from the start
		location) is unvisited,
		    then call pathExists starting from that location (and
				ending at the same ending location as in the
				current call).
			 If that returned true,
			     then return true.
	Return false.
(If you wish, you can implement the pseudocode for loop with a series of four if statements instead of a loop.)

You may make the same simplifying assumptions that we allowed you to make for Homework 2 (e.g., that the maze contains only Xs and dots).

For this part of the homework, you will turn in one file named maze.cpp that contains the Coord class (if you use it) and the pathExists function and nothing more.

Replace the incorrect implementations of the countIncludes and the order functions below with correct ones that use recursion in a useful way. Except in the code for the split function that we give you below, your solution must not use the keywords while, for, or goto. You must not use global variables or variables declared with the keyword static, and you must not modify the function parameter lists. You must not use any references or pointers as parameters except for the parameters representing arrays and the parameters of the exchange function we provided. If any of the parameters n1, n2, or n is negative, act as if it were zero.

	  // Return the number of ways that all n2 elements of a2 appear
	  // in the n1 element array a1 in the same order (though not
	  // necessarily consecutively).  The empty sequence appears in a
	  // sequence of length n1 in 1 way, even if n1 is 0.
	  // For example, if a1 is the 7 element array
	  //	10 50 40 20 50 40 30
	  // then for this value of a2     the function must return
	  //	10 20 40			1
	  //	10 40 30			2
	  //	20 10 40			0
	  //	50 40 30			3
	int countIncludes(const double a1[], int n1, const double a2[], int n2)
	{
	    return -999;  // This is incorrect.
	}

	  // Exchange two doubles
	void exchange(double& x, double& y)
	{
	    double t = x;
	    x = y;
	    y = t;
	}

	  // Rearrange the elements of the array so that all the elements
	  // whose value is > splitter come before all the other elements,
	  // and all the elements whose value is < splitter come after all
	  // the other elements.  Upon return, firstNotGreater is set to the
	  // index of the first element in the rearranged array that is
	  // <= splitter, or n if there is no such element, and firstLess is
	  // set to the index of the first element that is < splitter, or n
	  // if there is no such element.
	  // In other words, upon return from the function, the array is a
	  // permutation of its original value such that
	  //   * for 0 <= i < firstNotGreater, a[i] > splitter
	  //   * for firstNotGreater <= i < firstLess, a[i] == splitter
	  //   * for firstLess <= i < n, a[i] < splitter
	  // All the elements > splitter end up in no particular order.
	  // All the elements < splitter end up in no particular order.
	void split(double a[], int n, double splitter,
	                                    int& firstNotGreater, int& firstLess)
	{
	    if (n < 0)
	        n = 0;
	
	      // It will always be the case that just before evaluating the loop
	      // condition:
	      //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
	      //  Every element earlier than position firstNotGreater is > splitter
	      //  Every element from position firstNotGreater to firstUnknown-1 is
	      //    == splitter
	      //  Every element from firstUnknown to firstLess-1 is not known yet
	      //  Every element at position firstLess or later is < splitter
	
	    firstNotGreater = 0;
	    firstLess = n;
	    int firstUnknown = 0;
	    while (firstUnknown < firstLess)
	    {
	        if (a[firstUnknown] < splitter)
	        {
	            firstLess--;
	            exchange(a[firstUnknown], a[firstLess]);
	        }
	        else
	        {
	            if (a[firstUnknown] > splitter)
	            {
	                exchange(a[firstNotGreater], a[firstUnknown]);
	                firstNotGreater++;
	            }
	            firstUnknown++;
	        }
	    }
	}

	  // Rearrange the elements of the array so that
	  // a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
	  // If n <= 1, do nothing.
	void order(double a[], int n)
	{
	    return;  // This is not always correct.
	}
(Hint: Using the split function, the order function can be written in fewer than eight short lines of code.)

Consider all operations that a function performs that compares two doubles (e.g. <=, ==, etc.). You will not receive full credit if for nonnegative n1 and n2, the countIncludes function causes operations like these to be called more than factorial(n1+1) / (factorial(n2)*factorial(n1+1-n2)) times. The countIncludes function can be implemented in a way that meets the spec without calling any of the functions in problem 2. (If you implement it so that it does call one of those functions, then it will probably not meet the limit stated in this paragraph.)

For this part of the homework, you will turn in one file named tree.cpp that contains the four functions above and nothing more.

Turn it in
By Tuesday, February 13, there will be a link on the class webpage that will enable you to turn in this homework. Turn in one zip file that contains your solutions to the homework problems. The zip file must contain one to four of the four files investment.cpp, linear.cpp, maze.cpp, and tree.cpp, depending on how many of the problems you solved. Your code must be such that if we insert it into a a suitable test framework with a main routine and appropriate #include directives, it compiles. (In other words, it must have no missing semicolons, unbalanced parentheses, undeclared variables, etc.) You must verify that your code works correctly using g32 and either Visual C++ or clang++.
