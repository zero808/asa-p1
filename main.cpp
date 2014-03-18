#include <cstdio> //scanf
#include <cstdlib> // exit
#include <algorithm> // min
#include <list>
#include <stack>
#include <vector>

//using namespace std;

/* Constants */
#define UNDEFINED -1

class Vertex {
    public:
        Vertex() : id(0), d(UNDEFINED), low(UNDEFINED), onStack(false) {}
        Vertex(int _id) : id(_id), d(UNDEFINED), low(UNDEFINED), onStack(false) {}
        Vertex(int _id,  int _d,  int _low) :
            id(_id), d(_d), low(_low), onStack(false) {}
        virtual ~Vertex() {}

        int Id() { return id; }
        int D() { return d; }
        int Low() { return low; }
        bool OnStack() { return onStack; }
        std::list<Vertex*> Adjacents() { return adjacents; }

        void setId( int _id) { id = _id; }
        void setD( int _d) { d = _d; }
        void setLow( int _low) { low = _low; }
        void setOnStack(bool b) { onStack = b; }

        void addAdjacent(Vertex* v) { adjacents.push_back(v); }

    private:
        int id;
        int d;
        int low;
        // To test if this vertex was already added to the stack
        bool onStack;
        //this will work as an adjacency list
        std::list<Vertex*> adjacents;
};

/* Output */
/*  número de grupos máximos de pessoas que partilham informação; */
int groups = 0;
/* Uma linha com o tamanho do maior grupo máximo de pessoas que partilham informação; */
unsigned int biggest = 0;
/* número de grupos máximos de pessoas que partilham informação apenas dentro do grupo; */
int own_group_only = 0;
/* Groups of SCCs */
std::vector<std::vector<Vertex*> > sccs;

void visit(Vertex *v, std::stack<Vertex*> *s, int *visited);

//void SCC_Tarjan(std::vector<std::list<Vertex*> *graph)
void SCC_Tarjan(std::vector<Vertex*> *graph)
{
    //The counter for the amount of vertices visited
    int visited = 0;
    std::vector<Vertex*>::iterator it;
    // The stack needed by the algorithm
    std::stack<Vertex*> L;

    //for(Vertex* v : *graph) { // corrigir
    printf("size do grafo: %lu\n", graph->size());
    for(it = graph->begin(); it != graph->end(); ++it) {
        int i = (*it)->D();
        /* if((*it)->D() == UNDEFINED) { */
        if(i == UNDEFINED) {
            printf("i = %d\n", i);
            printf("id = %d\n", (*it)->Id());
            visit(*it, &L, &visited);
        }
        else {
            printf("i = %d\n", i);
            printf("id = %d\n", (*it)->Id());
            puts("skip");
        }
        printf("visited = %d\n", visited);
    }

    /* visit(*it, &L, &visited); */
}


void visit(Vertex *u, std::stack<Vertex*> *s, int *visited)
{
    std::list<Vertex*>::iterator it;
    Vertex *vp = NULL;
    std::vector<Vertex*> scc;
    /*  int grp_size(): */
    u->setD(*visited);
    u->setLow(*visited);
    ++(*visited); //*visited += 1;
    u->setOnStack(true);
    s->push(u);

    for(it = u->Adjacents().begin(); it != u->Adjacents().end(); ++it) {
        if(((*it)->D() == UNDEFINED) || (*it)->OnStack()) {
            if((*it)->D() == UNDEFINED) {
                visit((*it), s, visited);
            }
            u->setLow(std::min(u->Low(), (*it)->Low()));
        }
    }
    if(u->D() == u->Low()){
        do {
            /*
             * Adicionar os vertices que eu tiro do stack para um vector
             * em que cada vector é um scc
             * problema: adicionar cada vertice ao mesmo vector
             * no fim adicionar esse vector ao vector que guarda todos os SCCs
             */
            vp = s->top(); //Get the element at the top
            s->pop(); //because pop doesn't return anything
            if(vp != NULL) {
                vp->setOnStack(false); //add the vertex to a scc
                scc.push_back(vp);
            }
        }
        while(u->Id() != vp->Id()); //since they hold adresses this should do the right comparisson, otherwise compare the id

        //update the size of the biggest group if we have to
        printf("scc size =%lu\n", scc.size());
        if(scc.size() > biggest) {
            biggest = scc.size();
        }
        sccs.push_back(scc);
        printf("sccs size =%lu\n", sccs.size());
    }
}

void xpto(std::vector<Vertex*> *v) {
    std::vector<Vertex*>::iterator it;
    int i = 0;
    for(it= v->begin(); it != v->end(); ++it){
        (*it)->setD(i);
        (*it)->setLow(i++);
    }
}
int main(int argc, char *argv[])
{
    /* The values for the number of people and the sharing between them  */
    int N = 6, P = 7;
    //int a = 0, b = 0;
    int a[] = {1, 2, 3, 4, 5, 6, 3};
    int b[] = {2, 3, 4, 5, 6, 1, 5};
    std::vector<Vertex*>::iterator it;
    std::list<Vertex*>::iterator it2;

//    if(scanf("%d %d", &N, &P) != 2)
 //       exit(EXIT_FAILURE);

    std::vector<Vertex*> graph((N+1), new Vertex(0, -1, -1));
    for(int i = 0; i < P; ++i) {
 //       if(scanf("%d %d", &a, &b) != 2)
//            exit(EXIT_FAILURE);
        /* scanf("%d %d", &a, &b); */
        //else {
            graph[a[i]]->setId(a[i]);
  //          graph[a]->setId(a);
        printf("a = %d, Id = %d, d=%d, low = %d\n", a[i], graph[a[i]]->Id(), graph[a[i]]->D(), graph[a[i]]->Low());
        /* printf("a = %d, Id = %d\n", a, graph[a].Id()); */
            //graph[a]->addAdjacent(graph[b]);
            graph[a[i]]->addAdjacent(graph[b[i]]);
        //}
    }
    printf("Size do grafo %lu\n", graph.size());
    puts("passou o primeiro for");
    for(it = graph.begin(); it != graph.end(); ++it){
        printf("id exterior = %d\n", (*it)->Id());
        for(it2 = (*it)->Adjacents().begin(); it2 != (*it)->Adjacents().end(); ++it2) {
            unsigned long uls = (*it)->Adjacents().size();
            printf("Size da lista de adj. %lu", uls);
            printf("id adjacente = %d, ", (*it2)->Id());
        }
        puts("");
    }
    puts("passou o segundo for");
    //SCC_Tarjan(&graph);
    xpto(&graph);
    puts("passou o xpto");
    for(int i = 0; i < N; ++i) {
        printf("a = %d, Id = %d, d=%d, low = %d\n", a[i], graph[a[i]]->Id(), graph[a[i]]->D(), graph[a[i]]->Low());
    }
    puts("passou o ultimo for");
/*
    groups = sccs.size();
    own_group_only = groups;
    printf("%d\n%u\n%d\n", groups, biggest, own_group_only);
  */
    exit(EXIT_SUCCESS);
}

