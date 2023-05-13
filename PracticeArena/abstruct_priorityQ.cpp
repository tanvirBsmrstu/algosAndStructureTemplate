/*      TANVIR HASAN */

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <string>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <bitset>

#include <bits/stdc++.h>
using namespace std;

#define uu         first
#define vv         second
#define pb         push_back
#define mp         make_pair
#define LL         long long
#define inf        INT_MAX/3
#define mod        1000000007ll
#define PI         acos(-1.0)
#define linf       (1ll<<60)-1
#define pii        pair<int,int>
#define vl        vector<LL>
#define vi        vector<int>
#define vs        vector<string>
#define pii        pair<int,int>


#define ALL(A)     (A).begin(),(A).end()
#define mset(a,v)     memset(a,v,sizeof a)
#define setinf(ar)  memset(ar,126,sizeof ar)
#define vsort(v)   sort(v.begin(),v.end())

#define FOR(I,A,B) for (__typeof (B) I = (A) ; I <= B ; ++I)
#define rof(i, a, b)	for (__typeof (b)i = (b) ; i >= a ; --i)
#define rep(i, n)		FOR (i, 0, (n) - 1)
#define per(i, n)		for (__typeof (n)i = (n-1) ; i >= 0 ; --i)
#define forstl(I, s)	for (__typeof ((s).end ()) I = (s).begin (); I != (s).end (); ++I)
#define rofstl(I, s)	for (__typeof ((s).end ()) I = (s).end ()-1; I != (s).begin (); --I)

#define Int ({int a; scanf("%d", &a); a;})
#define I64 ({LL a; scanf("%I64d", &a); a;})
#define Double ({double a; scanf("%lf", &a); a;})
#define Char ({char a; scanf("%c", &a); a;})


const int  mx =(int) 1e6 +5;

struct nd
{
    int xi,vlu;
    nd()
    {
        vlu=0,xi=0;
    }
};

class AA
{
public:
    bool operator() (const nd& NN, const nd& Nb) const
    {
        return NN.vlu>Nb.vlu; ///min
    }
};

int pp[mx];
int sts[mx];
priority_queue<nd,vector<nd>,AA> pq;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //freopen("in.txt","r",stdin);
    int n,k,q;
    n=Int;
    k=Int;
    q=Int;
    FOR(i,1,n)
    {
        pp[i]=Int;
        sts[i]=0;
    }
    FOR(i,1,q)
    {
        int qq,qp;
        qq=Int;
        qp=Int;
        if(qq==1)
        {
            if(pq.size()<k)
            {
                nd NN;
                NN.vlu=pp[qp];
                NN.xi=qp;
                pq.push(NN);
                sts[qp]=1;
            }
            else
            {
                nd Ak=pq.top();
                if(Ak.vlu<pp[qp])
                {
                    pq.pop();
                    sts[Ak.xi]=0;
                    Ak.vlu=pp[qp];
                    Ak.xi=qp;
                    pq.push(Ak);
                    sts[qp]=1;
                }
            }
        }
        else if (qq==2)
        {
            if(sts[qp]==0) printf("NO\n");
            else if (sts[qp]==1) printf("YES\n");

        }
    }
    return 0;

}
