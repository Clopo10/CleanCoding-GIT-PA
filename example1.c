/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/
#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
}NODE;

/// pentru simplitate, folosim int uri pt a numi restaurantele/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct Graph
{
    int v;
    int *visited;
    struct Node **alist;
}GRAPH;


typedef struct Stack
{
    int t;
    int capacity;
    int *array;
}STACK;


NODE *create_Node(int v)
{
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

void add_Edge(GRAPH *graph,int src,int dest)
{
    NODE *new_node1 = create_Node(dest);
    new_node1->next = graph->alist[src];
    graph->alist[src] = new_node1;

    NODE *new_node2 = create_Node(src);
    new_node2->next = graph->alist[dest];
    graph->alist[dest] = new_node2;
}

GRAPH *create_Graph(int v)
{
    GRAPH *graph =(GRAPH*)malloc(sizeof(GRAPH));
    graph->v = v;
    graph->alist =(NODE**)malloc(v * sizeof(NODE *));
    graph->visited =(int*)malloc(v * sizeof(int));

    for (int i = 1; i <= v; i++)
    {
        graph->alist[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

STACK *create_Stack(int capacity)
{
    STACK *stack =(STACK*)malloc(sizeof(STACK));
    stack->array =(int*)malloc(capacity * sizeof(int));
    stack->t = -1;
    stack->capacity = capacity;

    return stack;
}

void Push(int pushed, STACK *stack)
{
    stack->t = stack->t + 1;
    stack->array[stack->t] = pushed;
}

int DFS(GRAPH *graph, STACK *stack, int vertex_nr, int dest)
{
    NODE *adj_list = graph->alist[vertex_nr];
    NODE *aux = adj_list;

    graph->visited[vertex_nr] = 1;
    Push(vertex_nr, stack);

    if (vertex_nr == dest)
    {
        return 1;
    }

    while (aux != NULL) {
        int connected_vertex = aux->data;
        if (graph->visited[connected_vertex] == 0)
        {
            int found = DFS(graph, stack, connected_vertex, dest);

            if (found)
            {
                return 1;
            }
        }

        aux = aux->next;
    }

    return 0;
}

void insert_Edges(GRAPH *graph,int edge_nr, int node_nr)
{
    int src, dest, i;
    for (i = 1; i <= edge_nr; i++)
    {
        printf("Introduceti %d muchii (de la 1 pana la %d):\n", edge_nr, node_nr);
        scanf("%d%d", &src, &dest);
        add_Edge(graph, src, dest);
    }
}

void Wipe(GRAPH *graph)
{
    for (int i = 0; i < graph->v; i++)
    {
        graph->visited[i] = 0;
    }
}

int can_be_Reached(GRAPH *graph, int src, int dest)// 0 sau 1 daca poate fi sau nu ajuns
{
    STACK *stack = create_Stack(graph->v);

    int found = DFS(graph, stack, src, dest);

    Wipe(graph);

    return found;
}


int main()
{

    int node_nr;
    int edge_nr;
    int vertex_1;
    int vertex_2;

    printf("Cate noduri are graful?\n");
    scanf("%d", &node_nr);

    GRAPH *graph = create_Graph(node_nr);

    printf("Cate muchii are graful?\n");
    scanf("%d", &edge_nr);

    insert_Edges(graph, edge_nr, node_nr);

    STACK *stack1 = create_Stack(2 * node_nr);
    STACK *stack2 = create_Stack(2 * node_nr);

    printf("\nIntroduceti doua noduri pentru a verifica daca exista drum intre ele:\n");
    scanf("%d %d", &vertex_1, &vertex_2);

    if (can_be_Reached(graph, vertex_1, vertex_2))
    {
        printf("Exista drum!");
    }
    else
    {
        printf("Nu exista drum!");
    }
}
