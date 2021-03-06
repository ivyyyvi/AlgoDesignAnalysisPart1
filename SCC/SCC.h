#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>


extern int nnn;

#pragma once

#define ASK_FOR_INPUT 0
#define PREFIX_PATH "/Users/ivy/SCC_Xcode/SCC/SCC/"

//for building in Xcode
#define DEFAULT_INPUT_FILENAME_Z
//#define _DEBUG_MAIN
//#define _DEBUG_PROCESS_INPUT
//#define _DEBUG_DFS
//#define _DEBUG

// input_Z.txt is the input from PA
#ifdef DEFAULT_INPUT_FILENAME_Z
  #define DEFAULT_INPUT_FILENAME "/Users/ivy/SCC_Xcode/SCC/SCC/input_Z.txt"
#endif
#ifdef DEFAULT_INPUT_FILENAME_A
#define DEFAULT_INPUT_FILENAME "/Users/ivy/SCC_Xcode/SCC/SCC/input_A.txt"
#endif
#ifdef DEFAULT_INPUT_FILENAME_B
  #define DEFAULT_INPUT_FILENAME "/Users/ivy/SCC_Xcode/SCC/SCC/input_B.txt"
#endif
#ifdef DEFAULT_INPUT_FILENAME_C
  #define DEFAULT_INPUT_FILENAME "/Users/ivy/SCC_Xcode/SCC/SCC/input_C.txt"
#endif
#ifdef DEFAULT_INPUT_FILENAME_D
  #define DEFAULT_INPUT_FILENAME "/Users/ivy/SCC_Xcode/SCC/SCC/input_D.txt"
#endif
#ifdef DEFAULT_INPUT_FILENAME_E
  #define DEFAULT_INPUT_FILENAME "/Users/ivy/SCC_Xcode/SCC/SCC/input_E.txt"
#endif
#ifdef DEFAULT_INPUT_FILENAME_F
  #define DEFAULT_INPUT_FILENAME "/Users/ivy/SCC_Xcode/SCC/SCC/input_F.txt"
#endif
#ifdef DEFAULT_INPUT_FILENAME_G
  #define DEFAULT_INPUT_FILENAME "/Users/ivy/SCC_Xcode/SCC/SCC/input_G.txt"
#endif
#ifdef DEFAULT_INPUT_FILENAME_H
  #define DEFAULT_INPUT_FILENAME "/Users/ivy/SCC_Xcode/SCC/SCC/input_H.txt"
#endif

#ifdef _DEBUG_PROCESS_INPUT
#define DEBUG_PROCESS_INPUT(format, args...) printf("[%s:%s:%d] \t"format, __FILE__, __FUNCTION__, __LINE__, ##args)
#else
#define DEBUG_PROCESS_INPUT(args...)
#endif


#ifdef _DEBUG_DFS
#define DEBUG_DFS(format, args...) printf("[%s:%s:%d] \t"format, __FILE__, __FUNCTION__, __LINE__, ##args)
#else
#define DEBUG_DFS(args...)
#endif

#ifdef _DEBUG_MAIN
#define DEBUG_MAIN(format, args...) printf("[%s:%s:%d] \t"format, __FILE__, __FUNCTION__, __LINE__, ##args)
#else
#define DEBUG_MAIN(args...)
#endif

#ifdef _DEBUG
#define DEBUG(format, args...) printf("[%s:%s:%d] \t"format, __FILE__, __FUNCTION__, __LINE__, ##args)
#else
#define DEBUG(args...)
#endif

typedef struct _vertex vertex;
typedef struct _edge edge;

//
// Function prototypes
//

int
PopEnd (int *wholedeal, int numTotal);

int
first (int *wholedeal, int numTotal);

void
append (int vertex_to_append, int *vertices_to_visit, int num_vertices_to_visit);

void
prepend (int vertex_to_prepend, int *vertices_to_visit, int num_vertices_to_visit);

void
takeout (int vertex_to_takeout, int *vertices, int num_vertices);

int
ReadFileToAdjList (
  vertex **V, // Pointer to the array of vertices to be returned
  vertex **rV,
  int *numberVertices // Pointer to the number of vertices to be returned
  );

int
DFS_Loop (
  int which_pass,
  vertex *V, // Pointer to the array of vertices to be returned
  int numberVertices, // Pointer to the number of vertices to be returned
  int *index_sequence_by_finish_time,
  int *index_sequence_by_finish_time_2,
  int *leader_group //int *leaderContainingNodes
  );

//
// Struct definitions
//


struct _vertex {
  int degree;
  int degreeMax;
  int leader;
  int index; // for debug
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
