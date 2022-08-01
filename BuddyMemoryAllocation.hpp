#ifndef BUDDYMEMORYALLOCATION_H
#define BUDDYMEMORYALLOCATION_H

#include <bits/stdc++.h>

using namespace std;

class BuddyMemoryAllocation {

    public:

// Size of vector of pairs
int size;
 
// Global vector of pairs to track all
// the free nodes of various sizes
vector<pair<int, int>> arr[100000];
 
// Map used as hash map to store the
// starting address as key and size
// of allocated segment key as value
map<int, int> mp;
 
void Buddy(int s);

 
void allocate(int s);

 
void deallocate(int id);



};

#endif