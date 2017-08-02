/********************************************************
 * File  : intset.cpp                                   *
 * Author: Ibook Eyoita                                 *
 ********************************************************/

#include "intset.hpp"

/****************************************************************
 * Note: This file uses capabilities of treating integers       *
 * as sequences of bits.  For example, integer 12 on a          *
 * 32 bit machine is 00000000000000000000000000001100.          *
 * The rightmost bit is the 1's column, the next bit the        *
 * 2's column, etc.  The columns are numbered, from right to    *
 * left, starting at 0.  A set is represented by putting a 1 in *
 * column k if k is in the set, and a 0 if k is not in the set. *
 * For example, set {2,5} is represented as integer             *
 * 00000000000000000000000000100100.                            *
 *                                                              *
 * C++ operations are as follows.                               *
 *                                                              *
 *   x & y      The bitwise "and" of x and y.  (The result has  *
 *              a 1 in each column whether both x and y have a  *
 *              1.)  This has the effect of intersecting sets.  *
 *                                                              *
 *  x | y       The bitwise "or" of x and y.  (Ther result has  *
 *              a 1 in each column whether either x or y or     *
 *              both have a 1.)  This has the effect of taking  *
 *              the union of sets.                              *
 *                                                              *
 *  ~x          The bitwise complement of x.  The result has a  *
 *              1 in each column where x has a 0, and a 0 in    *
 *              each column where x has a 1.                    *
 *                                                              *
 *  x >> k      The result of shifting x to the right k bits.   *
 *              (Normally, the leftmost bit is duplicated k     *
 *              times.)                                         *
 *                                                              *
 *  x << k      The result of shifting x to the left k bits.    *
 *              Normally, the rightmost k bits become 0.        *
 ****************************************************************/

int onlyMember(SetOfSmallInts s);
const SetOfSmallInts emptySet;

/***********************************************************
 *                   makeSet                               *
 ***********************************************************
 * Return the set represented by integer i.                *
 ***********************************************************/

SetOfSmallInts makeSet(int i)
{
    SetOfSmallInts s;
    s.ival = i;
    return s;
}

/***********************************************************
 *                   singletonSet                          *
 ***********************************************************/

SetOfSmallInts singletonSet(int x)
{
    return makeSet(1 << x);
}

/***********************************************************
 *                   rangeSet                              *
 ***********************************************************/

SetOfSmallInts rangeSet(int x, int y)
{
    if(x > y)
    {
        return emptySet;
    }
    else
    {
        return makeSet(((1 << (y - x + 1)) - 1) << x);
    }
}

/***********************************************************
 *                   isEmpty                               *
 ***********************************************************/

bool isEmpty(SetOfSmallInts s)
{
    return s.ival == 0;
}

/***********************************************************
 *                   isSingleton                           *
 ***********************************************************/

bool isSingleton(SetOfSmallInts s)
{
    return onlyMember(s) != 0;
}

/***********************************************************
 *                   size                                  *
 ***********************************************************/

int size(SetOfSmallInts s)
{
    int n, r;
    
    n = 0;
    r = s.ival;
    while(r != 0)
    {
        if((r & 1) != 0)
        {
            n++;
        }
        r = r >> 1;
    }
    return n;
}

/***********************************************************
 *                   member                                *
 ***********************************************************/

bool member(int x, SetOfSmallInts s)
{
    return ((1 << x) & s.ival) != 0;
}

/***********************************************************
 *                   insert                                *
 ***********************************************************/

SetOfSmallInts insert(int x, SetOfSmallInts s)
{
    return makeSet(s.ival | (1 << x));
}

/***********************************************************
 *                   remove                                *
 ***********************************************************/

SetOfSmallInts remove(int x, SetOfSmallInts s)
{
    return makeSet(s.ival & ~(1 << x));
}

/***********************************************************
 *                   setDifference                         *
 ***********************************************************/

SetOfSmallInts setDifference(SetOfSmallInts s, SetOfSmallInts t)
{
    return makeSet(s.ival & ~t.ival);
}

/***********************************************************
 *                   setUnion                              *
 ***********************************************************/

SetOfSmallInts setUnion(SetOfSmallInts s, SetOfSmallInts t)
{
    return makeSet(s.ival | t.ival);
}

/***********************************************************
 *                   setIntersection                       *
 ***********************************************************/

SetOfSmallInts setIntersection(SetOfSmallInts s, SetOfSmallInts t)
{
    return makeSet(s.ival & t.ival);
}

/***********************************************************
 *                   smallest                              *
 ***********************************************************/

int smallest(SetOfSmallInts s)
{
    int i,val;
    
    val = s.ival;
    if(val == 0)
    {
        return 0;
    }
    
    i = 0;
    if((val & 31) == 0)
    {
        val = val >> 5;
        i   = 5;
    }
    if((val & 7) == 0)
    {
        val = val >> 3;
        i += 3;
    }
    while((val & 1) == 0)
    {
        val = val >> 1;
        i++;
    }
    return i;
}


/***********************************************************
 *                   onlyMember                            *
 ***********************************************************/

int onlyMember(SetOfSmallInts s)
{
    int x = smallest(s);
    if(x != 0 && isEmpty(remove(x, s)))
    {
        return x;
    }
    else
    {
        return 0;
    }
}
