#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,tune=native")
#include <bits/stdc++.h>
using namespace std;
const int MOD=1000000007;
#define pii pair<int, int>

#define watch(x) cout << (#x) << ':' << (x) << '\n';

template<typename T,typename Y>
ostream& operator<<(ostream& os, const pair<T,Y>& v){
    os << v.first << ' ' <<v.second;
    return os;
}

int win[8]={123,456,789,147,258,369,159,357};

int input(int state[9],string name){
    int q;
    here:cout<<name<<" move: ";
    cin>>q;
    q--; // 0base
    if( q>8 || q<0 || state[q]!=0 ){
        cout<<"invalid move\n";
        goto here;
    }
    return q;
}

bool iswin(int state[9],int who){//who=1 or -1
    int sum=0;
    for(int i=0;i<9;i++){
        if(state[i]*who>0){
            sum*=10;
            sum+=i+1;
        }
    }
    for(auto i:win){
        if(sum==i) return 1;
    }
    return 0;
}

void nxtgen(int state[9],int turn){
    if(turn){
        for(int i=0;i<9;i++){
            if(state[i]>0) state[i]--;
        }
    }
    else{
         for(int i=0;i<9;i++){
            if(state[i]<0) state[i]++;
        }
    }
}

void display(int state[9]){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(state[i*3+j]<0) cout<<"\033[91m"<<state[i*3+j]<<"\033[0m ";
            else if(state[i*3+j]>0) cout<<" \033[94m"<<state[i*3+j]<<"\033[0m ";
            else cout<<" 0 ";
        }
        cout<<"\n";
    }
    return;
}

signed main(){
    system("");
    int state[9]={0};
    cout<<"1 2 3\n4 5 6\n7 8 9\n";
    cout<<"----------------\n";
    int q;
    while(1){
        q=input(state,"1");
        state[q]=4;
        nxtgen(state,1);
        display(state);
        if(iswin(state,1)){
            cout<<"omg player1 wins!! Orz\n";
            system("pause");
            return 0;
        }

        q=input(state,"2");
        state[q]=-4;
        nxtgen(state,0);
        display(state);
        if(iswin(state,-1)){
            cout<<"omg player2 wins!! Orz\n";
            system("pause");
            return 0;
        }
        cout<<"----------------\n";
    }
    // cout<<orz(state,0,0);
}