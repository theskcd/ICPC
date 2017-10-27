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

bitset<(int)(1<<10)> bits[201];
vector<string> stringsB;
vector<string> stringsE;

void solve(string s, int index) {
    int s1 = sz(s);
    FOR(length1, 1, min(sz(s), 9)) {
        // pr(s);
        FOR(j, 0, sz(s)- length1) {
            int val1 = 0;
            // pr(j);
            FOR(k, j, j+length1-1) {
                val1 = val1*2 + (s[k]-'0');
            }
            // pr(val1);
            bits[index].set(val1);
        }
    }
}

void convulate(string firstHalf, string secondHalf, int index1) {
    FOR(l1, 1, sz(firstHalf)) {
        FOR(l2, 1, sz(secondHalf)) {
            string temp = firstHalf.substr(sz(firstHalf)-l1, l1) + secondHalf.substr(0, l2);
            int val1 = 0;
            FOR(k, 0, sz(temp)-1) {
                val1 = 2*val1 + temp[k]-'0';
            }
            bits[index1].set(val1);
        }
    }
}

ll findAnswer(int index) {
    ll answer1 = 0;
    FOR(i, 0, (1<<9)-1) {
        if (!bits[index][i]) {
            break;
        }
        if (!(i & (i-1))) {
            answer1 = __builtin_popcount(i-1);
        }
    }
    return answer1;
}

int main() {
    fastio
    int n;
    scanf("%d", &n);

    FOR(i, 0, n-1) {
        string temp;
        cin>>temp;
        if (sz(temp)<=9) {
            stringsB.pb(temp);
            stringsE.pb(temp);
        } else {
            stringsB.pb(temp.substr(0, 10));
            stringsE.pb(temp.substr(sz(temp)-10, 10));
        }
        solve(temp, i);
    }

    int m;
    scanf("%d", &m);
    FOR(i, 0, m-1) {
        int a1, b1;
        cin>>a1>>b1;
        a1--;
        b1--;
        stringsB.pb(stringsB[a1]);
        stringsE.pb(stringsE[b1]);
        bits[n+i] = bits[a1] | bits[b1];
        convulate(stringsE[a1], stringsB[b1], n+i);
        printf("%lld\n", findAnswer(n+i));
    }
return 0;}