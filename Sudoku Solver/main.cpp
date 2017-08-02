// Author:     Ibook Eyoita
// File:       main.cpp
// Tab stops:  4

//This program solves an unsolved sudoku puzzle.


#include <cstdio>
#include "intset.hpp"
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

typedef SetOfSmallInts** Puzzle;
typedef SetOfSmallInts** PuzzleSection;

enum SolutionStatus {solved, unsolvable, working};

SolutionStatus solve(Puzzle p);
SolutionStatus speculate(Puzzle p, int i, int j);

int trace1=0, trace2=1;
//==============================================================
//                       Tracing
//==============================================================
//==============================================================
// tracing(argc,*argv[]) sets the trace values.
//==============================================================
void tracing (int argc, char *argv[])
{
    for(int i=1; i<argc; i++)
    {
        if (strcmp(argv[i], "-t1=1") == 0)
        {
            trace1 = 1;
        }
        if(strcmp(argv[i], "-t1=2") == 0)
        {
            trace1 = 2;
        }
        if (strcmp(argv[i], "-t2=1") == 0)
        {
            trace2 = 1;
        }
        if (strcmp(argv[i], "-t2=2") == 0)
        {
            trace2 = 2;
        }
    }
}

//==============================================================
//                      newPuzzle
//==============================================================
// newPuzzle() returns a newly allocated puzzle.
//==============================================================

Puzzle newPuzzle()
{
    Puzzle p = new SetOfSmallInts*[9];
    
    for(int i = 0; i < 9; i++)
    {
        p[i] = new SetOfSmallInts[9];
    }
    return p;
}

//==============================================================
//                      deletePuzzle
//==============================================================
// deletePuzzle(p) deallocates puzzle p that was allocated
// using newPuzzle.
//==============================================================

void deletePuzzle(Puzzle p)
{
    for(int i = 0; i < 9; i++)
    {
        delete[] p[i];
    }
    delete[] p;
}

//==============================================================
//                      newPuzzleSection
//==============================================================
// newPuzzleSection() returns a newly allocates PuzzleSection.
//==============================================================

PuzzleSection newPuzzleSection()
{
    return new SetOfSmallInts*[9];
}

//==============================================================
//                      deletePuzzleSection
//==============================================================
// deletePuzzleSection(s) deallocates puzzle section s that
// was allocated by newPuzzleSection.
//==============================================================

void deletePuzzleSection(PuzzleSection s)
{
    delete[] s;
}

//==============================================================
//                      copySetArray
//==============================================================
// Parameters p and q are arrays of 9 sets.  Copy array p into
// array q.
//==============================================================

void copySetArray(SetOfSmallInts* q, SetOfSmallInts* p)
{
    for(int i = 0; i < 9; i++)
    {
        q[i] = p[i];
    }
}

//==============================================================
//                      copyPuzzle
//==============================================================
// Copy puzzle p into q.  For example, if p is a puzzle, then
//    Puzzle q = newPuzzle();
//    copyPuzzle(q, p);
// stores a copy of puzzle p into q.  (Only allocate q if it
// was not already allocated.)
//==============================================================

void copyPuzzle(Puzzle q, Puzzle p)
{
    for(int i = 0; i < 9; i++)
    {
        copySetArray(q[i], p[i]);
    }
}

//==============================================================
//                      getRow
//==============================================================
// Store the i-th row of puzzle p into puzzle section S.
// The rows are numbered from 0 to 8.
//
// After doing this, the k-th set in row i is *(S[k]).
// The cells in the row are numbered 0,1,...,8.
//==============================================================

void getRow(PuzzleSection S, Puzzle p, int i)
{
    for(int j = 0; j < 9; j++)
    {
        S[j] = &(p[i][j]);
    }
}

//==============================================================
//                      getColumn
//==============================================================
// Store the j-th column of puzzle p into puzzle section S.
// The columns are numbered from 0 to 8.
//
// After doing this, the k-th set in column j is
// *(S[i]).  The cells in the column are numbered 0,1,...,8.
//==============================================================

