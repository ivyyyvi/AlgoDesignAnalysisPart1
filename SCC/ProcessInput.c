#include "SCC.h"

int
ReadFileToAdjList (
  vertex **V, // Pointer to the array of vertices to be returned
  vertex **rV,
  int *numberVertices // Pointer to the number of vertices to be returned
  )
{
  int num;
  int num_max = 0;
  int temp_head;
  long int mmm; // max number of edges just for alloc
  long int mmm_reverse; // max number of edges just for alloc

  char ch;
  int ttsize;
  int collect = 0;
  int edgeStart = 1;

  char file_name[100];
#if ASK_FOR_INPUT
#else
  char default_file_name[100] = "./input_A.txt";
#endif
  char *tracker;
  FILE *fp;
  char *bytes;
  long pos;

  int vertexCount;
  int edgePool;

  vertex *pv; // array of vertices
  vertex *pv_reverse; // array of vertices

  vertex *pCurrentVertex; // current vertex
  vertex *pCurrentVertex_reverse; // current vertex

#if ASK_FOR_INPUT
  // get file name from user input
  memset (file_name, 0, sizeof(file_name));//todo
  printf ("Type File name:");
  fgets (file_name, 100, stdin);

  tracker = file_name;

  while (*tracker) {
    //DEBUG_PROCESS_INPUT ("*file_name is  (0x%x)\n", *tracker);
    if (*tracker == 0xA || *tracker == 0xD) {
      //DEBUG_PROCESS_INPUT ("found new line (0x%x)\n", *tracker);
      *tracker = 0;
      break;
    }
    tracker++;
  }
#else 
  strcpy (file_name, default_file_name);
#endif
  // open file
  fp = fopen (file_name, "r");  // read mode

  if (fp == NULL) {
    DEBUG_PROCESS_INPUT ("Error while opening the file.\n");
    return -1;
  }

  fseek(fp, 0, SEEK_END);
  pos = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  bytes = malloc(pos);
  fread(bytes, pos, 1, fp);

  //
  // alloc vertices and edges array
  //

  mmm = 5105043;
  mmm_reverse = mmm;

  pv = calloc (nnn, sizeof(vertex));

  pv_reverse = calloc (nnn, sizeof(vertex));

  // alloc pool for edge incidented on the vertex
  
  for (int i = 0; i < nnn; i++) {
    (pv + i)->degreeMax = 1; // for now. realloc when needed // todo
    (pv + i)->connectTo = malloc (sizeof (int)*((pv + i)->degreeMax));
    memset ((pv + i)->connectTo, 0, sizeof(int)*((pv + i)->degreeMax));
    (pv_reverse + i)->connectTo = malloc (sizeof (int)*((pv + i)->degreeMax));
    memset ((pv_reverse + i)->connectTo, 0, sizeof(int)*((pv + i)->degreeMax));
  }

  //
  // read file to get graph
  //
  ch = 0;
  num = 0;
  vertexCount = 0;
  for (int progress = 0; progress < pos; progress++) {

    ch = bytes[progress];

    //
    // If get a number, collect it in num.
    //
    if (ch >= 0x30 && ch <= 0x39) {
      num = num * 10 + (ch - 0x30);
      collect = 1;
    } else {

      //
      // If array is running out of space,
      // double it before putting anything in it.
      //
      if (vertexCount >= nnn) {

        //
        // If array size is not enough, double the array size.
        //
        DEBUG_PROCESS_INPUT ("-------vertice pool not enough! (%d)\n", nnn);
        nnn *= 2;
        free (pv);
        pv = malloc (sizeof (vertex) * nnn);
        free (pv_reverse);
        pv_reverse = malloc (sizeof (vertex) * nnn);
      } // if vertex array is not big enough

      if (collect == 1) { // if a number is read
        collect = 0;

        //
        // use max of num saw to be the vertices count
        // this assumes vertices index are continual no skipping
        //
        if (num > num_max) {
          num_max = num;
        }

        if (edgeStart) {
          edgeStart = 0;

          // the num collected here is the start (tail) index of vertex of an edge
          pCurrentVertex = &pv [num];

          // for reverse G, the num collected here is the end (head) of vertex of an edge
          temp_head = num;
        } else {
          edgeStart = 1;

          //
          // finish collecting an edge's two vertices
          //

          //
          // if degreeMax not big enough, double it
          //
          if (pCurrentVertex->degree >= pCurrentVertex->degreeMax) {
            DEBUG_PROCESS_INPUT ("---V[%d] degreeMax (%d) not enough!\n",\
                                   temp_head,\
                                   pCurrentVertex->degreeMax);
            pCurrentVertex->degreeMax *= 2;
            pCurrentVertex->connectTo = realloc (pCurrentVertex->connectTo, pCurrentVertex->degreeMax);
          } // if degree Max not big enough // todo, what about the reverse

          //
          // the num here collected is the end (head) of an edge
          //
          pCurrentVertex->connectTo [pCurrentVertex->degree] = num;// connectTo is 0-base
          pCurrentVertex->degree++;

          //
          // for reverse G, the num collected is the start (tail) of an edge
          //
          pCurrentVertex_reverse = &pv_reverse [num];

          //
          // if degreeMax not big enough, double it
          //
          if (pCurrentVertex_reverse->degree >= pCurrentVertex_reverse->degreeMax) {
            DEBUG_PROCESS_INPUT ("---V[%d] degreeMax (%d) not enough!\n",\
                                   num,\
                                   pCurrentVertex_reverse->degreeMax);
            pCurrentVertex_reverse->degreeMax *= 2;
            pCurrentVertex_reverse->connectTo = realloc (pCurrentVertex_reverse->connectTo, pCurrentVertex_reverse->degreeMax);
          } // if degree Max not big enough // todo, what about the reverse

          // already knew the end (head) of the edge, now fill it in.
          pCurrentVertex_reverse->connectTo [pCurrentVertex_reverse->degree] = temp_head;
          pCurrentVertex_reverse->degree++;
        } // whether or not the num is collected after a new line

        num = 0;
      } // if finish collect a number from reading the file
    } // if-else reading number or non-number
  } // while not the end of file

  //*numberVertices = vertexCount;
  *numberVertices = num_max;
  *V = pv;
  *rV = pv_reverse;

  free (bytes);
  fclose (fp);
  return 0;
}
