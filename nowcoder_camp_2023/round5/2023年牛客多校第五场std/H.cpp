#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=1e5+5;
const int INFN=205;
int n,m,a[INFN],b[INFN],c[INF],num[INFN],d[INF];
int f[INFN][INF];
int f2[INFN][INFN][INFN];
bool vis[INFN][INFN][INFN];
int DFS(int x,int l,int r) {
	if (l>r) return 0;
	if (vis[x][l][r]) return f2[x][l][r];
	vis[x][l][r]=1;
	if (a[r]<=x) f2[x][l][r]=max(f2[x][l][r],DFS(x-a[r],l,r-1)+b[r]);
	f2[x][l][r]=max(f2[x][l][r],DFS(x,l,r-1));
	return f2[x][l][r];
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=n;i++) cin>>a[i]>>b[i];
	for (int i=1;i<=m;i++) cin>>c[i];
	for (int i=1;i<=m;i++) {
		num[c[i]]++;
		d[++d[0]]=c[i];
	}
	m=d[0];
	
				
	int ans=0;
	for (int i=0;i<=n;i++) {
		for (int j=1;j<=m;j++) {
			for (int k=i;k<=n;k++) {
				f[k][j]=max(f[k][j],DFS(d[j],i+1,k)+f[i][j-1]);
				ans=max(ans,f[k][j]);
			}
		}
	}
	cout<<ans<<"\n";
	return 0;
}