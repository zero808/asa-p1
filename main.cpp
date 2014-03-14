#include <cstdio> //scanf
#include <cstdlib> // exit
#include <algorithm> // min
#include <list>
#include <stack>
#include <vector>

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
        Vertex() : id(0), d(UNDEFINED), low(UNDEFINED) {}
        Vertex(unsigned int _id) : id(_id), d(UNDEFINED), low(UNDEFINED) {}
        Vertex(unsigned int _id, unsigned int _d, unsigned int _low) :
            id(_id), d(_d), low(_low), onStack(false) {}
        virtual ~Vertex() {}

        unsigned int Id() const { return id; }
        unsigned int D() const { return d; }
        unsigned int Low() const { return low; }
        bool OnStack() const { return onStack; }
        std::list<Vertex*> Adjacents() const { return adjacents; }

        void setId(unsigned int _id) { id = _id; }
        void setD(unsigned int _d) { d = _d; }
        void setLow(unsigned int _low) { low = _low; }
        void setOnStack(bool b) { onStack = b; }

    private:
        unsigned int id;
        unsigned int d;
        unsigned int low;
        // To test if this vertex was already added to the stack
        bool onStack;
        //this will work as an adjacency list
        std::list<Vertex*> adjacents;
};

void visit(Vertex *v, std::stack<Vertex*> *s, unsigned int *visited);

//void SCC_Tarjan(std::vector<std::list<Vertex*> *graph)
void SCC_Tarjan(std::vector<Vertex*> graph)
{
    //The counter for the amount of vertices visited
    unsigned int visited = 0;
    // The stack needed by the algorithm
    std::stack<Vertex*> L;

    for(Vertex* v : graph) { // corrigir
        if(v->D() == UNDEFINED) {
            visit(v, &L, &visited);
        }
    }
}


void visit(Vertex *u, std::stack<Vertex*> *s, unsigned int *visited)
{
    //std::list<Vertex*>::iterator it = u->Adjacents().begin();
    u->setD(*visited);
    u->setLow(*visited);
    ++(*visited); //*visited += 1;
    s->push(u);

    for(Vertex *v : u->Adjacents()) {
        if((v->D() == UNDEFINED) || v->OnStack()) {
            if(v->D() == UNDEFINED) {
                visit(v, s, visited);
            }
            u->setLow(std::min(u->Low(), v->Low()));
        }
    }
    if(u->D() == u->Low()){
        do {
            /*
             * Adicionar os vertices que eu tiro do stack para um vector
             * em que cada vector é um scc
             */
            //vx = s->pop();
        }
        while(true);
    }
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

