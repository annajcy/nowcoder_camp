#include<bits/stdc++.h>
#define F(i,l,r) for(int i=l;i<r;++i)
#define Fe(i,l,r) for(int i=l;i<=r;++i)
#define Fer(i,l,r) for(int i=l;i>=r;--i)
#if 0
#define pr(...) fprintf(stderr,__VA_ARGS__)
#else
#define pr(...) void(0)
#endif
int la=0;
typedef long long i64;
typedef uint32_t u32;
const int maxn=1e6,maxm=1e6,maxv=1e3,N=maxn+10,M=maxm+10;
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
	x^=la;
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
int pos[N];

int _rev=0;
struct Data{
	int sz,cnt;
	Data split(int k){
		Data ret;
		ret.sz=sz-k;
		sz=k;
		if(_rev)ret.cnt=cnt,cnt=0;
		else ret.cnt=0;
		return ret;
	}
};
Data operator+(Data a,Data b){
	return {a.sz+b.sz,a.cnt+b.cnt};
}
Data operator|(Data a,Data b){
	return {a.sz+b.sz,a.cnt|b.cnt};
}

template<class T,int N>
struct Alloc{
	T ns[N],*fs[N];
	int np=0,fp=0;
	T *alloc(){
		if(fp)return fs[--fp];
		return ns+(np++);
	}
	void free(T *x){
		fs[fp++]=x;
	}
	T *begin(){return ns;}
	T *end(){return ns+np;}
};

template<class D=Data>
struct Node{
	Node *c[2];
	u32 h,x,x2;
	D d;
	void up(){
		x=c[0]->x;
		x2=c[1]->x2;
		d=c[0]->d+c[1]->d;
	}
	static void _del(Node *);
	static Node *_new();
	static Node *_new(u32 x,const D &d0){
		Node *w=_new();
		w->h=0;
		w->x=x;
		w->x2=x;
		w->d=d0;
		return w;
	}
	static Node *cons(Node *a,Node *b,u32 h){
		Node *c=_new();
		c->c[0]=a;
		c->c[1]=b;
		c->h=h;
		c->up();
		return c;
	}
	friend void split(Node *w,int sz,Node *&l,Node *&r){
		if(w->c[0]){
			int lsz=w->c[0]->d.sz;
			if(sz<lsz){
				split(w->c[0],sz,l,w->c[0]);
				w->up();
				r=w;
			}else if(sz>lsz){
				split(w->c[1],sz-lsz,w->c[1],r);
				w->up();
				l=w;
			}else{
				l=w->c[0];
				r=w->c[1];
				_del(w);
			}
		}else{
			l=w;
			r=_new(w->x,w->d.split(sz));
		}
	}
	friend Node *merge(Node *a,Node *b){
		if(!a)return b;
		if(!b)return a;
		return _merge(a,b);
	}
	static Node *_merge(Node *a,Node *b){
		u32 dx=a->x^b->x;
		u32 h=!dx?0:32-__builtin_clz(dx);
		h=std::max(h,std::max(a->h,b->h));
		if(h>a->h){
			if(h>b->h){
				if((a->x>>(h-1))&1)std::swap(a,b);
				return cons(a,b,h);
			}
			int wc=((a->x>>(h-1))&1);
			b->c[wc]=_merge(a,b->c[wc]);
			b->up();
			return b;
		}
		if(h>b->h){
			int wc=((b->x>>(h-1))&1);
			a->c[wc]=_merge(a->c[wc],b);
			a->up();
			return a;
		}
		if(h){
			a->c[0]=_merge(a->c[0],b->c[0]);
			a->c[1]=_merge(a->c[1],b->c[1]);
			a->up();
			_del(b);
			return a;
		}
		a->d=a->d|b->d;
		_del(b);
		return a;
	}
};
Alloc<Node<Data>,N*2> ns;
template<>
void Node<Data>::_del(Node<Data> *w){
	ns.free(w);
}
template<>
Node<Data> *Node<Data>::_new(){
	auto *w=ns.alloc();
	w->c[0]=0;
	return w;
}

