#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (int)(a); i <= (int)(b); i++)
#define NFOR(i,a,b) for(int i = (int)(a); i >= (int)(b); --i)
#define endl "\n"
#define mp make_pair
#define X first
#define Y second
#define inf 1e18
#define mod 1000000007
#define pb push_back
#define Case cout<<"Case #"<<++cas<<": ";
#define fastio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define all(v) v.begin(),v.end()
#define sz(x) int(x.size())
// #define lli int
typedef long long int lli;
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<pii> vii;
typedef pair<lli,lli> pll;
typedef vector<lli> vl;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vl> vvl;

#define pr(...) dbs(#__VA_ARGS__, __VA_ARGS__)
template <class T> void dbs(string str, T t) {cerr << str << " : " << t << "\n";}
template <class T, class... S> void dbs(string str, T t, S... s) {int idx = str.find(','); cerr << str.substr(0, idx) << " : " << t << ","; dbs(str.substr(idx + 1), s...);}
template <class S, class T>ostream& operator <<(ostream& os, const pair<S, T>& p) {return os << "(" << p.first << ", " << p.second << ")";}
template <class T>ostream& operator <<(ostream& os, const vector<T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class T>ostream& operator <<(ostream& os, const set<T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class S, class T>ostream& operator <<(ostream& os, const map<S, T>& p) {os << "[ "; for (auto& it : p) os << it << " "; return os << "]";}
template <class T> void prc(T a, T b) {cerr << "["; for (T i = a; i != b; ++i) {if (i != a) cerr << ", "; cerr << *i;} cerr << "]\n";}

int a[100010];
ll dp[100010][24];
int l, r = -1;
ll currentVal = 0;
int f[100010];

ll get(int L, int R) {
    while (l< L) {
        currentVal -= --f[a[l++]];
    }
    while(L < l) {
        currentVal += f[a[--l]]++;
    }
    while(R < r) {
        currentVal -= --f[a[r--]];
    }
    while(r < R) {
        currentVal += f[a[++r]]++;
    }
    return currentVal;
}

void solve(int l1, int l2, int p1, int p2, int k) {
    if (l1 > l2) {
        return;
    }
    int lm = (l1 +l2)/2;
    get(p1, lm);
    dp[lm][k] = 10000000000000;
    ll prevSum = 0;
    int pointer = -1;
    FOR(i, p1, min(p2, lm)) {
        ll currVal = dp[i-1][k-1] + get(i, lm);
        if (dp[lm][k] > currVal) {
            dp[lm][k] = currVal;
            pointer = i;
        }
    }
    // pr(dp[lm][k], lm, k);
    if (l1 == l2) {
        return;
    }
    solve(l1, lm-1, p1, pointer, k);
    solve(lm+1, l2, pointer, p2, k);
}

int main() {
    int n, k;
    cin>>n>>k;

    FOR(i, 0, n-1) {
        cin>>a[i];
    }

    FOR(i, 0, n-1) {
        dp[i][0] = 1e15;
    }

    FOR(i, 0, n-1) {
        dp[i][1] = get(0, i);
        // pr(dp[i][1], i, 1);
    }

    FOR(i, 2, k) {
        FOR(j, 1, i-1) {
            dp[j][i] = 1e15;
        }
        solve(i-1, n-1, i-1, n-1, i);
    }

    cout<<dp[n-1][k]<<endl;
return 0;}