/********************************************************
 * File: intset.hpp                                       *
 * Author: Ibook Eyoita                                 *
 ********************************************************/

/****************************************************************
 *                     SetOfSmallInts                           *
 ****************************************************************
 * A value of type SetOfSmallInts is a set of the integers from *
 * 1 to 9.  When you create a variable of type SetofSmallInts,  *
 * it initially holds an empty set.                             *
 ****************************************************************/

struct SetOfSmallInts
{
    int ival;
    
    SetOfSmallInts()
    {
        ival = 0;
    }
};

/****************************************************************
 *                     emptySet                                 *
 ****************************************************************
 * emptySet is an empty set.                                    *
 ****************************************************************/

extern const SetOfSmallInts emptySet;

/****************************************************************
 *                     singletonSet                             *
 ****************************************************************
 * singletonSet(x) is the set {x}.                              *
 ****************************************************************/

SetOfSmallInts singletonSet(int x);

/****************************************************************
 *                     rangeSet                                 *
 ****************************************************************
 * rangeSet(x,y) is the set {x,x+1,...,y}.  For example,        *
 * rangeSet(2,5) is the set {2,3,4,5}.                          *
 ****************************************************************/

SetOfSmallInts rangeSet(int x, int y);

/****************************************************************
 *                     size                                     *
 ****************************************************************
 * size(s) returns the number of members of set s.              *
 ****************************************************************/

int size(SetOfSmallInts s);

/****************************************************************
 *                     isEmpty                                  *
 ****************************************************************
 * isEmpty(s) is true if s is an empty set.                     *
 ****************************************************************/

bool isEmpty(SetOfSmallInts s);

/****************************************************************
 *                     isSingleton                              *
 ****************************************************************
 * isSingletonSet(s) is true if s is a singleton set.  That is, *
 * it is true if s has exactly one member.                      *
 ****************************************************************/

bool isSingleton(SetOfSmallInts s);

/****************************************************************
 *                     member                                   *
 ****************************************************************
 * member(x,s) is true if x is a member of s.                   *
 ****************************************************************/

bool member(int x, SetOfSmallInts s);

/****************************************************************
 *                     setDifference                            *
 ****************************************************************
 * setDifference(s,t) is the set of all numbers that are in s,  *
 * but not in t.                                                *
 ****************************************************************/

SetOfSmallInts setDifference(SetOfSmallInts s, SetOfSmallInts t);

/****************************************************************
 *                     setUnion                                 *
 ****************************************************************
 * setUnion(s,t) is the set of all numbers that are in either s *
 * or t (or both).                                              *
 ****************************************************************/

SetOfSmallInts setUnion(SetOfSmallInts s, SetOfSmallInts t);

/****************************************************************
 *                     setIntersection                          *
 ****************************************************************
 * setIntersection(s,t) is the set of all numbers that are in   *
 * both s and t.                                                *
 ****************************************************************/

SetOfSmallInts setIntersection(SetOfSmallInts s, SetOfSmallInts t);

/****************************************************************
 *                     insert                                   *
 ****************************************************************
 * insert(x,s) returns the set that you get by adding x to      *
 * set s.  So it is equivalent to setUnion(s, singletonSet(x)). *
 ****************************************************************/

SetOfSmallInts insert(int x, SetOfSmallInts s);

/****************************************************************
 *                     remove                                   *
 ****************************************************************
 * remove(x,s) returns the set that you get by removing x from  *
 * set s.  So it is equivalent to                               *
 * setDifference(s, singletonSet(x)).                           *
 ****************************************************************/

SetOfSmallInts remove(int x, SetOfSmallInts s);

/****************************************************************
 *                     smallest                                 *
 ****************************************************************
 * smallest(s) returns the smallest member of s.  If s is empty,*
 * then smallest(s) returns 0.                                  *
 ****************************************************************/

int smallest(SetOfSmallInts s);
