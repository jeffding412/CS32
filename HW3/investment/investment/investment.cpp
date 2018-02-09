//
//  investment.cpp
//  investment
//
//  Created by Jeffrey Ding on 2/8/18.
//  Copyright © 2018 Jeffrey Ding. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

//abstract Investment class
class Investment
{
public:
    Investment(string name, int price)      //constructor, all investments have a name and price
    {
        m_name = name;
        m_price = price;
    }
    virtual ~Investment()                   //destructor
    {}
    string name() const                     //all investments can return name
    {
        return m_name;
    }
    virtual bool fungible() const           //most investments aren't fungible
    {
        return false;
    }
    virtual string description() const = 0; //a pure investment doesn't have a description
    int purchasePrice() const               //all investments can return a price
    {
        return m_price;
    }
private:
    string m_name;
    int m_price;
};

//Stock class inherits from Investments
class Stock : public Investment
{
public:
    Stock(string name, int price, string ticker)    //constructor, all stocks have a name, price, and ticker
    :Investment(name, price)
    {
        m_ticker = ticker;
    }
    virtual ~Stock()                                //destructor
    {
        cout << "Destroying " << name() <<  ", a stock holding" << endl;
    }
    virtual bool fungible() const                   //stocks are fungible
    {
        return true;
    }
    virtual string description() const              //stocks have descriptions
    {
        return "stock trading as " + m_ticker;
    }
private:
    string m_ticker;
};

//House class inherits from Investments
class House : public Investment
{
public:
    House(string name, int price)               //constructor, all houses have a name and price
    :Investment(name, price)
    {}
    virtual ~House()                            //destructor
    {
        cout << "Destroying the house " << name() << endl;
    }
    virtual string description() const          //houses have descriptions
    {
        return "house";
    }
};

//Painting class inherits from Investments
class Painting : public Investment
{
public:
    Painting(string name, int price)            //constructor, all paintings have a name and price
    :Investment(name, price)
    {}
    virtual ~Painting()                         //destructor
    {
        cout << "Destroying " << name() <<  ", a painting" << endl;
    }
    virtual string description() const          //paintings have descriptions
    {
        return "painting";
    }
};

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
