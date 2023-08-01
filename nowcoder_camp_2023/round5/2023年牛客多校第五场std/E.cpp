#include<bits/stdc++.h>
using namespace std;

const int maxn=4e3+100;
int ans[maxn],lb[maxn],rb[maxn],w[maxn],vis[maxn];

int main(void){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);

	int n,m;cin>>n>>m;
	vector<pair<int,int>>vec;
	for(int i=1;i<=m;++i){
		cin>>lb[i]>>rb[i]>>w[i];
		vec.push_back(make_pair(rb[i]-lb[i],i));
		if(lb[i]==rb[i]&&w[i]==1){
			cout<<"-1\n";return 0;
		}
	}
	for(int i=1;i<=n;++i)++m,lb[m]=rb[m]=i,w[m]=0;
	sort(vec.begin(),vec.end());

	for(int i=1;i<=n;++i)ans[i]=i;

	for(auto &[len,id]:vec){
		int l=lb[id],r=rb[id],w0=0;
		vector<int>sn;
		for(int i=1;i<=m;++i){
			if(!vis[i]&&i!=id&&l<=lb[i]&&rb[i]<=r){
				sn.push_back(i);
				vis[i]=1,w0^=w[i];
			}
		}
		if(w0!=w[id]){
			for(auto x:sn){
				if(rb[x]!=r){
					int id1=0,id2=0;
					for(int i=l;i<=r;++i){
						if(ans[i]==rb[x])id1=i;
						else if(ans[i]==rb[x]+1)id2=i;
					}
					swap(ans[id1],ans[id2]);
					break;
				}
			}
		}
	}
	
	for(int i=1;i<=n;++i)cout<<ans[i]<<" ";

	return 0;
}