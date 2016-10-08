#include <bits/stdc++.h>
using namespace std;
 
int m=65535;
int dp[22][300007];
 
int z[22][300007];
 
vector <string> pus;
string nic;
 
vector <string> dajgraf(int v, int u)
{
    if (!v && !u)
        return pus;
    if (z[v][u]==-1)
    {
        vector <string> ret=dajgraf(v-1, u-1);
        for (int i=0; i<v-1; i++)
            ret[i]+='N';
        ret.push_back(nic);
        for (int i=0; i<v; i++)
            ret.back().push_back('N');
        return ret;
    }
    if (z[v][u]==-2)
    {
        vector <string> ret=dajgraf(v-1, u-(1<<(v-1)));
        for (int i=0; i<v-1; i++)
            ret[i]+='Y';
        ret.push_back(nic);
        for (int i=0; i<v-1; i++)
            ret.back().push_back('Y');
        ret.back().push_back('N');
        return ret;
    }
    int r1=z[v][u]%100;
    int r2=v-r1;
    int l1=z[v][u]/100;
    int l2=u-l1;
    vector <string> ret1=dajgraf(r1, l1);
    vector <string> ret2=dajgraf(r2, l2);
    for (int i=0; i<r1; i++)
    {
        for (int j=0; j<r2; j++)
        {
            ret1[i].push_back('N');
        }
    }
    for (int i=0; i<r2; i++)
    {
        ret1.push_back(nic);
        for (int j=0; j<r1; j++)
        {
            ret1.back().push_back('N');
        }
        for (int j=0; j<r2; j++)
        {
            ret1.back().push_back(ret2[i][j]);
        }
    }
    return ret1;
}
 
struct ConnectedSubgraph
{
    vector <string> construct(int k)
    {
        dp[0][0]=1;
        for (int i=1; i<=20; i++)
        {
            for (int j=0; j<=k; j++)
            {
                if (!dp[i-1][j])
                    continue;
                dp[i][j+1]=1;
                z[i][j+1]=-1;
                dp[i][j+(1<<(i-1))]=1;
                z[i][j+(1<<(i-1))]=-2;
            }
            for (int l=1; l<i; l++)
            {
                vector <int> jed, dwa;
                for (int j=0; j<=k; j++)
                {
                    if (dp[l][j])
                        jed.push_back(j);
                    if (dp[i-l][j])
                        dwa.push_back(j);
                }
                for (int j=0; j<jed.size(); j++)
                {
                    for (int jj=0; jj<dwa.size(); jj++)
                    {
                        dp[i][jed[j]+dwa[jj]]=1;
                        z[i][jed[j]+dwa[jj]]=l+100*jed[j];
                    }
                }
            }
        }
        for (int i=1; i<=20; i++)
        {
            if (dp[i][k])
            {
                return dajgraf(i, k);
            }
        }
        return pus;
    }
};