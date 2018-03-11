//
//  MyHash.h
//  Cracked
//
//  Created by Zhengfu Ding on 3/10/18.
//  Copyright © 2018 Zhengfu Ding. All rights reserved.
//

#ifndef MyHash_h
#define MyHash_h

#include "provided.h"

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
    
    unsigned int getBucketNumber(const KeyType& key) const;
    
    Node** m_buckets;       //dynamically allocated array of pointers to Nodes
    int m_maxBuckets;       //maximum number of buckets
    double m_maxLoadFactor; //max load factor
    int m_numberNodes;      //current number of Nodes
};

#endif /* MyHash_h */

//MyHash implementation

template<typename KeyType, typename ValueType>
unsigned int MyHash<KeyType, ValueType>::getBucketNumber(const KeyType& key) const
{
    unsigned int hash(const KeyType& k); // prototype
    unsigned int h = hash(key);
    
    unsigned int bucketNum = h%m_maxBuckets;
    return bucketNum;
}

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
    for (int i = 0; i < m_maxBuckets; i++) {
        if (m_buckets[i] != nullptr) {
            Node *p = m_buckets[i];         //Node pointer p points to head
            while (p != nullptr) {          //while pointer p points to a valid pointer
                Node *n = p->next;          //create a Node pointer n that points to the next Node
                delete p;                   //delete current Node
                p = n;                      //Node pointer p now points to the next Node
            }
        }
    }
    delete [] m_buckets;
    m_numberNodes = 0;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::reset()
{
    for (int i = 0; i < m_maxBuckets; i++) {
        if (m_buckets[i] != nullptr) {
            Node *p = m_buckets[i];         //Node pointer p points to head
            while (p != nullptr) {          //while pointer p points to a valid pointer
                Node *n = p->next;          //create a Node pointer n that points to the next Node
                delete p;                   //delete current Node
                p = n;                      //Node pointer p now points to the next Node
            }
        }
    }
    delete [] m_buckets;
    
    m_maxBuckets = 100;
    m_buckets = new Node*[m_maxBuckets];
    for (int i = 0; i < m_maxBuckets; i++) {    //sets each bucket to unused
        m_buckets[i] = nullptr;
    }
    m_numberNodes = 0;
}

template<typename KeyType, typename ValueType>
int MyHash<KeyType, ValueType>::getNumItems() const
{
    return m_numberNodes;
}

template<typename KeyType, typename ValueType>
double MyHash<KeyType, ValueType>::getLoadFactor() const
{
    return ((1.0) * m_numberNodes) / m_maxBuckets;
}
