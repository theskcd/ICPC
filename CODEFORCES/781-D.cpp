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
#define MAX 810
// #define N 100010
const string debug_line="yolo";
#define debug error(debug_line)
#define read() freopen("mergedoutput.txt","r",stdin)
#define write() freopen("output.txt","w",stdout)
//template <typename T> using os =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef long long ll;
typedef pair<int,int>pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef unsigned long long ull;
typedef complex <long double> complex_t;
const long double PI = acos((long double)-1.0);
const long double eps=1e-6;
ull getRand(){return ((ull)rand()<<40)+((ull)rand()<<20)+((ull)rand());}

bool init0[62][510][510];
bool init1[62][510][510];
bool currAnswer[510][510];

void calcMat(int index,int mode,int prevIndex,const int n){
    if(mode==0){
        bitset<500> mat1[500];
        bitset<500> mat2[500];
        For(i,0,n){
            For(j,0,n){
                if(init0[prevIndex][i][j]) {
                    // Error3(prevIndex,i,j);
                    mat1[i].set(j);
                }
            }
        }
        For(j,0,n){
            For(i,0,n){
                if(init1[prevIndex][i][j]) mat2[j].set(i);
            }
        }
        For(i,0,n){
            For(j,0,n){
                bitset<500> res=mat1[i] & mat2[j];
                if(res.count()>=1){
                    init0[index][i][j]=1;
                    // Error4(index,i,j,mode);
                }
            }
        }
    }
    else{
        bitset<500> mat1[500];
        bitset<500> mat2[500];
        For(i,0,n){
            For(j,0,n){
                if(init1[prevIndex][i][j]) mat1[i].set(j);
            }
        }
        For(j,0,n){
            For(i,0,n){
                if(init0[prevIndex][i][j]) mat2[j].set(i);
            }
        }
        For(i,0,n){
            For(j,0,n){
                bitset<500> res=mat1[i]&mat2[j];
                if(res.count()!=0){
                    init1[index][i][j]=1;
                    // Error4(index,i,j,mode);
                }
            }
        }
    }
}

bool poss(int index1,int n){
    bool poss=false;
    // error(index1);
    // For(i,0,n){
    //     For(j,0,n){
    //         printf("%d",init0[index1][i][j]);
    //     }
    //     printf("\n");
    // }
    For(i,0,n){
        For(j,0,n){
            poss=poss | init0[index1][i][j];
        }
    }
    return poss;
}

void copyAnswer(int index1,const int n){
    For(i,0,n){
        For(j,0,n){
            currAnswer[i][j]=init0[index1][i][j];
        }
    }
}

bool checkPoss(int index1,const int mode,int n){
    bool poss=false;
    // Error3(index1,mode,n);
    if(mode==0){
        bitset<500> mat1[500];bitset<500> mat2[500];
        For(i,0,n){
            For(j,0,n){
                if(currAnswer[i][j]==1){
                    mat1[i].set(j);
                }
            }
        }
        For(j,0,n){
            For(i,0,n){
                if(init0[index1][i][j]){
                    mat2[j].set(i);
                }
            }
        }
        For(i,0,n){
            For(j,0,n){
                bitset<500> res=mat1[i] & mat2[j];
                if(res.count()>=1){poss=true;}
            }
        }
    }
    else{
        bitset<500> mat1[500];bitset<500> mat2[n];
        For(i,0,500){
            For(j,0,n){
                if(currAnswer[i][j]==1){
                    mat1[i].set(j);
                }
            }
        }
        For(j,0,n){
            For(i,0,n){
                if(init1[index1][i][j]==1){
                    mat2[j].set(i);
                }
            }
        }
        For(i,0,n){
            For(j,0,n){
                bitset<500> res=mat1[i] & mat2[j];
                if(res.count()>=1){
                    poss=true;
                }
            }
        }
    }
    return poss;
}

void commitAnswer(int index1,int mode,const int n){
    if(mode==0){
        bitset<500> mat1[500];
        bitset<500> mat2[500];
        For(i,0,n){
            For(j,0,n){
                if(currAnswer[i][j]==1){
                    mat1[i].set(j);
                }
            }
        }
        For(j,0,n){
            For(i,0,n){
                if(init0[index1][i][j]==1){
                    mat2[j].set(i);
                }
            }
        }
        For(i,0,n){
            For(j,0,n){
                bitset<500> res=mat1[i] & mat2[j];
                if(res.count()>=1){
                    currAnswer[i][j]=1;
                }
                else{
                    currAnswer[i][j]=0;
                }
            }
        }
    }
    else{
        bitset<500> mat1[500];
        bitset<500> mat2[500];
        For(i,0,n){
            For(j,0,n){
                if(currAnswer[i][j]==1){
                    mat1[i].set(j);
                }
            }
        }
        For(j,0,n){
            For(i,0,n){
                if(init1[index1][i][j]==1){
                    mat2[j].set(i);
                }
            }
        }
        For(i,0,n){
            For(j,0,n){
                bitset<500> res=mat1[i] & mat2[j];
                if(res.count()>=1){
                    currAnswer[i][j]=1;
                }
                else{
                    currAnswer[i][j]=0;
                }
            }
        }
    }
}

ll calc(const int n){
    For(i,1,62){
        // error(i);
        calcMat(i,0,i-1,n);
        calcMat(i,1,i-1,n);
    }
    int start1=-1;
    For(i,0,62){
        if(poss(i,n)){
            start1=i;
            copyAnswer(i,n);
        }
    }
    ll answer1=(1LL<<start1);
    int mode=true;
    start1--;
    // Error(start1,answer1);
    while(start1>=0){
        // Error(start1,mode);
        // For(i,0,n){
        //     For(j,0,n){
        //         printf("%d",currAnswer[i][j]);
        //     }
        //     printf("\n");
        // }
        if(checkPoss(start1,mode,n)){
            // error("multiply with");
            // For(i,0,n){
            //     For(j,0,n){
            //         if(mode){
            //             printf("%d",init1[start1][i][j]);
            //         }
            //         else{
            //             printf("%d",init0[start1][i][j]);
            //         }
            //     }
            //     printf("\n");
            // }
            // Error3("success for",start1,mode);
            // For(i,0,n){
            //     For(j,0,n){
            //         printf("%d",currAnswer[i][j]);
            //     }
            //     printf("\n");
            // }
            answer1=answer1+(1LL<<start1);
            commitAnswer(start1,mode,n);
            start1--;
            mode=1-mode;
        }
        else{
            start1--;
        }
    }
    return answer1;
}

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    For(i,0,m){
        int a1,b1,t1;
        scanf("%d%d%d",&a1,&b1,&t1);a1--,b1--;
        // Error3(a1,b1,t1);
        if(t1==0){
            init0[0][a1][b1]=1;
        }
        else{
            init1[0][a1][b1]=1;
        }
    }
    if(m==0){
        puts("0");return 0;
    }
    // For(i,0,n){
    //     For(j,0,n){
    //         printf("%d",init0[0][i][j]);
    //     }
    //     printf("\n");
    // }
    // For(i,0,n){
    //     For(j,0,n){
    //         printf("%d",init1[0][i][j]);
    //     }
    //     printf("\n");
    // }
    ll answer1=calc(n);
    if(answer1>=1000000000000000000LL){answer1=-1;}
    printf("%lld\n",answer1);
return 0;}

// 3 6
// 3 1 1
// 1 2 1
// 2 1 1
// 1 3 0
// 3 2 1
// 2 2 0