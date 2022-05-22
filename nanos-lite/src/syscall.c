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
extern int mm_brk(uint32_t new_brk);
extern char _end;
extern ssize_t fs_read(int fd, void *buf, size_t len);
extern ssize_t fs_write(int fd, const void *buf, size_t len);
extern int fs_open(const char *pathname, int flags, int mode);
extern off_t fs_lseek(int fd, off_t offset, int whence);
extern int fs_close(int fd);
void sys_exit(int a) {
  _halt(a);
}
int sys_write(int fd,void* buf,size_t len) {
  Log("len=%d",len);
  if(fd ==1 || fd ==2) {
    char c;
    for(int i=0;i<len;++i){
      memcpy(&c,buf+i,1);
      Log("c=%c",c);
      _putc(c);
    }
    return len;
  }
  else if(fd>=3)
    return fs_write(fd,buf,len);
  else
    panic("Unhandled fd = %d in sys_write",fd);
  return -1;
}

int sys_brk(int addr)
{
  return mm_brk(addr);
}
int sys_open(const char* filename) {
  return fs_open(filename,0,0);
}
int sys_read(int fd,void* buf,size_t len) {
  return fs_read(fd,buf,len);
}
int sys_close(int fd) {
  return fs_close(fd);
}
int sys_lseek(int fd,off_t offset,int whence) {
  return fs_lseek(fd,offset,whence);
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
    case SYS_open:
      result = sys_open((char*)a[1]);
      break;
    case SYS_read:
      result = sys_read(a[1],(void*)a[2],a[3]);
      break;
    case SYS_close:
      result = sys_close(a[1]);
      break;
    case SYS_lseek:
      result = sys_lseek(a[1],a[2],a[3]);
      break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }
  SYSCALL_ARG1(r) = result;

  return NULL;
}
