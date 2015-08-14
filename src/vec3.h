//
//  vec3.h
//  turing3d
//
//  Created by Patrick on 11/08/2015.
//  Copyright (c) 2015 Patrick. All rights reserved.
//

#ifndef __turing3d__vec3__
#define __turing3d__vec3__

#include <stdio.h>
#include <iostream>
#include <stdexcept>

template <class T>
class Vec3
{
public:
    Vec3();
    Vec3(const T& a, const T& b, const T& c);
    T x, y, z;
    
    T& at(int i);
    const T& at(int i) const;
    
    Vec3& operator+= (const Vec3 &v) { x+=v.x; y+=v.y; z+=v.z; return *this; }
    friend std::ostream& operator << (std::ostream &out, const Vec3 &v)
        { out << '(' << v.x << ',' << v.y << ',' << v.z << ')'; return out; }
};

template <class T>
Vec3<T>::Vec3(): x(0), y(0), z(0) {}

template <class T>
Vec3<T>::Vec3(const T& a, const T& b, const T& c): x(a), y(b), z(c) {}

template <class T>
T& Vec3<T>::at(int i)
{
    if (i > 2)
        throw std::out_of_range("Vec3 index out of range");
    
    if (i == 0)
        return x;
    else if (i == 1)
        return y;
    return z;
}

template <class T>
const T& Vec3<T>::at(int i) const
{
    if (i > 2)
        throw std::out_of_range("Vec3 index out of range");
    
    if (i == 0)
        return x;
    else if (i == 1)
        return y;
    return z;
}

#endif /* defined(__turing3d__vec3__) */
