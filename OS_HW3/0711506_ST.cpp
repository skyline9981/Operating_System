#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false),cin.tie(0)
#define ll long long

using namespace std;

vector<int>vec;
vector<int>ans;

int main (int argc, const char * argv[]) {
	
	int tmp,a=0;
	while(cin>>tmp){
		vec.push_back(tmp);
		a++;
	}

	for(int i=0;i<(a/2);i++){
		for(int j=i+1;j<(a/2);j++){
			if (vec[i] > vec[j]){
                int temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
            } 
		}
	}

	for(int i=(a/2);i<a;i++){
		for(int j=i+1;j<a;j++){
			if (vec[i] > vec[j]){
                int temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
            } 
		}
	}

	int i=0,j=(a/2);

	while(i<(a/2) && j<a){
		if(vec[i] < vec[j]){
			ans.push_back(vec[i++]);
		}else{
			ans.push_back(vec[j++]);
		}
	}

	while (i < (a/2)){
        ans.push_back(vec[i++]);
    }

    while (j < a){
        ans.push_back(vec[j++]);
    }

	for (int i = 0; i < a; i ++) {
        cout << ans[i] << ' ';
    }

    return 0;
}