void getColumn(PuzzleSection S, Puzzle p, int j)
{
    for(int i = 0; i < 9; i++)
    {
        S[i] = &(p[i][j]);
    }
}

//==============================================================
//                      getSquare
//==============================================================
// Store the k-th square of puzzle p into puzzle section S.
// The squares are numbered as follows.
//           0 1 2
//           3 4 5
//           6 7 8
// For example, square 4 is the middle square in the puzzle.
//
// After doing getSquare, the i-th set in the square is *(S[i]).
// The cells in the square are numbered 0,1,...,8, in the same
// pattern shown above for the squares themselves.
// For example *(R[3]) is the first position in the second row
// of the square.
//==============================================================

void getSquare(PuzzleSection S, Puzzle p, int k)
{
    for(int i = 0; i < 9; i++)
    {
        S[i] = &(p[k - k%3 + i/3][3*(k%3) + i%3]);
    }
}

//==============================================================
//                      readRow
//==============================================================
// readRow(p,i) reads a row from the standard input and stores it
// into the i-th row of p.
//==============================================================

void readRow(Puzzle p, int i)
{
    char c;
    for(int j=0; j<9; j++)
    {
        scanf(" %c", &c);
        if(c == '-')
        {
            p[i][j]= rangeSet(1, 9);
        }
        else
        {
            p[i][j]= singletonSet(c-'0');
        }
    }
}

//==============================================================
//                      readPuzzle
//==============================================================
// readPuzzle()  reads from the standard input.
//==============================================================

Puzzle readPuzzle()
{
    Puzzle p = newPuzzle();
    for(int i=0; i<9; i++)
    {
        readRow(p,i);
    }
    return p;
}

//==============================================================
//                      printRow
//==============================================================
// printRow(p,i) prints the i-th row in Puzzle p.
//==============================================================
void printRow(Puzzle p, int i)
{
    int s;
    for(int j= 0; j<9; j++)
    {
        if(isSingleton(p[i][j]))
        {
            s=smallest(p[i][j]);
            printf("%i",s);
        }
        else if(isEmpty(p[i][j]))
        {
            printf("*");
        }
        else
        {
            printf("-");
        }
        if( j==2 || j==5)
        {
            printf("  ");
        }
        
    }
}

//==============================================================
//                      printPuzzle
//==============================================================
// printPuzzle(p) prints the rows in Puzzle p.
//==============================================================
void printPuzzle(Puzzle p)
{
    for(int i = 0; i < 9; i++)
    {
        printRow(p,i);
        printf("\n");
        if( i==2 || i==5)
        {
            printf("\n");
        }
    }
}

//==============================================================
//                      printSet
//==============================================================
// printSet(s)  prints values from s if the value is a member of
// s.
//==============================================================
void printSet(SetOfSmallInts s)
{
    for(int x=1; x<=9; x++)
    {
        if(member(x,s))
        {
            printf("%i",x);
        }
    }
}

//==============================================================
//                      Format
//==============================================================
// Format(x) prints out spaces depending on the amount of the
// input
//==============================================================

void format(int x)
{
    for(int i=1; i<=x ; i++)
    {
        printf(" ");
    }
}

//==============================================================
//                      showRow
//==============================================================
// showRow(p,i) displays the i-th row with all the values in each
// set in Puzzle p.
//==============================================================
void showRow(Puzzle p, int i)
{
    for(int j=0; j<9; j++)
    {
        int spacesAvailable = size(p[i][j]);
        if(isEmpty(p[i][j]))
        {
            printf("*");
        }
        else
        {
            printSet(p[i][j]);
            format(10- spacesAvailable);
        }
    }
}

//==============================================================
//                      showPuzzle
//==============================================================
// showPuzzle(p,i) displays Puzzle p with all the values in each
// row.
//==============================================================
void showPuzzle(Puzzle p)
{
    for(int i=0; i<9; i++)
    {
        showRow(p,i);
        printf("\n");
    }
}

