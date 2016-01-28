/*
COMP3270 Assignment1
Question 1c(2)
Wu, Tien Hsuan 2013500516
*/
#include <iostream>
#include <stack> 
#include <queue>
#include <set>

using namespace std;

int nodesdiscovered=0;
bool config[9][9][9][9][9][9][9][9]={false};


class Node{
	private:
		int puzzle[3][3]; // 0 indicates empty slot
		char pm; //previous move U:up, D:down, L:left, R:right, X:initial state
		int depth; //depth of the node
		int heu; //heuristic
	public:
		Node* prev=NULL; //parent node
		Node* nextU=NULL; //child node
		Node* nextD=NULL;
		Node* nextL=NULL;
		Node* nextR=NULL;
		Node* move(char direction); //returns a Node pointer with one tile moved
		int getpiece(int a, int b); //returns puzzle[a][b]
		int getDepth(); //returns depth
		void calheu(); //calculates heuristic function
		int getheu(); //return heu
		void setpuzzle(int a, int b, int c, int d, int e, int f, int g, int h, int i); //set the puzzle
		void generatechild(); //generate the child and link with this node
		void printpuzzle(); //print the puzzle
		bool checkpuzzle(); //check if the goal state has reached
		void setpm(char p); //set the previous move
	friend bool operator <(const Node &l,const Node &r); //operator overloading required for multiset
};

queue<Node*> Q; //for generating tree
Node* tree; // tree

struct Comp {
  bool operator() (Node* l, Node* r) const{
  	return l->getheu()+l->getDepth()<r->getheu()+r->getDepth();
  }
};

void Node::setpuzzle(int a, int b, int c, int d, int e, int f, int g, int h, int i){
	puzzle[0][0]=a;
	puzzle[0][1]=b;
	puzzle[0][2]=c;
	puzzle[1][0]=d;
	puzzle[1][1]=e;
	puzzle[1][2]=f;
	puzzle[2][0]=g;
	puzzle[2][1]=h;
	puzzle[2][2]=i;
	pm='X';
	depth=0;
	config[a][b][c][d][e][f][g][h]=1;
	prev=NULL;
	nextU=NULL;
	nextD=NULL;
	nextL=NULL;
	nextR=NULL;
	calheu();
}

void Node::setpm(char p){
	pm=p;
}

void Node::calheu(){ //calculate heuristic function
	heu=0;
	switch(puzzle[0][0]){
		case 8: //requires 4 moves (heu+=4)
			heu++;
		case 5: //requires 3 moves (heu+=3)
		case 7:
			heu++;
		case 2: //requires 2 moves (heu+=2)
		case 4:
		case 6:
			heu++;
		case 1: //requires 1 move (heu+=1)
		case 3:
			heu++;
	}
	switch(puzzle[0][1]){
		case 6:
		case 8:
			heu++;
		case 3:
		case 7:
		case 5:
			heu++;
		case 2:
		case 4:
			heu++;
	}
	switch(puzzle[0][2]){
		case 6:
			heu++;
		case 3:
		case 7:
			heu++;
		case 4:
		case 8:
			heu++;
		case 1:
		case 5:
			heu++;
	}
	switch(puzzle[1][0]){
		case 2:
		case 8:
			heu++;
		case 1:
		case 7:
		case 5:
			heu++;
		case 6:
		case 4:
			heu++;
	}
	switch(puzzle[1][1]){
		case 2:
		case 6:
		case 8:
			heu++;
		case 1:
		case 7:
		case 5:
		case 3:
			heu++;
	}
	switch(puzzle[1][2]){
		case 6:
			heu++;
		case 1:
		case 7:
		case 3:
			heu++;
		case 2:
		case 4:
		case 8:
			heu++;
	}
	switch(puzzle[2][0]){
		case 2:
			heu++;
		case 1:
		case 5:
			heu++;
		case 4:
		case 8:
			heu++;
		case 3:
		case 7:
			heu++;
	}
	switch(puzzle[2][1]){
		case 2:
			heu++;
		case 1:
		case 5:
		case 3:
			heu++;
		case 6:
		case 4:
		case 8:
			heu++;
	}
	switch(puzzle[2][2]){
		case 1:
		case 3:
			heu++;
		case 2:
		case 4:
		case 6:
			heu++;
		case 5:
		case 7:
			heu++;
	}
}

int Node::getheu(){
	return heu;
}

