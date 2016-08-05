struct trie{
	int startNode;
	vector<vector<int> > Trie;
	vector<int> sizeTree;
	int countNodes;

	trie(){
		startNode=0;
		Trie.resize(N,vector<int>(26));
		sizeTree.resize(N);
		countNodes=1;
		For(i,0,Trie[startNode].size()){
			Trie[startNode][i]=-1;
		}
	};

public:

	void reset(int node){
		For(i,0,Trie[node].size()){
			Trie[node][i]=-1;
		}
	};

	void insert(string &word){
		int size1=word.size();
		int currNode=0;
		For(i,0,size1){
			if(Trie[currNode][word[i]-'a']==-1){
				Trie[currNode][word[i]-'a']=countNodes++;
				reset(Trie[currNode][word[i]-'a']);
			}
			currNode=Trie[currNode][word[i]-'a'];
			sizeTree[currNode]++;
		}
	};

	string query(string &word){
		string answer1;
		int currNode=0;
		int size1=word.size();
		For(i,0,size1){
			// Error(currNode,sizeTree[Trie[currNode][word[i]-'a']]);
			if(sizeTree[Trie[currNode][word[i]-'a']]==1){
				answer1=answer1+(char)(word[i]);
				return answer1;
			}
			else{
				answer1=answer1+(char)word[i];
				currNode=Trie[currNode][word[i]-'a'];
			}
		}
	}
};

//https://www.interviewbit.com/problems/shortest-unique-prefix/