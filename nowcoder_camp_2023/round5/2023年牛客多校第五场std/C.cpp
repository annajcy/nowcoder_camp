#include<bits/stdc++.h>
using namespace std;


int main(void){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);

	int n,pre=0;cin>>n;
	vector<int>d(n,0);
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			char c;cin>>c;
			if(c=='1')++d[j];
		}
	}

	sort(d.begin(),d.end());

	for(int i=0;i<n-1;++i){
		pre+=d[i];
		if(pre==(i+1)*i/2){
			cout<<n-1;
			return 0;
		}
	}

	cout<<n;

	return 0;
}