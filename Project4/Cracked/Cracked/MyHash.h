//
//  MyHash.h
//  Cracked
//
//  Created by Zhengfu Ding on 3/10/18.
//  Copyright © 2018 Zhengfu Ding. All rights reserved.
//

#ifndef MyHash_h
#define MyHash_h

template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor = 0.5);
    ~MyHash();
    void reset();
    void associate(const KeyType& key, const ValueType& value);
    int getNumItems() const;
    double getLoadFactor() const;
    
    // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const;
    
    // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }
    
    // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;
    
private:
    struct Node {
        KeyType m_key;
        ValueType m_value;
        Node* next;
    };
    
    Node** m_buckets;       //dynamically allocated array of pointers to Nodes
    int m_maxBuckets;       //maximum number of buckets
    int m_maxLoadFactor;    //max load factor
    int m_numberNodes;      //current number of Nodes
};

#endif /* MyHash_h */

//MyHash.cpp

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor)
{
    if (maxLoadFactor <= 0) {
        m_maxLoadFactor = 0.5;
    }
    else if (maxLoadFactor > 2) {
        m_maxLoadFactor = 2.0;
    }
    else {
        m_maxLoadFactor = maxLoadFactor;
    }
    m_maxBuckets = 100;
    m_buckets = new Node*[m_maxBuckets];        //dynamically allocates array of pointers to Nodes
    
    for (int i = 0; i < m_maxBuckets; i++) {    //sets each bucket to unused
        m_buckets[i] = nullptr;
    }
    m_numberNodes = 0;
}

template<typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::~MyHash()
{
    
}

