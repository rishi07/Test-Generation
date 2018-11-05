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
vector<int> v[MAX];
int par[MAX];

void dfs(int i,int p)
{
	for(int j=0;j<v[i].size();j++)
	{
		if(v[i][j]!=p)
		{
			par[v[i][j]]=i;
			dfs(v[i][j],i);
		}
	}
}

int main()
{
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	
	//number of testcases you want to generate (supports at max 20 files upto input19.txt)
	int testcases=5;

	//number of nodes for each testcase
	int nodes[]={3,5,10,20,25};
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
			join(x,y);
			edges.pb(mp(x,y));
			cnt--;
		}


		//printing number of nodes
		pf("%d\n",n);

		//printing edges is done in two formats. Comment out which-ever not necessary.

		//printing the edges in list format
		for(int i=0;i<edges.size();i++)
			pf("%d %d\n",edges[i].first,edges[i].second);

		//To print in array format where arr[i] is connected to i for every 1<=i<=n-1
		for(int i=0;i<edges.size();i++)
		{
			v[edges[i].first].pb(edges[i].second);
			v[edges[i].second].pb(edges[i].first);
		}
		dfs(n,-1);
		for(int i=1;i<n;i++)
			pf("%d ",par[i]);
		pf("\n");

		edges.clear();
		for(int i=0;i<=n;i++)
			v[i].clear();
	}
	return 0;
}