//==============================================================
//                   trace1PosBegin
//==============================================================
//trace1PosBegin(p) prints Puzzle p before running through
//tactic 1
//==============================================================
void trace1PosBegin(Puzzle p)
{
    if(trace1 > 0)
    {
        printf("Tactic 1: Here is your initial puzzle.\n");
        showPuzzle(p);
    }
}

//==============================================================
//                   trace1PosEnd
//==============================================================
//tracePos1End(p) prints Puzzle p after runinning through
//tactic 1.
//==============================================================
void tracePos1End(Puzzle p)
{
    if(trace1 > 0)
    {
        printf("\n\nTactic 1: Here is your puzzle afterwards \n");
        showPuzzle(p);
    }
}

//==============================================================
//                   printSection
//==============================================================
//printSection(sec) prints out the section
//==============================================================
void printSection(PuzzleSection sec)
{
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            if(member(j,*(sec[i])))
            {
                printf("%i",j);
            }
        }
        int spaces = size(*(sec[i]));
        format(10- spaces);
    }
}

//==============================================================
//                   traceSectionBefore
//==============================================================
//traceSectionBefore(sec,i) prints PuzzleSection sec after i.
//==============================================================
void traceSectionBefore(PuzzleSection sec, int i)
{
    if(trace1 > 1)
    {
        printf("\nTactic 1: section %i before \n\n", i);
        printSection(sec);
    }
}

//==============================================================
//                   traceSectionAfter
//==============================================================
//traceSectionAfter(sec,i) prints PuzzleSection sec after i.
//==============================================================
void traceSectionAfter(PuzzleSection sec, int i)
{
    if(trace1 > 1)
    {
        printf("\nTactic 1: section %i after \n\n", i);
        printSection(sec);
    }
}

//==============================================================
//                   tac1helper
//==============================================================
//tac1helper(i,val,sec,result) returns the result,true,
//if changes were actually made by removing val
//from a cell in the Puzzlesection sec without removing the
//singleton set i.
//==============================================================
bool tac1helper(int i, int val, PuzzleSection sec, bool result)
{
    for(int count=0; count<9; count++)
    {
        if(count!=i && member(val,*(sec[count])))
        {
            SetOfSmallInts som= *(sec[count]);
            *(sec[count])= remove(val,*(sec[count]));
            if(smallest(setDifference(som,*sec[count])))
            {
                result = true;
            }
        }
    }
    return result;
}

//==============================================================
//                   tacticOneOnSection
//==============================================================
//tacticOneOnSection(sec) returns true if any changes were
//made on the PuzzleSection.
//==============================================================

bool tacticOneOnSection(PuzzleSection sec)
{
    bool result = false;
    for(int i=0; i<9; i++)
    {
        if(isSingleton(*(sec[i])))
        {
            int val= smallest(*(sec[i]));
            result = tac1helper(i,val,sec,result);
        }
    }
    return result;
}

//==============================================================
//                   tacticOne
//==============================================================
//tacticOneOnSection(p) returns true if any changes were
//made on the Puzzle.
//==============================================================
bool tacticOne(Puzzle p)
{
    bool result = false;
    PuzzleSection sec = newPuzzleSection();
    trace1PosBegin(p);
    for(int i =0; i< 9; i++)
    {
        
        getRow(sec, p, i);
        traceSectionBefore(sec, i);
        if(tacticOneOnSection(sec))
        {
            result = true;
        }
        
        traceSectionAfter(sec, i);
        
        getColumn(sec, p, i);
        traceSectionBefore(sec, i);
        if(tacticOneOnSection(sec))
        {
            result= true;
        }
        traceSectionAfter(sec, i);
        
        getSquare(sec, p, i);
        traceSectionBefore(sec, i);
        if(tacticOneOnSection(sec))
        {
            result= true;
        }
        traceSectionAfter(sec,i);
    }
    tracePos1End(p);
    return result;
}

