#include<bits/stdc++.h>
using namespace std;

int n,k,max_w=-1,a[1010];

int main(void){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);

	cin>>n>>k;for(int i=1;i<=n;++i)cin>>a[i],max_w=max(max_w,a[i]);

	if(k<=0){
		cout<<min(max_w,0);
		return 0;
	}

	int ans=0x3f3f3f3f;

	for(int l=1;l<=n;++l){
		priority_queue<int>Ql;
		priority_queue<int,vector<int>,greater<int>>Qr;
		int sum=0;
		for(int r=l;r<=n;++r){
			if(a[r]>=0)Qr.push(a[r]),sum+=a[r];
			else if(Qr.size()){
				if(Qr.top()>=a[r])Ql.push(a[r]);
				else Qr.push(a[r]),sum+=a[r];
			}
			else Ql.push(a[r]);
			while(sum<k&&Qr.size()&&Qr.top()<0)sum-=Qr.top(),Ql.push(Qr.top()),Qr.pop();
			while(Ql.size()&&sum+Ql.top()>=k)sum+=Ql.top(),Qr.push(Ql.top()),Ql.pop();
			if(sum>=k)ans=min(ans,r-l+(int)Ql.size());
		}
	}

	if(ans==0x3f3f3f3f)cout<<-1;
	else cout<<ans;

	return 0;
}