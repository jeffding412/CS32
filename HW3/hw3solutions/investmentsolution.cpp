// ======================================= Investment
class Investment
{
  public:
    Investment(string nm, int pp);
    string name() const;
    int purchasePrice() const;
    virtual string description() const = 0;
    virtual bool fungible() const;
    virtual ~Investment() {}
  private:
    string m_name;
    int m_purchasePrice;
};

Investment::Investment(string nm, int pp)
 : m_name(nm), m_purchasePrice(pp)
{}

string Investment::name() const
{
  return m_name;
}

int Investment::purchasePrice() const
{
  return m_purchasePrice;
}

bool Investment::fungible() const
{
  return false;
}

// ======================================= Painting
class Painting : public Investment
{
  public:
    Painting(string nm, int pp);
    virtual string description() const;
    virtual ~Painting();
};

Painting::Painting(string nm, int pp)
 : Investment(nm, pp)
{}

string Painting::description() const
{
  return "painting";
}

Painting::~Painting()
{
  cout << "Destroying " << name() << ", a painting" << endl;
}

// ======================================= Stock
class Stock : public Investment
{
  public:
    Stock(string nm, int pp, string ticker);
    virtual string description() const;
    virtual bool fungible() const;
    virtual ~Stock();
  private:
    string m_tickerSymbol;
};

Stock::Stock(string nm, int pp, string ticker)
 : Investment(nm, pp), m_tickerSymbol(ticker)
{}

string Stock::description() const
{
  return "stock trading as " + m_tickerSymbol;
}

bool Stock::fungible() const
{
  return true;
}

Stock::~Stock()
{
  cout << "Destroying " << name() << ", a stock holding" << endl;
}

// ======================================= House
class House : public Investment
{
  public:
    House(string nm, int pp);
    virtual string description() const;
    virtual ~House();
};

House::House(string nm, int pp)
 : Investment(nm, pp)
{}

string House::description() const
{
  return "house";
}

House::~House()
{
  cout << "Destroying the house " + name() << endl;
}
