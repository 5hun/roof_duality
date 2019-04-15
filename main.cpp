#include <stdio.h>
#include <stdlib.h>
#include "QPBO.h"

typedef int REAL;

QPBO<REAL>* read_qubo_from_file(const char* filename){
    QPBO<REAL>* q;
    int num_vars, num_unary, num_pair;
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "%s\n", "error: can't read file.");
        return NULL;
    } 
    fscanf(fp, "%d %d %d", &num_vars, &num_unary, &num_pair);
    q = new QPBO<REAL>(num_vars, num_pair);
    q->AddNode(num_vars);
    for(int i = 0; i < num_vars; ++i){
        int vi;
        REAL v;
        fscanf(fp, "%d %d", &vi, &v);
        q->AddUnaryTerm(vi, 0, v);
    }
    for(int i = 0; i < num_pair; ++i){
        int vi, vj;
        REAL v;
        fscanf(fp, "%d %d %d", &vi, &vj, &v);
        q->AddPairwiseTerm(vi, vj, 0, 0, 0, v);
    }
    return q;
}

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("Usage: ./main qubo_file\n");
        return 0;
    }
    QPBO<REAL>* q = read_qubo_from_file(argv[1]);

    q->Solve();
    q->ComputeWeakPersistencies();

    for(int i = 0; i < q->GetNodeNum(); ++i){
        printf("%d\n", q->GetLabel(i));
    }

    delete q;
    return 0;
}