Node* Node::move(char direction){
	Node* n = new Node;
	n->setpuzzle(puzzle[0][0],puzzle[0][1],puzzle[0][2],puzzle[1][0],puzzle[1][1],puzzle[1][2],puzzle[2][0],puzzle[2][1],puzzle[2][2]);
	switch(direction){
		case 'U':
			n->setpm('U');
			for(int i=0; i<2; i++){
				for(int j=0; j<3; j++){
					if (puzzle[i][j]==0){
						n->puzzle[i][j]=n->puzzle[i+1][j];
						n->puzzle[i+1][j]=0;
						if(config[n->getpiece(0,0)][n->getpiece(0,1)][n->getpiece(0,2)][n->getpiece(1,0)][n->getpiece(1,1)][n->getpiece(1,2)][n->getpiece(2,0)][n->getpiece(2,1)]==1){
							return NULL;
						}						
						config[n->getpiece(0,0)][n->getpiece(0,1)][n->getpiece(0,2)][n->getpiece(1,0)][n->getpiece(1,1)][n->getpiece(1,2)][n->getpiece(2,0)][n->getpiece(2,1)]=1;
						return n;
					}
				}
			}
			return NULL;
			break;
			
		case 'D':
			n->setpm('D');
			for(int i=1; i<3; i++){
				for(int j=0; j<3; j++){
					if (puzzle[i][j]==0){
						n->puzzle[i][j]=n->puzzle[i-1][j];
						n->puzzle[i-1][j]=0;
						if(config[n->getpiece(0,0)][n->getpiece(0,1)][n->getpiece(0,2)][n->getpiece(1,0)][n->getpiece(1,1)][n->getpiece(1,2)][n->getpiece(2,0)][n->getpiece(2,1)]==1){
							return NULL;
						}						
						config[n->getpiece(0,0)][n->getpiece(0,1)][n->getpiece(0,2)][n->getpiece(1,0)][n->getpiece(1,1)][n->getpiece(1,2)][n->getpiece(2,0)][n->getpiece(2,1)]=1;
						return n;
					}
				}
			}
			return NULL;
			break;
			
		case 'L':
			n->setpm('L');
			for(int i=0; i<3; i++){
				for(int j=0; j<2; j++){
					if (puzzle[i][j]==0){
						n->puzzle[i][j]=n->puzzle[i][j+1];
						n->puzzle[i][j+1]=0;
						if(config[n->getpiece(0,0)][n->getpiece(0,1)][n->getpiece(0,2)][n->getpiece(1,0)][n->getpiece(1,1)][n->getpiece(1,2)][n->getpiece(2,0)][n->getpiece(2,1)]==1){
							return NULL;
						}						
						config[n->getpiece(0,0)][n->getpiece(0,1)][n->getpiece(0,2)][n->getpiece(1,0)][n->getpiece(1,1)][n->getpiece(1,2)][n->getpiece(2,0)][n->getpiece(2,1)]=1;
						return n;				
					}
				}
			}
			return NULL;
			break;
			
		case 'R':
			n->setpm('R');
			for(int i=0; i<3; i++){
				for(int j=1; j<3; j++){
					if (puzzle[i][j]==0){
						n->puzzle[i][j]=n->puzzle[i][j-1];
						n->puzzle[i][j-1]=0;
						if(config[n->getpiece(0,0)][n->getpiece(0,1)][n->getpiece(0,2)][n->getpiece(1,0)][n->getpiece(1,1)][n->getpiece(1,2)][n->getpiece(2,0)][n->getpiece(2,1)]==1){
							return NULL;
						}						
						config[n->getpiece(0,0)][n->getpiece(0,1)][n->getpiece(0,2)][n->getpiece(1,0)][n->getpiece(1,1)][n->getpiece(1,2)][n->getpiece(2,0)][n->getpiece(2,1)]=1;
						return n;
					}
				}
			}
			return NULL;
			break;
	}
}

void Node::printpuzzle(){
	if(pm=='X'){
		cout << "Initial State:" << endl;
	}else{
		cout<<"Moved:" << pm << endl;
	}
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			cout << " " << puzzle[i][j];
		}
			cout <<  endl ;
	}
}

