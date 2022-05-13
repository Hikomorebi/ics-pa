#include "common.h"
enum {
  SYS_none,
  SYS_open,
  SYS_read,
  SYS_write,
  SYS_exit,
  SYS_kill,
  SYS_getpid,
  SYS_close,
  SYS_lseek,
  SYS_brk,
  SYS_fstat,
  SYS_time,
  SYS_signal,
  SYS_execve,
  SYS_fork,
  SYS_link,
  SYS_unlink,
  SYS_wait,
  SYS_times,
  SYS_gettimeofday
};
//#include "syscall.h"

void sys_exit(int a) {
  _halt(a);
}
int sys_write(int fd,void* buf,size_t len) {
	int i = 0;
	if (fd == 1 || fd == 2) {
    Log("buffer:%s",(char*)buf);
		for(; len > 0; len--) {
			_putc(((char*)buf)[i]);
			i++;;
		}
	}
  else {
    panic("Unhandled fd = %d in sys_write",fd);
    return -1;
  }
	return i;
}

int sys_brk(int a)
{
  return 0;
}
_RegSet* do_syscall(_RegSet *r) {
  uintptr_t a[4];
  int result = -1;
  a[0] = SYSCALL_ARG1(r);
  a[1] = SYSCALL_ARG2(r);
  a[2] = SYSCALL_ARG3(r);
  a[3] = SYSCALL_ARG4(r);

  switch (a[0]) {
    case SYS_none:
      result = 1;
      break;
    case SYS_exit:
      sys_exit(a[1]);
      break;
    case SYS_write:
      result = sys_write(a[1],(void *)a[2],a[3]);
      break;
    case SYS_brk:
      result = sys_brk(a[1]);
      break;
      
    default: panic("Unhandled syscall ID = %d", a[0]);
  }
  SYSCALL_ARG1(r) = result;

  return NULL;
}
