#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,tune=native")
#include <bits/stdc++.h>
using namespace std;
const int MOD=1000000007;
typedef long long ll;
#define pii pair<int, int>

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

void nxtgen(int state[9],int turn){
    if(!turn){
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

pair<pii,int> orz(int stat[9],int turn,int cnt){ //->win,maxcnt,best_move
    
    int state[9];
    for(int i=0;i<9;i++) state[i]=stat[i];
        // for(int i=0;i<9;i++) cout<<state[i]<<" ";
        // cout<<"   "<<turn<<" "<<cnt<<endl;
    if(cnt==15) return {{0,15},-1};
    int gone=-1;
    int line[3]={0};
    if(turn){
        int encode=0;
        for(int i=0;i<9;i++){
            if(state[i]==1) gone=i;
            if(state[i]>0) state[i]--;
            else if(state[i]<0){
                encode=10*encode+i+1;
            }
        }
        //if enemy line
        for(auto i:win){
            if(encode==i) return {{-1,cnt},-1};
        }
        pii winans={100,-1}; //win=1 //mxcnt,best_move
        pii loseans={-100,-1}; //win=-1
        int drawans=-1; //bestmove
        for(int i=0;i<9;i++){
            if(state[i]==0 && i!=gone){
                state[i]=3;
                pii ret=orz(state,0,cnt+1).first;
                state[i]=0;
    
                if(ret.first==1 && ret.second<winans.first) winans={ret.second,i};
                if(ret.first==-1 && ret.second>loseans.first) loseans={ret.second,i};
                if(ret.first==0) drawans=i;
            }
        }
        if(winans.first!=100) return {{1,winans.first},winans.second};
        else if(drawans!=-1) return {{0,100},drawans};
        else return {{-1,loseans.first},loseans.second};
    }
    else{
        int encode=0;
        for(int i=0;i<9;i++){
            if(state[i]==-1) gone=i;
            if(state[i]<0) state[i]++;
            else if(state[i]>0){
                encode=10*encode+i+1;
            }
        }
        //if enemy line
        for(auto i:win){
            if(encode==i) return {{1,cnt},-1};
        }

        pii winans={100,-1};//-1
        pii loseans={-100,-1};//1
        int drawans=-1;
        for(int i=0;i<9;i++){
            if(state[i]==0 && i!=gone){
                state[i]=-3;
                pii ret=orz(state,1,cnt+1).first;
                state[i]=0;
    
                if(ret.first==-1 && ret.second<winans.first) winans={ret.second,i};
                if(ret.first==1 && ret.second>loseans.first) loseans={ret.second,i};
                if(ret.first==0) drawans=i;
            }
        }
        if(winans.first!=100) return {{-1,winans.first},winans.second};
        else if(drawans!=-1) return {{0,100},drawans};
        else return {{1,loseans.first},loseans.second};
    }

}


signed main(){
    system("");
    int state[9]={0};
    // for(int i=0;i<9;i++){
    //     cin>>state[i];
    // }
    cout<<"1 2 3\n4 5 6\n7 8 9\n";
    cout<<"----------------\n";
    // display(state);
    while(1){
        int q=input(state,"ur");
        state[q]=4;
        nxtgen(state,0);
        display(state);

        auto[tmp,c]=orz(state,0,0);
        auto[a,b]=tmp;
        cout<<"debug: "<<a<<" "<<b<<" "<<c<<"\n";
        if(b==0){
            cout<<"u win!!Orz_Orz_Orz\n";
            system("pause");
            return 0;
        }
        cout<<"cpu move: "<<c<<"\n";
        state[c]=-4;
        nxtgen(state,1);
        display(state);
        cout<<"----------------\n";
        if(b==1){
            cout<<"cpu win\n";
            system("pause");
            return 0;
        }
    }
    // cout<<orz(state,0,0);
}