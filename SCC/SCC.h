#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>


extern int nnn;


#define ASK_FOR_INPUT 0
#define DEFAULT_INPUT_FILENAME "sinput3.txt"
//#define DEFAULT_INPUT_FILENAME "input.txt"
//#define DEFAULT_INPUT_FILENAME "HalfInput.txt"


#define _DEBUG

#ifdef _DEBUG
#define DEBUG(format, args...) printf("[%s:%d] "format, __FILE__, __LINE__, ##args)
#else
#define DEBUG(args...)
#endif

typedef struct _vertex vertex;
typedef struct _edge edge;

//
// Function prototypes
//

int
ReadFileToAdjList (
  vertex **V, // Pointer to the array of vertices to be returned
  vertex **rV,
  int *numberVertices // Pointer to the number of vertices to be returned
  );

//
// Struct definitions
//


struct _vertex {
  int index;
  int degree;
  int Explored;
  int leader;
  int parent_add_it_to_vertices_to_visit;
  int *connectTo;
};

struct _edge {
  int u; // vertex index 1st endpoint
  int v; // vertex index 2nd endpoint
};

struct _graph {
  vertex *V;
};

/*struct _listClass {
  vertex* vertex_list;
  vertex* (*first) (listClass *list);
};*/