//==============================================================
//                   allSingleton
//==============================================================
//allSingleton(p) returns true if all the sets in the puzzle are
//singleton.
//==============================================================
bool allSingleton(Puzzle p)
{
    for(int i =0; i< 9; i++)
    {
        for(int j= 0; j<9; j++)
        {
            if(!isSingleton(p[i][j]))
            {
                return false;
            }
        }
    }
    return true;
}

//==============================================================
//                   anEmptySet
//==============================================================
//anEmptySet(p) returns true if there exists a set in the puzzle
//that is empty.
//==============================================================
bool anEmptySet(Puzzle p)
{
    for(int i =0; i< 9; i++)
    {
        for(int j= 0; j<9; j++)
        {
            if(isEmpty(p[i][j]))
            {
                return true;
            }
        }
    }
    return false;
}

//==============================================================
//						Speculate
//==============================================================
//speculate creates a copied puzzle and tries to solve the puzzle
//==============================================================
SolutionStatus speculate(Puzzle p, int i, int j)
{
    if(trace2 > 1)
    {
        printf("Speculate begins \n");
        showPuzzle(p);
    }
    Puzzle q = newPuzzle();
    for(int count =1; count<=9; count++)
    {
        if (member(count, p[i][j]))
        {
            if(trace2 > 0)
            {
                printf("speculating %i at (%i,%i) \n", count, i, j);
            }
            copyPuzzle(q, p);
            q[i][j]= rangeSet(count, count);
            if(solve(q) == unsolvable)
            {
                if(trace2 > 0)
                {
                    printf("The puzzle at (%i,%i) is not %i\n", i,j, count);
                    
                }
            }
            else if (solve(q) == solved)
            {
                if(trace2 > 0)
                {
                    printf("The puzzle at (%i,%i) is %i\n",i,j,count);
                }
                copyPuzzle(p, q);
                if(trace2 > 1)
                {
                    printf("Speculate ends \n");
                    showPuzzle(q);
                }
                deletePuzzle(q);
                return solved;
            }
        }
    }
    if(trace2 > 1)
    {
        printf("\nSpeculate ends.");
        showPuzzle(q);
    }
    return unsolvable;
}


//==============================================================
//						Tactic 2
//==============================================================
//tactic2 checks to see if Puzzle p does not have a singletonset
//It then speculates them.
//==============================================================
SolutionStatus tactic2(Puzzle p)
{
    for(int i =0; i<9; i++)
    {
        for (int j= 0; j<9; j++)
        {
            if(!isSingleton(p[i][j]))
            {
                if(speculate(p, i, j)== solved)
                {
                    return solved;
                }
                else
                {
                    return unsolvable;
                }
            }
        }
    }
    return unsolvable;
}

//==============================================================
//						Solve
//==============================================================
//solve(p) returns the status of the puzzle after running
//tacticOne.
//==============================================================
SolutionStatus solve(Puzzle p)
{
    
    while(tacticOne(p))
    {
    }
    if(anEmptySet(p))
    {
        return unsolvable;
    }
    if(allSingleton(p))
    {
        return solved;
    }
    if(tactic2(p) == unsolvable)
    {
        return unsolvable;
    }
    if(allSingleton(p))
    {
        return solved;
    }
    else
    {
        return working;
    }
}

//==============================================================
//                       main
//==============================================================

int main(int argc, char** argv)
{
    SolutionStatus n;
    tracing(argc,argv);
    Puzzle p;
    p = readPuzzle();
    printf("\nHere is your initial puzzle \n");
    printPuzzle(p);
    n =solve(p);
    if(n == unsolvable)
    {
        printf("\nNo solution for the puzzle\n");
    }
    else
    {
        printf("\nHere is your solved puzzle \n");
        printPuzzle(p);
        printf("\n");
    }
    return 0;
}
