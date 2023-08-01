#include<bits/stdc++.h>
using namespace std;


inline void solve(){
	int k,c,n;cin>>k>>c>>n;
	int ans=0;
	for(int i=1;i*i<=c;++i){
		if(c%i==0){
			int b=i;
			int a=(c-b)/k;
			if((c-b)%k==0&&a>0&&__gcd(a,b)>=n)++ans;
			if(i*i!=c){
				b=c/i;
				a=(c-b)/k;
				if((c-b)%k==0&&a>0&&__gcd(a,b)>=n)++ans;
			}
		}
	}
	cout<<ans<<"\n";
}

int main(void){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);

	int t;cin>>t;
	while(t--)solve();

	return 0;
}