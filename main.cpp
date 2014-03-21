#include <cstdio> //scanf printf
#include <cstdlib> // exit
#include <algorithm> // min find
#include <list>
#include <stack>
#include <vector>

//using namespace std;

/* Constants */
#define UNDEFINED -1

class Vertex {
    public:
        Vertex() : id(0), d(UNDEFINED), low(UNDEFINED), sccId(0), onStack(false) {}
        Vertex(int _id) : id(_id), d(UNDEFINED), low(UNDEFINED), sccId(0), onStack(false) {}
        Vertex(int _id,  int _d,  int _low) :
            id(_id), d(_d), low(_low), sccId(0), onStack(false) {}
        virtual ~Vertex() { adjacents.clear(); }

        int Id() { return id; }
        int D() { return d; }
        int Low() { return low; }
        int SccId() { return sccId; }
        bool OnStack() { return onStack; }
        std::list<Vertex*> *Adjacents() { return &adjacents; }

        void setId( int _id) { id = _id; }
        void setD( int _d) { d = _d; }
        void setLow( int _low) { low = _low; }
        void setSCCId( int _id) { sccId = _id; }
        void setOnStack(bool b) { onStack = b; }

        void addAdjacent(Vertex* v) { adjacents.push_back(v); }

    private:
        int id;
        int d;
        int low;
        //the number of the scc;
        int sccId;
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

    for(it = graph->begin(); it != graph->end(); ++it) {
        if((*it)->D() == UNDEFINED) {
            visit(*it, &L, &visited);
        }
    }
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

    for(it = u->Adjacents()->begin(); it != u->Adjacents()->end(); ++it) {
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
                vp->setSCCId(sccs.size());
                scc.push_back(vp);
            }
        }
        while(u->Id() != vp->Id()); //since they hold adresses this should do the right comparisson, otherwise compare the id

        //update the size of the biggest group if we have to
        if(scc.size() > biggest) {
            biggest = scc.size();
        }
        sccs.push_back(scc);
    }
}

void countSharingOutside(std::vector<std::vector<Vertex*> > v) {
    bool sharesOutside;
    //assume they only share between the members of the same SCC
    own_group_only = v.size();

    //For each SCC
    for(std::vector<std::vector<Vertex*> >::iterator itx = v.begin(); itx != v.end(); ++itx) {
        sharesOutside = false;

        //for each vertex that is a member of the SCC *itx points to
        for(std::vector<Vertex*>::iterator ity = itx->begin(); (ity != itx->end())
                && !sharesOutside; ++ity) {

            //check if each Vertex has a transition to another vertex that isn't a member of the
            //same SCC
            for(std::list<Vertex*>::iterator itz = (*ity)->Adjacents()->begin();
                    itz != (*ity)->Adjacents()->end(); ++itz) {
                if((*ity)->SccId() != (*itz)->SccId()) {
                /* if(std::find(itx->begin(), itx->end(), *itz) == itx->end()) { */
                    //if at least one shares with a member of other scc:
                    //decrement the count and move on to the next SCC
                    --own_group_only;
                    sharesOutside = true;
                    break;
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    /* The values for the number of people and the sharing between them  */
    int N = 0, P = 0;
    /* variables to hold the input, where a is the node that shares with b */
    int a = 0, b = 0;
    std::vector<Vertex*>::iterator it;

    if(scanf("%d %d", &N, &P) != 2)
        exit(EXIT_FAILURE);

    std::vector<Vertex*> graph;
    //We add one more vertex because it's better than doing two subtractions
    //in order to add transitions to the right vertex
    graph.reserve(N+1);

    //Create the graph's vertices
    for(int ix = 0; ix <= N; ++ix){
        graph.push_back(new Vertex(ix, UNDEFINED, UNDEFINED));
    }

    for(int ix = 0; ix < P; ++ix) {
        // we assume it will work for now
        /* if(scanf("%d %d", &a, &b) != 2) */
        /*      exit(EXIT_FAILURE); */
        //else {
        scanf("%d %d", &a, &b);
        // we don't have to subtract 1 because there is an extra element at graph[0]
        graph[a]->addAdjacent(graph[b]);
    }

    SCC_Tarjan(&graph);
    groups = sccs.size(); //the amount of SCCs
    countSharingOutside(sccs); //the size of the SCC with more elements
    // we have to decrement groups and own_group_only because of the extra vertex
    // at graph[0]
    printf("%d\n%u\n%d\n", --groups, biggest, --own_group_only);

    //delete the vertices
    for(it = graph.begin(); it != graph.end(); ++it){
        delete *it;
    }
    graph.clear();
    graph.resize(0);
    exit(EXIT_SUCCESS);
}

