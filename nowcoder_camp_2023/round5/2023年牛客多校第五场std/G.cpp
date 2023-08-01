#include<bits/stdc++.h>
using namespace std;

vector<int>a(100010,0);

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);

	int n,k;cin>>n>>k;
	
	for(int i=1;i<=n;++i)cin>>a[i];
	int ans=n,cnt[5]={0,0,0,0,0};
	for(int l=1,r=0;l<=n;--cnt[a[l++]]){
		while(r<=n&&(cnt[1]<1||cnt[2]<1||cnt[3]<1||cnt[4]<k)){
			++cnt[a[++r]];
		}
		if(r>n)break;
		ans=min(ans,r-l+1);
	}
	cout<<ans;

	return 0;
}