void Node::generatechild(){	
	if(pm!='L'){
		Node* r = new Node;
		r->setpuzzle(puzzle[0][0], puzzle[0][1], puzzle[0][2], puzzle[1][0], puzzle[1][1], puzzle[1][2], puzzle[2][0], puzzle[2][1], puzzle[2][2]);
		r=r->move('R');
		if(r!=NULL){
			nextR = r;
			r->prev=this;
			r->depth=depth+1;
			r->calheu();
			Q.push(r);
		}		
	}
	
	if (pm!='D'){
		Node* u = new Node;
		u->setpuzzle(puzzle[0][0], puzzle[0][1], puzzle[0][2], puzzle[1][0], puzzle[1][1], puzzle[1][2], puzzle[2][0], puzzle[2][1], puzzle[2][2]);
		u=u->move('U');
		if(u!=NULL){
			nextU = u;
			u->prev=this;
			u->depth=depth+1;
			u->calheu();
			Q.push(u);
		}
	}
	
	if(pm!='U'){
		Node* d = new Node;
		d->setpuzzle(puzzle[0][0], puzzle[0][1], puzzle[0][2], puzzle[1][0], puzzle[1][1], puzzle[1][2], puzzle[2][0], puzzle[2][1], puzzle[2][2]);
		d=d->move('D');
		if(d!=NULL){
			nextD = d;
			d->prev=this;
			d->depth=depth+1;
			d->calheu();
			Q.push(d);
		}
	}
	
	if(pm!='R'){
		Node* l = new Node;
		l->setpuzzle(puzzle[0][0], puzzle[0][1], puzzle[0][2], puzzle[1][0], puzzle[1][1], puzzle[1][2], puzzle[2][0], puzzle[2][1], puzzle[2][2]);
		l=l->move('L');
		if(l!=NULL){
			nextL = l;
			l->prev=this;
			l->depth=depth+1;
			l->calheu();
			Q.push(l);
		}		
	}

}

int Node::getDepth(){
	return depth;
}

bool Node::checkpuzzle(){
	return (puzzle[0][0]==0&&puzzle[0][1]==1&&puzzle[0][2]==2&&puzzle[1][0]==3&&puzzle[1][1]==4&&puzzle[1][2]==5&&puzzle[2][0]==6&&puzzle[2][1]==7&&puzzle[2][2]==8);
}

int Node::getpiece(int a, int b){
	return puzzle[a][b];
}

void delist(Node* n){
	if(n->nextD!=NULL){
		delist(n->nextD);
	}
	if(n->nextU!=NULL){
		delist(n->nextU);
	}
	if(n->nextL!=NULL){
		delist(n->nextL);
	}
	if(n->nextR!=NULL){
		delist(n->nextR);
	}
	delete n;
}

void generatetree(){
	tree = new Node;
	tree->setpuzzle(7,2,4,5,0,6,8,3,1);
	Node* x=tree;
	Q.push(x);
	while(!Q.empty()){
		x=Q.front();
		Q.pop();
		x->generatechild();
	}
	
}

int main(){

	generatetree();

	Node* x=tree;

	multiset<Node*, Comp> S;
	S.insert(x);
	while(!S.empty()){

		multiset<Node*, Comp>::iterator itr=S.begin();
		x=*itr;
		
		S.erase(S.begin());
		if(x->checkpuzzle()==true){
			break;
		}else{
			
			if(x->nextL!=NULL){
				S.insert(x->nextL);
				nodesdiscovered++;
			}
			if(x->nextU!=NULL){
				S.insert(x->nextU);
				nodesdiscovered++;
			}
			if(x->nextD!=NULL){
				S.insert(x->nextD);
				nodesdiscovered++;
			}
			if(x->nextR!=NULL){
				S.insert(x->nextR);
				nodesdiscovered++;
			}
		}
	}
	
	if(x->checkpuzzle()==false){
		cout << "Unsolvable puzzle" << endl;
	}else{
		cout<<"U denotes moving the number tile upwards to fill the space" << endl;
		cout<<"D denotes moving the number downwards tile to fill the space" << endl;
		cout<<"L denotes moving the number tile leftwards to fill the space" << endl;
		cout<<"R denotes moving the number tile rightwards to fill the space" << endl;
		
		stack<Node*> S2;
	
		while(x != NULL){
			S2.push(x);
			x=x->prev;
		}
		while(!S2.empty()){
			x=S2.top();
			S2.pop();
			x->printpuzzle();
		}
	}


	
	cout << "A* search using Manhattan distances" << endl;
	cout << "Number of nodes explored: " << nodesdiscovered << endl;
	cout << "Moves (Depth of solution): " << x->getDepth() << endl; 
	delist(x);

	return 0;
}

