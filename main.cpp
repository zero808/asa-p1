#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <list>

/* Constants */
#define UNDEFINED -1

/* Output */
/*  número de grupos máximos de pessoas que partilham informação; */
unsigned int groups = 0;
/* Uma linha com o tamanho do maior grupo máximo de pessoas que partilham informação; */
unsigned int biggest = 0;
/* número de grupos máximos de pessoas que partilham informação apenas dentro do grupo; */
unsigned int own_group_only = 0;

void visit(/* vertex u)*/);

void SCC_Tarjan(/* *Graph g */)
{
    unsigned int visited = 0;
    //std::queue<G>;
}


void visit()
{
    
}

int main(int argc, char *argv[])
{
    /* The values for the number of people and the sharing between them  */
    unsigned int N = 0, P = 0;
    unsigned int a = 0, b = 0;

    if(scanf("%u %u", &N, &P) != 2)
        exit(EXIT_FAILURE);

    std::vector<std::list<int>> graph(P); /* Adjacency list */
    for(int i = 0; i < P; ++i) {
        if(scanf("%u %u", &a, &b) != 2)
            exit(EXIT_FAILURE);
        else
            graph[a].push_back(b);
        //TODO
        //iterate through the graph and see if the values are the same
    }

    exit(EXIT_SUCCESS);
}

