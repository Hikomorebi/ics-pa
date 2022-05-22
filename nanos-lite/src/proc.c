#include "proc.h"

#define MAX_NR_PROC 4

static PCB pcb[MAX_NR_PROC];
static int nr_proc = 0;
PCB *current = NULL;

uintptr_t loader(_Protect *as, const char *filename);

void load_prog(const char *filename) {
  int i = nr_proc ++;
  _protect(&pcb[i].as);

  uintptr_t entry = loader(&pcb[i].as, filename);
  Log("aa\n\n");
  // TODO: remove the following three lines after you have implemented _umake()
  _switch(&pcb[i].as);
  current = &pcb[i];
  ((void (*)(void))entry)();
  Log("aabb\n\n");
  _Area stack;
  stack.start = pcb[i].stack;
  stack.end = stack.start + sizeof(pcb[i].stack);
Log("aabbv\n\n");
  pcb[i].tf = _umake(&pcb[i].as, stack, stack, (void *)entry, NULL, NULL);

}

_RegSet* schedule(_RegSet *prev) {
  return NULL;
}
