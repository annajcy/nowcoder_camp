#include<bits/stdc++.h>
#define F(i,l,r) for(int i=l;i<r;++i)
#define Fe(i,l,r) for(int i=l;i<=r;++i)
#define Fer(i,l,r) for(int i=l;i>=r;--i)
#if 0
#define pr(...) fprintf(stderr,__VA_ARGS__)
#else
#define pr(...) void(0)
#endif

typedef long long i64;
const int maxn=1e6,maxm=1e6,maxv=1e3,N=maxn+10,M=maxm+10;
const int MEM=1<<26;
uint64_t pool[MEM],*pool_p=pool;

template<class T>
void alloc(T *&p,int sz,bool init=0){
	p=reinterpret_cast<T*>(pool_p);
	pool_p+=(sz*sizeof(T)+7)>>3;
	assert(pool_p<pool+MEM);
	if(init)F(i,0,sz)new(p+i)T();
}

template<class T>
struct Undo{
	T &x;
	T x0;
	Undo(T &x):x(x),x0(x){}
	~Undo(){x=x0;}
};
#define alloc_scope Undo<uint64_t*> _##__LINE__(pool_p)

template<class T>
struct Array{
	T *v;
	int sz;
	Array(){}
	Array(int n){alloc(n);}
	void alloc(int n){
		sz=n;
		::alloc(v,n);
	}
	T &operator[](int x){
		return v[x];
	}
	T *begin(){return v;}
	T *end(){return v+sz;}
};
template<class T>
struct Grid{
	T *v;
	int xsz,ysz;
	Grid(){}
	Grid(int xn,int yn){
		alloc(xn,yn);
	}
	void alloc(int xn,int yn){
		xsz=xn;ysz=yn;
		::alloc(v,xn*yn);
	}
	T &operator()(int x,int y){
		return v[x*ysz+y];
	}
};


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
int n,m,t2n,vn;
int qs[N],ans[N];
Array<int> a,a1;
struct Seg{
	int sz,rev,to;
};
Array<int> cal_xs(Array<Seg> ss){
	Array<int> xs(ss.sz);
	int x=0;
	F(i,0,ss.sz){
		x+=ss[i].sz;
		xs[i]=x;
	}
	return xs;
}
Array<int> cal_sz(Array<int> xs1,Array<int> xs){
	Array<int> sz1(xs1.sz+1);
	int p1=-1;
	F(i,0,xs1.sz){
		int p2=p1+1;
		sz1[i]=p2;
		while(xs[p2]<xs1[i])++p2;
		p1=p2;
	}
	sz1[xs1.sz]=xs.sz;
	return sz1;
}
Array<int> cal_mp(Array<int> sz1,Array<Seg> ss){
	Array<int> sz2(sz1.sz);
	F(i,0,ss.sz)sz2[ss[i].to+1]=sz1[i+1]-sz1[i];
	sz2[0]=0;
	F(i,1,sz2.sz)sz2[i]+=sz2[i-1];
	return sz2;
}
#define BE(x) x.begin(),x.end()
struct Node{
	Node *lc,*rc;
	int L,R;
	Array<Seg> ss;
	Array<int> mp;
	Grid<int> sum;
	void cal(Node *fa=nullptr){
		alloc_scope;
		sum.alloc(ss.sz,ss.sz);
		F(i,0,ss.sz)Fe(j,0,i)sum(i,j)=0;
		if(fa){
			F(i,0,fa->ss.sz)Fe(j,0,i){
				int l=mp[i],r=mp[j];
				if(l<r)std::swap(l,r);
				sum(l,r)+=fa->sum(i,j);
			}
		}else{
			static int bid[N],pre[N],pos[N];
			mp.alloc(ss.sz+1);
			mp[0]=1;
			F(i,0,ss.sz)mp[ss[i].to+1]=ss[i].sz;
			F(i,1,mp.sz)mp[i]+=mp[i-1];
			Fe(i,1,vn)pos[i]=0;
			int x0=1;
			F(i,0,ss.sz){
				Seg &s=ss[i];
				F(j,0,s.sz){
					int k=x0+j;
					bid[k]=i;
					int x=a[k];
					if(x){
						pre[k]=pos[x];
						for(int k0=pre[k];k0;k0=pre[k0]){
							sum(i,bid[k0])+=(x<=t2n?2:1);
						}
						pos[x]=k;
					}
				}
				int x1=mp[s.to];
				if(!s.rev){
					F(j,0,s.sz)a1[x1+j]=a[x0+j];
				}else{
					F(j,0,s.sz)a1[x1+j]=a[x0+s.sz-1-j];
				}
				x0+=s.sz;
			}
			std::swap(a,a1);
		}
		if(L==R){
			if(ss.sz==2)ans[L]=sum(1,0)/2;
			return;
		}
		lc->cal(this);
		rc->cal(this);
	}
	void init(){
		int x=qs[L];
		ss.alloc(2);
		ss[0]={x,1,0};
		if(x<n)ss[1]={n-x,0,1};
		else ss.sz=1;
	}
	void up(){
		Array<Seg> s1=lc->ss,s2=rc->ss;
		Array<Seg> s1_(s1.sz);
		F(i,0,s1.sz)s1_[s1[i].to]={s1[i].sz,s1[i].rev,i};
		auto xs1=cal_xs(s1_),xs2=cal_xs(s2);
		Array<int> xs(s1.sz+s2.sz);
		xs.sz=std::set_union(BE(xs1),BE(xs2),xs.begin())-xs.begin();
		auto sz1=cal_sz(xs1,xs),sz2=cal_sz(xs2,xs);
		auto sz0=cal_mp(sz1,s1_),sz3=cal_mp(sz2,s2);
		Array<Seg> s3(xs.sz);
		int x0=0;
		F(i,0,xs.sz){
			s3[i].sz=xs[i]-x0;
			x0=xs[i];
		}
		Array<int> mp(xs.sz);
		F(i,0,s2.sz){
			Seg &w=s2[i];
			F(j,sz2[i],sz2[i+1]){
				Seg &s=s3[j];
				s.rev=w.rev;
				s.to=sz3[w.to]+(w.rev?sz2[i+1]-1-j:j-sz2[i]);
				mp[j]=i;
			}
		}
		ss.alloc(xs.sz);
		lc->mp.alloc(ss.sz);
		rc->mp.alloc(ss.sz);
		F(i,0,s1.sz){
			Seg &w=s1_[i];
			F(j,sz1[i],sz1[i+1]){
				Seg &s=s3[j];
				int k=sz0[w.to]+(w.rev?sz1[i+1]-1-j:j-sz1[i]);
				ss[k]={s.sz,s.rev^w.rev,s.to};
				lc->mp[k]=w.to;
				rc->mp[k]=mp[j];
			}
		}
	}
}ns[N],*np=ns,*rt;
Node *dc(int L,int R){
	Node *w=np++;
	w->L=L;
	w->R=R;
	if(L<R){
		int M=(L+R)>>1;
		w->lc=dc(L,M);
		w->rc=dc(M+1,R);
		w->up();
	}else w->init();
	return w;
}
int main(){
	n=read(1,maxn);
	m=read(1,maxm);
	a.alloc(n+1);
	a1.alloc(n+1);
	Fe(i,1,n)a[i]=read(1,n);
	static int t[N],t2[N],t3[N];
	Fe(i,1,n)++t[a[i]];
	Fe(i,1,n){
		t2[i]=t2[i-1]+(t[i]==2);
		t3[i]=t3[i-1]+(t[i]==3);
	}
	t2n=t2[n];
	vn=t2n+t3[n];
	Fe(i,1,n){
		int x=a[i];
		if(t[x]==1)a[i]=0;
		else if(t[x]==2)a[i]=t2[x];
		else a[i]=t2n+t3[x];
	}
	Fe(i,1,m)qs[i]=read(1,n);
	int B=sqrt(n)*1.2+1;
	for(int l=1;l<=m;l+=B){
		int r=std::min(m,l+B-1);
		alloc_scope;
		np=ns;
		rt=dc(l,r);
		rt->cal();
	}
	Fe(i,1,m)write(ans[i],'\n');
	return 0;
}
