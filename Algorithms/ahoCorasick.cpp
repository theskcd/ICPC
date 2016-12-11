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
        while(g[answer][nextChar]==-1){
            answer=f[answer];
        }
        return g[answer][nextChar];
    };
};