#include<bits/stdc++.h>
#define F(i,l,r) for(int i=l;i<r;++i)
#define Fe(i,l,r) for(int i=l;i<=r;++i)
#define Fer(i,l,r) for(int i=l;i>=r;--i)
#if 1
#define pr(...) fprintf(stderr,__VA_ARGS__)
#else
#define pr(...) void(0)
#endif

typedef long long i64;
const int maxn=1e6,maxm=1e6,N=maxn*1.05+10;

namespace IO{
const int BUF_SZ=1<<16;
char ib[BUF_SZ+1],*ip=ib+BUF_SZ;
void ipre(int n){
	int c=ib+BUF_SZ-ip;
	if(c<n){
		memcpy(ib,ip,c);
		ip=ib;
		fread(ib+c,1,BUF_SZ-c,stdin)[ib+c]=0;
	}
}
template<class T>
T read(T L,T R){
	ipre(100);
	T x=0,f=1;
	while(*ip<'0'||*ip>'9')if(*ip++=='-')f=-f;
	while(*ip>='0'&&*ip<='9')x=x*10+*ip++-'0';
	x*=f;
	if(!(L<=x&&x<=R)){
		std::cerr<<x<<" not in ["<<L<<","<<R<<"]\n";
		exit(1);
	}
	return x;
}
char ob[BUF_SZ+1],*op=ob;
void opre(int n){
	int c=ob+BUF_SZ-op;
	if(c<n){
		fwrite(ob,1,BUF_SZ-c,stdout);
		op=ob;
	}
}
template<class T>
void write(T x){
	opre(100);
	char ss[100],*sp=ss;
	if(x<T(0))x=-x,*op++='-';
	do *sp++=x%10+'0';while(x/=10);
	while(sp!=ss)*op++=*--sp;
}
template<class T>
void write(T x,char c){
	write(x);
	*op++=c;
}
struct __{
	__(){}
	~__(){
		fwrite(ob,1,op-ob,stdout);
	}
}_;
};
using IO::read;
using IO::write;
int a[N];

struct Q{
	int l,r,id;
	bool operator<(const Q &w)const{return r<w.r;}
}qs[N];
i64 ans[N];
struct Pos{int x,y;};
std::vector<Pos> ps[N];
int cnt[N];
template<class T,int n>
struct Vec{
	T v[n];
	Vec operator+(const Vec &w)const{
		Vec c;
		F(i,0,n)c.v[i]=v[i]+w.v[i];
		return c;
	}
	void operator+=(const Vec &w){
		F(i,0,n)v[i]+=w.v[i];
	}
	Vec operator-(const Vec &w)const{
		Vec c;
		F(i,0,n)c.v[i]=v[i]-w.v[i];
		return c;
	}
	T operator*(const Vec &w)const{
		T s=0;
		F(i,0,n)s+=v[i]*w.v[i];
		return s;
	}
};
Vec<i64,3> s2[N];
int pos[N];
template<class T>
struct AddSumO1Sqrt{
	void alloc(int n0){
		n=n0;
		for(D=1;n>>(D*2);++D);
	}
	T s1[N],s2[N];
	int n,D;
	void add(int x,T a){
		s1[x]+=a;
		s2[x>>D]+=a;
	}
	T sum(int x){
		T s=0;
		int l=(x>>D)+1,r=(n>>D);
		Fe(i,l,r)s+=s2[i];
		F(i,x,(l<<D))s+=s1[i];
		return s;
	}
};
template<class T>
struct AddSumSqrtO1{
	void alloc(int n0){
		n=n0;
		for(D=1;n>>(D*2);++D);
	}
	T s1[N],s2[N];
	int n,D;
	void add(int x,T a){
		int l=(x>>D)+1,r=(n>>D);
		Fe(i,l,r)s2[i]+=a;
		F(i,x,(l<<D))s1[i]+=a;
	}
	T sum(int x){
		return s1[x]+s2[x>>D];
	}
};
AddSumSqrtO1<int> s1;
AddSumO1Sqrt<i64> s3;
i64 cost1=0,cost2=0;
int main(){
	int n=read(1,maxn);	
	int m=read(1,maxm);
	Fe(i,1,n)a[i]=read(1,n);
	bool REV=0;
	if(REV)std::reverse(a+1,a+n+1);
	Fe(i,1,n)ps[a[i]].push_back({i,0});
	Fe(i,1,m){
		int l=read(1,n),r=read(l,n);
		if(REV)l=n+1-l,r=n+1-r,std::swap(l,r);
		qs[i]=Q{l,r,i};
	}
	int B=sqrt(n)*2;
	s1.alloc(n);
	Fe(i,1,n){
		Pos *p=ps[i].data();
		int pn=(int)ps[i].size();
		if(pn>=2+B){
			cost1+=n+m;
			std::fill(cnt,cnt+p[0].x,0);
			F(j,1,pn){
				int l=p[j-1].x,r=p[j].x;
				std::fill(cnt+l,cnt+r,j);
				s2[j].v[0]=s1.sum(r)-s1.sum(l);
				Fe(t,1,2)s2[j].v[t]=s2[j].v[t-1]*j;
				s2[j]+=s2[j-1];
			}
			std::fill(cnt+p[pn-1].x,cnt+n+1,pn);
			Fe(j,1,m){
				Q &q=qs[j];
				int L=cnt[q.l-1],R=cnt[q.r];
				if(R-1>L)ans[j]+=(s2[R-1]-s2[L])*Vec<i64,3>{-i64(R)*L,R+L,-1};
			}
		}else{
			F(j,1,pn){
				int l=p[j-1].x,r=p[j].x;
				p[j].y=s1.sum(r)-s1.sum(l);
				pos[r]=j;
			}
		}
		F(j,0,pn)s1.add(p[j].x,1);
	}
	std::sort(qs+1,qs+m+1);
	int qp=1;
	s3.alloc(n);
	Fe(i,1,n){
		if(pos[i]){
			cost2+=pos[i];
			Pos *p=ps[a[i]].data();
			i64 s=0;
			Fer(j,pos[i],1){
				s+=p[j].y;
				s3.add(p[j-1].x,s);
			}
		}	
		for(;qp<=m&&qs[qp].r==i;++qp)ans[qs[qp].id]+=s3.sum(qs[qp].l);
	}
	Fe(i,1,m)write(ans[i],'\n');
	fprintf(stderr,"cost1=%lld\n",cost1);
	fprintf(stderr,"cost2=%lld\n",cost2);
	return 0;
}
