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

int bitVal[11];
int typeBit[11];

int main() {
    int n;
    cin >> n;
    FOR(i, 0, n-1) {
        string type;
        int num;
        cin>>type>>num;
        if (type[0] == '|') {
            FOR(j, 0, 9) {
                if (num & (1<<j)) {
                    //nothing changes
                    typeBit[j] = 1;
                    bitVal[j] = 1;
                }
            }
        } else if(type[0] == '&') {
            FOR(j, 0, 9) {
                if (!(num & (1<<j))) {
                    typeBit[j] = 1;
                    bitVal[j] = 0;
                }
            }
        } else if(type[0] == '^') {
            FOR(j, 0, 9) {
                if (num & (1<<j)) {
                    bitVal[j] ^= 1;
                } else {
                    bitVal[j] ^= 0;
                }
                // bitVal[j] ^= (num & (1<<j));
            }
        }
    }

    // get the fixed value
    int val1 = 0;
    // get values which should be set to 0
    int val3 = 0;
    // FOR(i, 0, 9) {
    //     pr(i, bitVal[i], typeBit[i]);
    // }
    FOR(i , 0, 9) {
        if (typeBit[i] == 1) {
            if (bitVal[i] != 0) {
                val3 += (1<<i);
            }
        } else {
            val3 += (1<<i);
        }
    }

    FOR(i, 0, 9) {
        if (typeBit[i] == 1) {
            if (bitVal[i] == 1) {
                val1 += (1<<i);
            }
        }
    }

    //get the variable value
    int val2 = 0;
    FOR(i, 0, 9) {
        if (typeBit[i] == 0) {
            val2 += bitVal[i]* (1<<i);
        }
    }

    // pr(val1, val2);
    // FOR(i, 0, 10) {
    //     pr(type[i], bitVal[i]);
    // }

    cout << "3\n";
    cout <<"& "<<val3<<"\n";
    cout <<"| "<<val1<<"\n";
    cout <<"^ "<<val2<<"\n";
return 0;}