#include <iostream>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

struct GenerateSubsetsCall{
    int start_index;
    int cur_index;
    int cur_subset[100];
};

void GenerateSubsets(int *a, int n ,int k)
{
    GenerateSubsetsCall stcall;
    stcall.cur_index = 0;
    stcall.start_index = 0;
    stack<GenerateSubsetsCall> s;
    s.push(stcall);

    while(!s.empty()){
        GenerateSubsetsCall call = s.top(); s.pop();
        /// Base case.
        if(call.start_index == n)
        {
            int index = 0;
            /// enter here if size of stack equal subsets of size k.
             if(call.cur_index == k)
             {
                   cout<<"{";
                while(index<call.cur_index)
                {
                  cout<<call.cur_subset[index++];
                  if(index != call.cur_index) cout<<",";
                }
                cout<<"}"<<endl;
             }
              continue;
        }

        ///First recursion .
        GenerateSubsetsCall C1;
        C1.start_index = call.start_index+1;
        C1.cur_index = call.cur_index;
        for(int i=0; i<C1.cur_index; i++){
            C1.cur_subset[i] = call.cur_subset[i];
        }
        call.cur_subset[call.cur_index] = a[call.start_index];


        /// Second recursion .
        GenerateSubsetsCall C2;
        C2.start_index = call.start_index+1;
        C2.cur_index = call.cur_index+1;
        for(int i=0; i<C2.cur_index; i++){
            C2.cur_subset[i] = call.cur_subset[i];
        }
        s.push(C2);
        s.push(C1);
    }
}


int main()
{

    int k=3;
    int a[]={1,3,5,8,10}; int n=sizeof(a)/sizeof(a[0]);
    GenerateSubsets(a, n ,k );

    /// Output.
    /*
    {5,8,10}
    {3,8,10}
    {3,5,10}
    {3,5,8}
    {1,8,10}
    {1,5,10}
    {1,5,8}
    {1,3,10}
    {1,3,8}
    {1,3,5}
    */

    return 0;
}
