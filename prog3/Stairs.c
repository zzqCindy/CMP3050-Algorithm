#include <stdio.h>

#define MAX 100 

typedef struct point{
	int index;
	int pre;
}Point;

Point* ptr[MAX+1];
int visit[MAX+1];
int ans;

// BFS
void stairs(int f, int s, int g, int u, int d){
	
	if( f < 1 || f > MAX || s < 1 || s > f || g < 1 || g > f){
		printf("the input are out of range\n");
		return;
	}
	
	if(s == g){
		return;
	}	
	
	int front = 0, rear = 1;
	memset(visit,0,sizeof(visit));
	Point* p1 = (Point*)malloc(sizeof(Point));
	p1->index = s;
	p1->pre = -1;
	ptr[front] = p1;
	visit[s] = 1;
	
	while(front < rear){
		Point* top = ptr[front];
		if(top->index == g){
			ans = front;
			break;
		}
		front++;
		if(front > MAX) break;
		int i;
		for(i = 0; i < 2; i++){
			int step;
			if(i == 0) step = u;
			if(i == 1) step = -d;
			if(top->index + step <= 0 || top->index + step > f)
				continue;
			if(visit[top->index+step])
				continue;
			visit[top->index+step] = 1;
			Point* p1 = (Point*)malloc(sizeof(Point));
			p1->index = top->index+step;
			p1->pre = front-1;
			ptr[rear] = p1;
			rear++;
		}
	}
} 

void output(int x){
	if(x == -1){
		return;
	}
	output(ptr[x]->pre);
	printf("%d ", ptr[x]->index);
	if(x != ans)
		printf("-> ");
	else
		printf("\n");
}

int main(){
	
	int floors, start, goal, up, down;
	while(1){
		ans = -1;
		printf("please enter the input(enter 0 to exit): ");
		scanf("%d",&floors);
		if(floors == 0)
			break;
		scanf("%d%d%d%d",&start,&goal,&up,&down);
		stairs(floors,start,goal,up,down);
		if(ans != -1)
			output(ans);
		else
			printf("use the stairs\n");
	}
	
	return 0;
} 
