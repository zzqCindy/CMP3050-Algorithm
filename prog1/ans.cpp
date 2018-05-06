#include <iostream>
#include <vector>
using namespace std;

// num is the number that required to select

void permutation(vector<int> &A, vector<int> B, int start, int num,vector<vector<int>> &ret){
	
	if(num == 0)
		ret.push_back(B);
		
	for(int i = 0; i <= A.size()-num; i++){
		num.push_back(A[i]);
		permutation(A,B,i+1,num-1,ret);
	}
}

vector<vector<int>> permu(vector<int> A, int num){
	vector<vector<int>> ret;
	if(A.size() <= 0 || num <= 0)
		return ret;
	
	vector<int> tmp;
	permutation(A,tmp,0,num,ret);
	return ret;
}


int main(){
	
	//testing
	vector<int> A;
	for(int i = 0; i < 10; i++)
		A.push_back(i);
	
	vector<vector<int>> ans = permu(A,2);
	for(int i = 0; i < ans.size(); i++){
		for(int j = 0; j < ans[i].size(); j++){
			cout << ans[i][j] << " ";
		}
		cout << "\n";
	}
	
	return 0;
}
