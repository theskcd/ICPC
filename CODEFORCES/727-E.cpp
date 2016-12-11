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
#define MAXN 2000010
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

public:

    void mergeOutput(int state1,int state2){
        output[state1].insert(output[state1].end(),all(output[state2]));
    }

    void buildMatchingMachine(const vector<string> &words){
        int states=1;
        memset(f,-1,sizeof(f));
        memset(g,-1,sizeof(g));
        memset(output,0,sizeof(output));

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
            output[currentState].pb(i);
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
        // Error(currentState,answer);
        // Error(answer,nextChar);
        // error(g[answer][nextChar]);
        // Error(answer,g[answer][nextChar]);
        while(g[answer][nextChar]==-1){
            answer=f[answer];
        }
        // Error(currentState,g[answer][nextChar]);
        return g[answer][nextChar];
    };
};

string s;
char str[MAXN];
char str1[MAXN];
vector<string> collect;
int states[MAXN];

int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    scanf("%s",str);
    s.assign(str);

    int g;
    scanf("%d",&g);
    For(i,0,g){
        scanf("%s",str1);
        string temp(str1);
        collect.pb(temp);
    }

    For(i,0,MAXN){
        states[i]=-1;
    }
    ahoCorasick ac;
    ac.buildMatchingMachine(collect);
    int currState=0;
    int modulo=(int)s.size();
    For(i,0,s.size()+k){
        // Error(currState,s[i%modulo]);
        int currState1=ac.findNextState(currState,s[i%modulo]);
        currState=currState1;
        if(output[currState].size()!=0){
            states[i%modulo]=output[currState][0];
            assert(output[currState].size()==1);
        }
        // Error(i,currState);
    }
    For(i,0,k){
        set<int> s1;
        For(j,0,n){
            if(states[i+j*k]!=-1){
                s1.insert(states[i+j*k]);
            }
        }
        if(s1.size()==n){
            printf("YES\n");
            For(j,0,n){
                printf("%d ",states[i+j*k]+1);
            }
            printf("\n");
            return 0;
        }
    }
    printf("NO\n");
return 0;}