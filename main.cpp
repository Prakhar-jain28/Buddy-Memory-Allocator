#include <bits/stdc++.h>
#include "BuddyMemoryAllocation.hpp"
using namespace std;
 

 
// Driver code
int main()
{
     
    
    int total,c,req;
    cout<<"Enter Total Memory Size (in Bytes) => ";
    cin>>total;


    BuddyMemoryAllocation obj1;
    obj1.Buddy(total);


    label:
    while(1)
    {
        cout<<"\n1. Add Process into Memory\n2. Remove Process\n3. Exit\n=> ";
        cin>>c;
        switch(c)
        {
            case 1:
            cout<<"Enter Process Size (in Bytes) => ";
            cin>>req;
            cout<<"\n===>";
            obj1.allocate(req);
            break;
 
            case 2:
            cout<<"Enter Starting Address => ";
            cin>>req;
            cout<<"\n===>";
            obj1.deallocate(req);
            break;
 
            case 3:
            exit(0);
            break;
 
            default:
            goto label;
        }
    }
     
 
    return 0;
}