template<class T>
struct BIT{
	int n;
	T a[N];
	void alloc(int n0){
		n=n0;
		Fe(i,0,n)a[i]=0;
	}
	void add(int x,T y){
		int _n=n;
		for(;x<=_n;x+=x&-x)a[x]+=y;
	}
	struct Add{
		BIT &bit;
		int x;
		void operator=(T y){bit.a[x]=y;}
		void operator+=(T y){bit.add(x,y);}
		void operator-=(T y){bit.add(x,-y);}
	};
	Add operator[](int x){
		return Add{*this,x};
	}
	T sum(int x){
		T s=0;
		for(;x;x-=x&-x)s+=a[x];
		return s;
	}
	void build(){
		Fe(i,1,n){
			int j=i+(i&-i);
			if(j<=n)a[j]+=a[i];
		}
	}
};

BIT<int> s;


struct Seg{
	mutable int l,r;
	mutable bool rev;
	mutable Node<Data> *rt;
	bool operator<(const Seg &w)const{return r<w.r;}
};
std::multiset<Seg> ss;
void split_(bool rev,Node<Data> *w,int sz,Node<Data> *&l,Node<Data> *&r){
	_rev=rev;
	if(!rev)split(w,sz,l,r);
	else split(w,w->d.sz-sz,r,l);
}
void ins(int l,int r,bool rev){
	auto it=ss.lower_bound(Seg{0,l,0,nullptr});
	Node<Data> *rt=nullptr,*tmp;
	for(;;){
		if(r<it->l)break;
		if(r<it->r){
			if(it->l<l){
				split_(it->rev,it->rt,l-it->l,tmp,it->rt);
				s[it->r]-=tmp->d.cnt;
				s[l-1]+=tmp->d.cnt;
				ss.insert(Seg{it->l,l-1,it->rev,tmp});
				it->l=l;
			}
			split_(it->rev,it->rt,r+1-it->l,tmp,it->rt);
			s[it->r]-=tmp->d.cnt;
			rt=merge(rt,tmp);
			it->l=r+1;
			break;
		}
		s[it->r]-=it->rt->d.cnt;
		if(it->l<l){
			split_(it->rev,it->rt,l-it->l,it->rt,tmp);
			rt=merge(rt,tmp);
			it->r=l-1;
			s[it->r]+=it->rt->d.cnt;
			++it;
		}else{
			rt=merge(rt,it->rt);
			auto it2=it;
			++it2;
			ss.erase(it);
			it=it2;
		}
	}
	s[r]+=rt->d.cnt;
	ss.emplace_hint(it,Seg{l,r,rev,rt});
}
int main(){
	int n=read(1,maxn);
	int m=read(1,maxm);
	s.alloc(n);
	Fe(i,1,n){
		int x=read(1,n);
		int y=!pos[x];
		pos[x]=i;
		s[i]=y;
		ss.emplace_hint(ss.end(),Seg{i,i,0,Node<Data>::_new(x,{1,y})});
	}
	s.build();
	ss.insert(Seg{n+1,n+1,0,nullptr});
	Fe(i,1,m){
		int l=read(1,n),r=read(1,n);
		bool rev=(l>r);
		if(rev)std::swap(l,r);
		ins(l,r,rev);
		int x=read(1,n);
		
		
		int ans=0;
		
		auto it=ss.lower_bound(Seg{0,x,0,nullptr});
		int x0=it->r;
		if(x<it->r){
			x0=it->l-1;
			Node<Data> *l,*r;
			split_(it->rev,it->rt,x+1-it->l,l,r);
			ans+=l->d.cnt;
			it->rt=merge(l,r);
		}
		ans+=s.sum(x0);
		write(ans,'\n');
		la=ans;
	}
	return 0;
}
