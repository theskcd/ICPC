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
#define MAXN 100100
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
const int root=0;

vector<string> tokens;
const int statesLimit=MAXN;
const int characterLimit=26;
int BLOCK=350;
int f[statesLimit];
int g[statesLimit][26];
vi output[statesLimit];
vi stringReach[statesLimit];
vi endsHere[statesLimit];
int numStates;
int endAt[MAXN];
vi Adj[MAXN];
int parent1[MAXN];
ll answer1[MAXN];
ll ps[MAXN];
int n;

struct query{
    int l1,r1,k1;
    query(){};
    query(int _l1,int _r1,int _k1){
        l1=_l1;
        r1=_r1;
        k1=_k1;
    }
};

vector<struct query> Q;
vi queries[MAXN];

void add(int index1,int val){
    index1++;
    for(;index1<MAXN;index1=index1+(index1&(-index1))){
        assert(index1>=0);
        ps[index1]+=val;
    }
}

ll ask(int index1){
    ll sum1=0;
    index1++;
    for(;index1>0;index1=index1-(index1&(-index1))){
        assert(index1>=0);
        sum1=sum1+ps[index1];
    }
    return sum1;
}

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
                stringReach[currentState].pb(i);
            }
            output[currentState].pb(i);
            endsHere[currentState].pb(i);
            endAt[i]=currentState;
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

    void createTree(){
        For(i,1,numStates){
            parent1[i]=f[i];
            // assert(f[i]!=-1);
            Adj[f[i]].pb(i);
        }
    }

    int DFS1(int node,int i){
        int answer1=0;
        rep(t1,stringReach[node]){
            if(t1==i){
                answer1++;
            }
        }
        rep(t1,Adj[node]){
            answer1+=DFS1(t1,i);
        }
        rep(t1,endsHere[node]){
            ps[t1]+=(ll)answer1;
        }
        return answer1;
    }

    void solve(int i){
        For(i,1,n){
            ps[i]=(ps[i-1]+ps[i]);
        }
        rep(index1,queries[i]){
            answer1[index1]=ps[Q[index1].r1];
            if(Q[index1].l1!=0){
                answer1[index1]=answer1[index1]-ps[Q[index1].l1-1];
            }
        }
    }

    int DFS(int node){
        rep(node1,endsHere[node]){
            add(node1,1);
        }
        rep(i,stringReach[node]){
            if((int)tokens[i].size()<BLOCK){
                rep(index1,queries[i]){
                    answer1[index1]+=ask(Q[index1].r1);
                    if(Q[index1].l1!=0){
                        answer1[index1]=answer1[index1]-ask(Q[index1].l1-1);
                    }
                }
            }
        }
        rep(t1,Adj[node]){
            DFS(t1);
        }
        rep(node1,endsHere[node]){
            add(node1,-1);
        }
    }
};

int main(){
    int q;
    scanf("%d%d",&n,&q);
    // n=50001;
    // q=1;

    For(i,0,n){
        string s;
        cin>>s;
        // s="a";
        tokens.pb(s);
    }

    ahoCorasick ac;
    ac.buildMatchingMachine(tokens);
    // debug;
    ac.createTree();
    // debug;

    while(q--){
        int l1,r1,k1;
        scanf("%d%d%d",&l1,&r1,&k1);
        l1--,r1--,k1--;
        Q.pb(query(l1,r1,k1));
        queries[k1].pb(Q.size()-1);
    }

    For(i,0,n){
        if(tokens[i].size()>=BLOCK){
            ac.DFS1(root,i);
            ac.solve(i);
            memset(ps,0,sizeof(ps));
        }
    }

    ac.DFS(root);

    For(i,0,Q.size()){
        printf("%lld\n",answer1[i]);
    }
return 0;}