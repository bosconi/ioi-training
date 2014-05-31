#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cassert>

#define NMAX 610
#define PI 3.14159265

using namespace std;

struct point{
	int x,y;
	bool operator< (const point &rhs)const {
		return (1LL*y*rhs.x) < (1LL*x*rhs.y);
	}
};

long long cross(point &p1, point &p2){
	return (1LL*p1.x*p2.y - 1LL*p1.y*p2.x);
}

pair<point,int> sp[NMAX*2];
int S;

point st[NMAX];
point en[NMAX];
int N;

int init(point origin, int exc){
	int inc,i;

	S = 0;
	inc = 0;
	for(i = 0; i < N; ++i){
		if(i == exc) continue;
		st[i].x -= origin.x, st[i].y -= origin.y;
		en[i].x -= origin.x, en[i].y -= origin.y;

		if(cross(st[i],en[i]) < 0){
			swap(st[i],en[i]);
		}

		sp[S++] = make_pair(st[i],-1);
		sp[S++] = make_pair(en[i],1);

		if(st[i].y && (!en[i].y  || (st[i].y < 0) != (en[i].y < 0))){
			++inc;
		}
	}

	for(i = 0; i < S; ++i){
		if(sp[i].first.y >= 0) continue;
		sp[i].first.y = -sp[i].first.y;
		sp[i].first.x = -sp[i].first.x;
	}

	sort(sp,sp+S);

	for(i = 0; i < N; ++i){
		if(i == exc) continue;
		st[i].x += origin.x, st[i].y += origin.y;
		en[i].x += origin.x, en[i].y += origin.y;
	}

	return inc;
}

int sweep(int start){
	int max_ins,ins,i;

	max_ins = start;
	ins = start;

	for(i = S; i < N; ++i){
		ins -= sp[i].second;
		if(i < N-1 && sp[i+1] <= sp[i]) continue;
		max_ins = max(max_ins,ins);
	}

	return max_ins;
}

int compute(){
	int i,max_ins;

	max_ins = 0;
	for(i = 0; i < N; ++i){
		max_ins = max(max_ins,1+sweep(init(st[i],i)));
		max_ins = max(max_ins,1+sweep(init(en[i],i)));
	}

	return max_ins;
}

int main(){
	int i;

	scanf("%d",&N);

	for(i =0 ; i < N; ++i){
		scanf("%d%d%d%d",&st[i].x,&st[i].y,&en[i].x,&en[i].y);
	}

	printf("%d\n",compute());

	return 0;
}