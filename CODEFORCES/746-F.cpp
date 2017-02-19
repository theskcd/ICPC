#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

//using namespace __gnu_pbds;
using namespace std;

// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜

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
#define LIMIT 10000000000000000LL
#define INF 10000000000LL
#define MAX1 1000000000
const int inf=0x3f3f3f3f;
const long double pi=acos(-1.0);
#define MAX 50010
// #define N 100010
const string debug_line="yolo";
#define debug error(debug_line)
#define read() freopen("mergedoutput.txt","r",stdin)
#define write() freopen("output.txt","w",stdout)
//template <typename T> using os =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef long long ll;
typedef pair<int,int>pii;
typedef vector<int> vi;
typedef unsigned long long ull;
typedef complex <long double> complex_t;
const long double PI = acos((long double)-1.0);
const long double eps=1e-6;
ull getRand(){return ((ull)rand()<<40)+((ull)rand()<<20)+((ull)rand());}

int a1[200010];
int t1[200010];
int currAnswer=0;
int answer1=0;
int n,w,k;
// auto comp=[](pii a,pii b){
//     if(a.y==b.y){
//         return true;
//     }
//     return a.x>b.x;
// };
// typedef set<pii,decltype(comp)> set1;
// set1 s2(comp);
// set1 s1(comp);
set<pii> s1,s2;
int l1=1;
int r1=1;
bool marked[200010];

void rearrange(){
    if(s1.size()<w){
        if(!s2.empty()){
            pii t2=*(s2.rbegin());
            s2.erase(t2);
            k+=t1[t2.y];
            k-=(t1[t2.y]+1)/2;
            s1.insert(t2);
        }      
    }
}

bool checkInsert(int index,bool same=0){
    // Error("checkIsnert",index);
    if(same || s1.size()<w){
        if(k-(t1[index]+1)/2>=0){
            k-=(t1[index]+1)/2;
            s1.insert(mp(t1[index],index));
            marked[index]=true;
            answer1+=a1[index];
            return true;
        }
        return false;
    }
    pii t2=*(s1.begin());
    if(t2.x>t1[index]){
        if(k-t1[index]>=0){
            s2.insert(mp(t1[index],index));
            marked[index]=true;
            answer1+=a1[index];k-=t1[index];
            return true;
        }
        else{
            return false;
        }
    }
    else{
        int newW=k;
        newW=newW+(t2.x+1)/2-t2.x-(t1[index]+1)/2;
        if(newW<0){
            return false;
        }
        else{
            s1.erase(t2);
            s2.insert(t2);
            s1.insert(mp(t1[index],index));
            marked[index]=true;
            k=newW;answer1+=a1[index];
            return true;
        }
    }
}


bool checkValid(int index){
    // error(index);
    // rep(t1,s1){
    //     printf("(%d,%d) ",t1.x,t1.y);
    // }
    // rep(t1,s2){
    //     printf("(%d,%d) ",t1.x,t1.y);
    // }
    bool poss1=(s2.find(mp(t1[index],index))!=s2.end());
    bool poss2=(s1.find(mp(t1[index],index))!=s1.end());
    return (poss1 | poss2);
}

void removeElement(int index){
    marked[index]=false;
    // Error3("remove",t1[index],index);
    if(s1.find(mp(t1[index],index))!=s1.end()){
        s1.erase(mp(t1[index],index));
        k+=(t1[index]+1)/2;answer1-=a1[index];
        rearrange();
    }
    else{
        // error((s1.find(mp(t1[index],index))==s1.end()));
        // error((s2.find(mp(t1[index],index))==s2.end()));
        assert(s2.find(mp(t1[index],index))!=s2.end());
        s2.erase(mp(t1[index],index));
        k+=t1[index];answer1-=a1[index];
        rearrange();
    }
    // For(i,l1,r1+1){
    //     checkValid(i);
    // }
}

int main(){
    scanf("%d%d%d",&n,&w,&k);
    For(i,1,n+1){
        int temp;
        scanf("%d",&temp);
        a1[i]=temp;
    }

    For(i,1,n+1){
        int temp;scanf("%d",&temp);t1[i]=temp;
    }

    while(l1<=r1 && r1<=n){
        // Error4(l1,r1,s1.size(),s2.size());
        // assert(l1<=r1);
        if(l1==r1){
            if(!checkInsert(r1)){
                l1++;
            }
            else{
                assert(checkValid(r1));
            }
            // Error("Iinsert",r1);
            currAnswer=max(currAnswer,answer1);
            r1++;
        }
        else{
            if(!checkInsert(r1)){
                removeElement(l1);
                l1++;
            }
            else{
                // Error("insert",r1);
                // Error(l1,r1);
                r1++;
            }
            currAnswer=max(currAnswer,answer1);
        }
        // Error(answer1,k);
    }
    printf("%d\n",currAnswer);
return 0;}