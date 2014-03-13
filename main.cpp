#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stack>
#include <list>
#include <array>

//using namespace std;

/* Constants */
#define UNDEFINED -1

/* Output */
/*  número de grupos máximos de pessoas que partilham informação; */
unsigned int groups = 0;
/* Uma linha com o tamanho do maior grupo máximo de pessoas que partilham informação; */
unsigned int biggest = 0;
/* número de grupos máximos de pessoas que partilham informação apenas dentro do grupo; */
unsigned int own_group_only = 0;

class Vertex {
    public:
        Vertex() : d(UNDEFINED) {}
        Vertex(unsigned int _id) : id(_id), d(UNDEFINED), low(UNDEFINED) {}
        Vertex(unsigned int _id, unsigned int _d, unsigned int _low) :
            id(_id), d(_d), low(_low) {}
        virtual ~Vertex() {}

        unsigned int Id() const { return id; }
        unsigned int D() const { return d; }
        unsigned int Low() const { return low; }
    private:
        unsigned int id;
        unsigned int d;
        unsigned int low;
        //this will work as an adjacency list
        std::list<Vertex*> adjacents;
};

void visit(Vertex *v);

//void SCC_Tarjan(std::vector<std::list<Vertex*> *graph)
void SCC_Tarjan(std::vector<Vertex*> graph)
{
    //The counter for the amount of vertices visited
    unsigned int visited = 0;
    // The stack needed by the algorithm
    std::stack<Vertex*> L;
    // We need to know if a given vertex is on the stack
    //std::array<bool, graph.size()> onStack;
    //bool[graph->size()] onStack; //V is the number of vertices on the graph;

    for(Vertex* v : graph) {
        if(v->D() == UNDEFINED) {
            visit(v);
        }
    }
}


void visit(Vertex *v)
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

