#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <list>
#include <queue>
#include <string>
#include <cstring>


struct node
{
  int color; //Being 0-> white, 1->gray, 2->black;
  int dist; //Contains distance;
  int parent; //Contains the parent of this node;
};

//Função que realiza uma busca em largura no grafo;
inline int * bfs(std::list <int> edgelist[],int s,int V)
{
    node *nos = new node [V];

  for(int i=0;i<V;i++)
  {
    nos[i].color=0;
    nos[i].dist=-1;
    nos[i].parent=NULL;
  }
  //Graph initialized; =D ( or not =( )

  std::queue <int> myqueue;

      nos[s].color=1;
      nos[s].dist=0;
      nos[s].parent=NULL;

      myqueue.push(s);

      while(!myqueue.empty())
      {
	int u = myqueue.front();
	std::list <int> :: iterator it;
	for(it=edgelist[u].begin();it!=edgelist[u].end();it++)
	{
	  if(nos[*it].color==0)
	    {
	      nos[*it].color=1;
	      nos[*it].dist=nos[u].dist+1;
	      nos[*it].parent=u;
	      myqueue.push(*it);
	    }
	}
	nos[u].color=2;
	myqueue.pop();
      }

      int *vetdist = new int [V];

      for(int j=0;j<V;j++)
	  vetdist[j]=nos[j].dist;

      delete nos;
      return vetdist;
};


int main(int argc,char **argv) {
  struct timeval t1m, t2m, t1, t2;
  double dtm, dtbfs;
  gettimeofday(&t1m,0);
  std::ifstream file (argv[1]);
  int V, E, v1, v2 ;

  file>>V>>E;

  std::list <int> edgelist [V];


  for (int i =0; i<E ; i++){
    file>>v1>>v2;
    edgelist[v1].push_back(v2);
    edgelist[v2].push_back(v1);
  }
  file.close();

  int **distmat = new int *[V];

  for(int i=0;i<V;i++)
      distmat[i] = new int [V];

  gettimeofday(&t1,0);
  for(int i=0;i<V;i++)
    distmat[i]=bfs(edgelist,i,V);
  gettimeofday(&t2,0);

  std::string nome = "dist-";
  std::string nomeaux = argv[1];
  nome += nomeaux;
  const char *cnome = new char [nome.size()+1];

  cnome=nome.c_str();


  std::ofstream outputfile (cnome);
  for (int i=0; i<V; i++)
    {
      for(int j=0; j<V; j++)
	outputfile<<distmat[i][j]<<"\t";
      outputfile<<std::endl;
    }
    outputfile.close();

  for(int i=0;i<V;i++)
    delete distmat[i];

  delete distmat;
  gettimeofday(&t2m,0);

  dtm=(t2m.tv_sec - t1m.tv_sec)+((t2m.tv_usec-t1m.tv_usec)/1e6);
  std::cout<<"O tempo total do programa foi: "<<dtm<<std::endl;
  dtbfs=(t2.tv_sec - t1.tv_sec)+((t2.tv_usec-t1.tv_usec)/1e6);
  std::cout<<"O tempo da função de busca foi: "<<dtbfs<<std::endl;
  return 0;
}
