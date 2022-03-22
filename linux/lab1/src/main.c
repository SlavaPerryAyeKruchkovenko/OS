#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

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
  printf("\nowner ");
  if (buf.st_mode & S_IRUSR)
    printf("read ");
  if (buf.st_mode & S_IWUSR)
    printf("write ");
  if (buf.st_mode & S_IXUSR)
    printf("use ");
}
void checkGroup(struct stat buf) {
  printf("\ngroup ");
  if (buf.st_mode & S_IRGRP)
    printf("read ");
  if (buf.st_mode & S_IWGRP)
    printf("write ");
  if (buf.st_mode & S_IXGRP)
    printf("use ");
}
void checkOther(struct stat buf) {
  printf("\nother ");
  if (buf.st_mode & S_IROTH)
    printf("read ");
  if (buf.st_mode & S_IWOTH)
    printf("write ");
  if (buf.st_mode & S_IXOTH)
    printf("use ");
}
void checkFile(struct stat buf) {
  printf("\nFile ");
  if ((buf.st_mode & S_IFMT) == S_IFREG)
    printf("default file");
  else if ((buf.st_mode & S_IFMT) == S_IFDIR)
    printf("direcrory");
  else if ((buf.st_mode & S_IFMT) == S_IFCHR)
    printf("sign device");
  /*else if ((buf.st_mode & S_IFMT) == S_IFIFO)
    printf("\nFIFO");*/ //work only on linux
}
int main(int argc, char *argv[]) {
  struct stat buf;
  if (argc != 2) {
    fprintf(stderr, "Использование: %s <путь>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  if (stat(argv[1], &buf) == -1) {
    perror("stat");
    exit(EXIT_FAILURE);
  }
  checkFile(buf);
  checkOwner(buf);
  checkGroup(buf);
  checkOther(buf);
  return 0;
}