//
//  infinite3dArray.h
//  turing3d
//
//  Created by Patrick on 12/08/2015.
//  Copyright (c) 2015 Patrick. All rights reserved.
//

#ifndef __turing3d__infinite3dArray__
#define __turing3d__infinite3dArray__

#include <stdio.h>
#include <map>
#include <iostream>

template <class T>
class Infinite3dArray
{
public:
    Infinite3dArray(T default_elem);
    void set(int x, int y, int z, const T& elem);
    T& get(int x, int y, int z);
    const T& get(int x, int y, int z) const;
    void remove(int x, int y, int z);
    void set_default_element(T element);
    
    template <class S>
    struct Triplet
    {
        int first, second, third;
        Triplet(int a, int b, int c): first(a), second(b), third(c) {}
        friend bool operator< (const Triplet<S>& t1, const Triplet<S>& t2)
        { return (t1.first < t2.first) ||
            (!(t2.first < t1.first) && (t1.second < t2.second)) ||
            (!(t2.second < t1.second) && (t1.third < t2.third)); }
    };
protected:
    T default_elem;
    std::map<Triplet<int>, T> data;
};

template <class T>
Infinite3dArray<T>::Infinite3dArray(T default_elem): default_elem(default_elem) {}

template <class T>
void Infinite3dArray<T>::set(int x, int y, int z, const T& elem)
{
    T current = get(x, y, z);
    if (elem == default_elem && current != default_elem)
        remove(x, y, z);
    else if (elem != default_elem)
        data[Triplet<int>(x, y, z)] = elem;
}

template <class T>
T& Infinite3dArray<T>::get(int x, int y, int z)
{
    try
    {
        return data.at(Triplet<int>(x, y, z));
    }
    catch (std::out_of_range)
    {
        return default_elem;
    }
}

template <class T>
void Infinite3dArray<T>::remove(int x, int y, int z)
{
    data.erase(data.find(Triplet<int>(x, y, z)));
}

template <class T>
const T& Infinite3dArray<T>::get(int x, int y, int z) const
{
    try
    {
        return data.at(Triplet<int>(x, y, z));
    }
    catch (std::out_of_range)
    {
        return default_elem;
    }
}

template <class T>
void Infinite3dArray<T>::set_default_element(T element)
{
    default_elem = element;
}

#endif /* defined(__turing3d__infinite3dArray__) */
