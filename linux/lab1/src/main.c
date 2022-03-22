#include <stdio.h>
#include <sys/stat.h>

#define Uread 0x00400
#define Uwrite 0x00200
#define Uuse 0x00100
#define Gread 0x00040
#define Gwrite 0x00020
#define Guse 0x00010
#define Oread 0x00004
#define Owrite 0x00002
#define Ouse 0x00001

void checkOwner(struct stat buf) {
  printf("\nowner");
  if (buf.st_mode & Uread)
    printf("read ");
  if (buf.st_mode & Uwrite)
    printf("write ");
  if (buf.st_mode & Uuse)
    printf("use ");
}
void checkGroup(struct stat buf) {
  printf("\ngroup");
  if (buf.st_mode & Gread)
    printf("read ");
  if (buf.st_mode & Gwrite)
    printf("write ");
  if (buf.st_mode & Guse)
    printf("use ");
}
void checkOther(struct stat buf) {
  printf("\nother");
  if (buf.st_mode & Oread)
    printf("read ");
  if (buf.st_mode & Owrite)
    printf("write ");
  if (buf.st_mode & Ouse)
    printf("use ");
}
void checkFile(struct stat buf) {
  printf("\nFile");
  if ((buf.st_mode & S_IFMT) == S_IFREG)
    printf("\ndefault file");
  else if ((buf.st_mode & S_IFMT) == S_IFDIR)
    printf("\ndirecrory");
  else if ((buf.st_mode & S_IFMT) == S_IFCHR)
    printf("\nsign device");
  /*else if ((buf.st_mode & S_IFMT) == S_IFIFO)
    printf("\nFIFO");*/ //work only on linux
}
int main() {
  printf("Print path\n");
  char *path;
  fscanf(stdin, "%s", path);
  struct stat buf;
  int res = stat(path, &buf);
  checkFile(buf);
  checkOwner(buf);
  checkGroup(buf);
  checkOther(buf);
  return 0;
}