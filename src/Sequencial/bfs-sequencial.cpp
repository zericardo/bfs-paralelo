#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <list>

int main(int argc,char **argv) {
  std::ifstream file (argv[1]);
  int V, E, v1, v2 ;

  file>>V>>E;

  std::list <int> adjlist [V];

  for (int i =0; i<E ; i++){
    file>>v1>>v2;
    adjlist[v1].push_back(v2);
    adjlist[v2].push_back(v1);
    std::cout<<v1<<" "<<v2<<std::endl;
  }
  
  return 0;
}
