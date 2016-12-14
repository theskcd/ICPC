#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

//using namespace __gnu_pbds;
using namespace std;

// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・

#define Foreach(i, c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define For(i,a,b) for(int (i)=(a);(i) < (b); ++(i))
#define rof(i,a,b) for(int (i)=(a);(i) > (b); --(i))
#define rep(i, c) for(auto &(i) : (c))
#define x first
#define y second
#define pb push_back
#define mp make_pair
#define PB pop_back()
#define iOS ios_base::sync_with_stdio(false)
#define sqr(a) (((a) * (a)))
#define all(a) a.begin() , a.end()
#define error(x) cerr << #x << " = " << (x) <<endl
#define Error(a,b) cerr<<"( "<<#a<<" , "<<#b<<" ) = ( "<<(a)<<" , "<<(b)<<" )\n";
#define Error3(a,b,c) cerr<<"("<<#a<<" , "<<#b<<" , "<<#c<<" ) = ( "<<(a)<<" , "<<(b)<<" , "<<(c)<<")\n";
#define Error4(a,b,c,d) cerr<<"("<<#a<<" , "<<#b<<" , "<<#c<<" , "<<#d<<" ) = ( "<<(a)<<" , "<<(b)<<" , "<<(c)<<" , "<<(d)<<")\n";
#define Error5(a,b,c,d,e) cerr<<"("<<#a<<" , "<<#b<<" , "<<#c<<" , "<<#d<<" , "<<#e<<" ) = ( "<<(a)<<" , "<<(b)<<" , "<<(c)<<" , "<<(d)<<" , "<<(e)<<")\n";
#define errop(a) cerr<<#a<<" = ( "<<((a).x)<<" , "<<((a).y)<<" )\n";
#define coud(a,b) cout<<fixed << setprecision((b)) << (a)
#define L(x) (((x)<<1)+1)
#define R(x) (((x)<<1)+2)
#define umap unordered_map
//#define double long double
#define mod 1000000007
#define mod1 1000000009
#define LIMIT 1000000000000000000LL
#define MAX1 1000000000
const int inf=0x3f3f3f3f;
const long double pi=acos(-1.0);
#define MAXN 50010
const string debug_line="yolo";
#define debug error(debug_line)
#define read() freopen("mergedoutput.txt","r",stdin)
#define write() freopen("output.txt","w",stdout)
//template <typename T> using os =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef long long ll;
typedef pair<int,int>pii;
typedef vector<int> vi;
typedef complex <long double> complex_t;
const long double PI = acos((long double)-1.0);

const int statesLimit=MAXN;
const int characterLimit=26;

int f[statesLimit];
int g[statesLimit][26];
vi output[statesLimit];
int numStates;

struct ahoCorasick{
    vi f;
    vector<vi> g;
    vi output;
    int wordCount;

public:

    ahoCorasick(){
        wordCount=-1;
    }

    void clearData(){
        f.clear();
        g.clear();
        output.clear();
        wordCount=-1;
    }

    void mergeOutput(int state1,int state2){
        output[state1]+=output[state2];
    }

    void buildMatchingMachine(const vector<string> &words){
        int states=1;
        int totalSize=0;
        For(i,0,words.size()){
            totalSize+=words[i].size();
        }
        wordCount=0;
        f.resize(totalSize+10,-1);
        g.resize(totalSize+10,vi(26,-1));
        output.resize(totalSize+1);

        For(i,0,words.size()){
            const string &word=words[i];
            int currentState=0;
            For(index,0,word.size()){
                int c=word[index]-'a';
                if(g[currentState][c]==-1){
                    g[currentState][c]=states++;
                }
                currentState=g[currentState][c];
            }
            output[currentState]++;
        }

        For(index,0,characterLimit){
            if(g[0][index]==-1){
                g[0][index]=0;
            }
        }

        queue<int> Q1;
        For(index,0,characterLimit){
            if(g[0][index]!=-1 && g[0][index]!=0){
                f[g[0][index]]=0;
                Q1.push(g[0][index]);
            }
        }

        while(!Q1.empty()){
            int state=Q1.front();
            Q1.pop();
            For(index,0,characterLimit){
                if(g[state][index]!=-1){
                    int failure=f[state];
                    while(g[failure][index]==-1){
                        failure=f[failure];
                    }
                    failure=g[failure][index];
                    f[g[state][index]]=failure;
                    mergeOutput(g[state][index],failure);
                    Q1.push(g[state][index]);
                }
            }
        }

        numStates=states;
    };

    int findNextState(int currentState,char nextCharacter){
        int answer=currentState;
        int nextChar=nextCharacter-'a';
        while(g[answer][nextChar]==-1){
            answer=f[answer];
        }
        return g[answer][nextChar];
    };

    ll findOccurance(string sample){
        if(wordCount==-1){
            return 0;
        }
        ll answer1=0;
        int currState=0;
        For(i,0,sample.size()){
            currState=findNextState(currState,sample[i]);
            answer1=answer1+(ll)output[currState];
        }
        return answer1;
    }
};

struct blocks{
    vector<string> block[30];
    vector<ahoCorasick> root;

    blocks(){
        For(i,0,30){
            block[i].clear();
            ahoCorasick ac;
            root.pb(ac);
        }
    }

    void insert(string s){
        vector<string> curr(1,s);
        For(i,0,30){
            if(block[i].size()==curr.size()){
                curr.insert(curr.end(),all(block[i]));
                block[i].clear();
                root[i].clearData();
            }
            else{
                block[i]=curr;
                root[i].clearData();
                root[i].buildMatchingMachine(block[i]);
                break;
            }
        }
    }

    ll calc(string s){
        ll answer1=0;
        For(i,0,30){
            answer1=answer1+root[i].findOccurance(s);
        }
        return answer1;
    }
};

int main(){
    int m;
    scanf("%d",&m);
    blocks b1;
    blocks b2;
    while(m--){
        int type;
        scanf("%d",&type);
        string s;
        cin>>s;
        if(type==1){
            b1.insert(s);
        }
        else if(type==2){
            b2.insert(s);
        }
        else{
            ll answer1=b1.calc(s)-b2.calc(s);
            printf("%lld\n",answer1);
            fflush(stdout);
        }
    }
return 0;}