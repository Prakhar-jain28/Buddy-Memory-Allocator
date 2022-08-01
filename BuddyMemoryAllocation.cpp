#include "BuddyMemoryAllocation.hpp"


 
void BuddyMemoryAllocation::Buddy(int s)
{
     
    // Maximum number of powers of 2 possible
    int n = ceil(log(s) / log(2));
     
    size = n + 1;
    for(int i = 0; i <= n; i++)
        arr[i].clear();
 
    // Initially whole block of specified
    // size is available
    arr[n].push_back(make_pair(0, s - 1));
}
 
void BuddyMemoryAllocation::allocate(int s)
{
     
    // Calculate index in free list
    // to search for block if available
    int x = ceil(log(s) / log(2));
     
    // Block available
    if (arr[x].size() > 0)
    {
        pair<int, int> temp = arr[x][0];
 
        // Remove block from free list
        arr[x].erase(arr[x].begin());
         
        cout << "Memory from " << temp.first
             << " to " << temp.second
             << " allocated" << "\n";
 
        // Map starting address with
        // size to make deallocating easy
        mp[temp.first] = temp.second -
                         temp.first + 1;
    }
    else
    {
        int i;
         
        // If not, search for a larger block
        for(i = x + 1; i < size; i++)
        {
             
            // Find block size greater
            // than request
            if (arr[i].size() != 0)
                break;
        }
 
        // If no such block is found
        // i.e., no memory block available
        if (i == size)
        {
            cout << "Sorry, failed to allocate memory\n";
        }
         
        // If found
        else
        {
            pair<int, int> temp;
            temp = arr[i][0];
 
            // Remove first block to split
            // it into halves
            arr[i].erase(arr[i].begin());
            i--;
             
            for(;i >= x; i--)
            {
                 
                // Divide block into two halves
                pair<int, int> pair1, pair2;
                pair1 = make_pair(temp.first,
                                  temp.first +
                                 (temp.second -
                                  temp.first) / 2);
                pair2 = make_pair(temp.first +
                                 (temp.second -
                                  temp.first + 1) / 2,
                                  temp.second);
                                  
                arr[i].push_back(pair1);
 
                // Push them in free list
                arr[i].push_back(pair2);
                temp = arr[i][0];
 
                // Remove first free block to
                // further split
                arr[i].erase(arr[i].begin());
            }
             
            cout << "Memory from " << temp.first
                 << " to " << temp.second
                 << " allocated" << "\n";
                  
            mp[temp.first] = temp.second -
                             temp.first + 1;
        }
    }
}
 
void BuddyMemoryAllocation::deallocate(int id)
{
     
    // If no such starting address available
    if(mp.find(id) == mp.end())
    {
        cout << "Sorry, invalid free request\n";
        return;
    }
     
    // Size of block to be searched
    int n = ceil(log(mp[id]) / log(2));
     
    int i, buddyNumber, buddyAddress;
 
    // Add the block in free list
    arr[n].push_back(make_pair(id,
                               id + pow(2, n) - 1));
    cout << "Memory block from " << id
         << " to "<< id + pow(2, n) - 1
         << " freed\n";
 
    // Calculate buddy number
    buddyNumber = id / mp[id];
 
    if (buddyNumber % 2 != 0)
        buddyAddress = id - pow(2, n);
    else
        buddyAddress = id + pow(2, n);
         
    // Search in free list to find it's buddy
    for(i = 0; i < arr[n].size(); i++)
    {
         
        // If buddy found and is also free
        if (arr[n][i].first == buddyAddress)
        {
             
            // Now merge the buddies to make
            // them one large free memory block
            if (buddyNumber % 2 == 0)
            {
                arr[n + 1].push_back(make_pair(id,
                   id + 2 * (pow(2, n) - 1)));
                    
                cout << "Coalescing of blocks starting at "
                     << id << " and " << buddyAddress
                     << " was done" << "\n";
            }
            else
            {
                arr[n + 1].push_back(make_pair(
                    buddyAddress, buddyAddress +
                    2 * (pow(2, n))));
                     
                cout << "Coalescing of blocks starting at "
                     << buddyAddress << " and "
                     << id << " was done" << "\n";
            }
            arr[n].erase(arr[n].begin() + i);
            arr[n].erase(arr[n].begin() +
            arr[n].size() - 1);
            break;
        }
    }
 
    // Remove the key existence from map
    mp.erase(id);
}


