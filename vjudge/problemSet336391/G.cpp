#include <iostream>
#include <stack>
#include <queue>
#include <string>

using namespace std;

int N,n,tmp;
string cmd,ans;
stack<int> filo;
queue<int> fifo;
string io;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>N;
    for(int it=0;it<N;++it)
    {
        cin>>n>>cmd;
        if(cmd=="FIFO")
        {
            while(!fifo.empty())fifo.pop(); //SIGSEGV
            for(int i=0;i<n;++i)
            {
                cin>>cmd;
                if(cmd=="IN")
                {
                    cin>>tmp;
                    fifo.push(tmp);
                }
                else
                {
                    if(fifo.empty())io+="None";
                    else 
                    {
                        io+=to_string(fifo.front());
                        fifo.pop();
                    }
                    io+='\n';
                }
            }
        }
        else
        {
            while(!filo.empty())filo.pop();
            for(int i=0;i<n;++i)
            {
                cin>>cmd;
                if(cmd=="IN")
                {
                    cin>>tmp;
                    filo.push(tmp);
                }
                else
                {
                    if(filo.empty())io+="None";
                    else 
                    {
                        io+=to_string(filo.top());
                        filo.pop();
                    }
                    io+='\n';
                }
            }
        }
    }

    //io = io.substr(0,io.length()-1);
    cout<<io;
    return 0;
}