#include<bits/stdc++.h>
using namespace std;

const int maxn=2e5+100;
const int mod=998244353;
const int m=30;

int n,a[maxn],b[maxn];
long long pre[maxn],suf[maxn];

int main(void){
	// freopen("input.txt","r",stdin);
	// freopen("my.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);

	cin>>n;for(int i=1;i<=n;++i)cin>>a[i];

	for(int w=0;w<m;++w){
		for(int i=1;i<=n;++i)b[i]=min(a[i]&(1<<w),1);
		int cnt[2]={1,0},now=0;
		for(int i=1;i<=n;++i){
			now^=b[i],++cnt[now];
			pre[i]+=(1ll<<w)*cnt[now^1];
		}
		cnt[0]=1,cnt[1]=now=0;
		for(int i=n;i>=1;--i){
			now^=b[i],++cnt[now];
			suf[i]+=(1ll<<w)*cnt[now^1];
		}
	}
	for(int i=1;i<=n;++i)pre[i]=(pre[i-1]+pre[i])%mod;
	for(int i=n;i>=1;--i)suf[i]=(suf[i+1]+suf[i])%mod;

	// for(int i=1;i<=n;++i)cout<<pre[i]<<" ";cout<<"\n";
	// for(int i=1;i<=n;++i)cout<<suf[i]<<" ";cout<<"\n";

	long long ans=0;
	for(int w=0;w<m;++w){
		long long cnt[2]={0,0};int now=0;
		for(int r=1;r<=n;++r){
			now^=min(a[r]&(1<<w),1),cnt[now]+=pre[r];
			ans+=cnt[now^1]%mod*(1<<w)%mod*suf[r+1]%mod;
		}
	}
	
	cout<<ans%mod;

	return 0;
}