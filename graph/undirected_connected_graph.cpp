//-----Author: Saptarshi Dey 
//-----Handle: rishi_07

#include<bits/stdc++.h>
#define ll long long
#define mp make_pair
#define pb push_back
#define si(x) scanf("%d",&x)
#define sl(x) scanf("%lld",&x)
#define pf printf
#define trace1(x) cerr<<#x<<": "<<x<<endl;
#define trace2(x,y) cerr<<#x<<": "<<x<<" | "<<#y<<": "<<y<<endl;
#define trace3(x,y,z) cerr<<#x<<": "<<x<<" | "<<#y<<": "<<y<<" | "<<#z<<": "<<z<<endl;
using namespace std;
 
ll mod=1e9+7;
 
ll modexp(ll x,ll n)
{
    if(n==0)
        return 1;
    if(n%2==0)
    {
        ll y=modexp(x,n/2)%mod;
        return (y*y)%mod;
    }
    return (x*modexp(x,n-1)%mod)%mod;
}
 
ll powr(ll x,ll n)
{
    ll ans=1;
    for(int i=1;i<=n;i++)
        ans=ans*x;
    return ans;
}

const int MAX=100005;

int a[MAX];
int s[MAX];


//------------------------------------DSU template starts here
void init(int n)
{
    for(int i=1;i<=n;i++)
    {
        a[i]=i;
        s[i]=1;
    }
}

int root(int x)
{
    while(a[x]!=x)
    {
        a[x]=a[a[x]];
        x=a[x];
    }
    return x;
}

bool query(int x,int y)
{
    if(root(x)==root(y))
        return true;
    return false;
}

void join(int x,int y)
{
    if(query(x,y)==true)
        return;
    int parx=root(x);
    int pary=root(y);
    if(s[parx]<s[pary])
    {
        a[parx]=pary;
        s[pary]+=s[parx];
    }
    else
    {
        a[pary]=parx;
        s[parx]+=s[pary];
    }
}
//-----------------------------DSU template ends here

//to store the list of edges
vector<pair<int,int> > edges;

int main()
{
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	//seed
	srand(time(0));
	
	//number of testcases you want to generate (supports at max 20 files upto input19.txt)
	int testcases=5;

	//number of nodes for each testcase
	int nodes[]={3,5,10,20,25};

	//make sure number of edges is less than or equal to (n*(n-1))/2, where n is number of nodes 
	int edge_cnt[]={3,7,15,43,100};
	char input[]="input/input00.txt";

	for(int t=0;t<testcases;t++)
	{
		if(t==10)
		{
			input[11]='1';
			input[12]='0';
		}
		else if(t>0)
		{
			input[12]++;
		}
		freopen(input,"w",stdout);
		
		int n=nodes[t];

		//set to check repitition of edges
		set<pair<int,int> > connect;
		
		init(n);
		int cnt=n-1;
		int low = 1;
		int high = n;
		while(cnt)
		{
			int x=uniform_int_distribution<int>(low, high)(rng);
			int y=uniform_int_distribution<int>(low, high)(rng);
			if(query(x,y)==true)
				continue;
			connect.insert(mp(min(x,y),max(x,y)));
			join(x,y);
			edges.pb(mp(x,y));
			cnt--;
		}
		int extra=edge_cnt[t]-(n-1);

		while(extra)
		{
			int x=uniform_int_distribution<int>(low, high)(rng);
			int y=uniform_int_distribution<int>(low, high)(rng);
			if(x==y||connect.count(mp(min(x,y),max(x,y))))
				continue;
			extra--;
			connect.insert(mp(min(x,y),max(x,y)));
			edges.pb(mp(x,y));
		}

		//printing number of nodes
		pf("%d\n",n);

		//printing the edges in list format
		for(int i=0;i<edges.size();i++)
			pf("%d %d\n",edges[i].first,edges[i].second);
		edges.clear();
	}
	return 0;
}
