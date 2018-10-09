#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "More or Less Arguments!\n");
    return EXIT_FAILURE;
  }
  struct stat mysb;
  if (lstat(argv[1], &mysb) == -1) {
    fprintf(stderr, "lstat error\n");
    return EXIT_FAILURE;
  }
  fprintf(stdout, "  File: %s\n", argv[1]);

  char * filetype;
  char access[11];
  switch (mysb.st_mode & S_IFMT) {
    case S_IFBLK:
      filetype = "block special file";
      access[0] = 'b';
      break;
    case S_IFCHR:
      filetype = "character special file";
      access[0] = 'c';
      break;
    case S_IFDIR:
      filetype = "directory";
      access[0] = 'd';
      break;
    case S_IFIFO:
      filetype = "fifo";
      access[0] = 'p';
      break;
    case S_IFLNK:
      filetype = "symbolic link";
      access[0] = 'l';
      break;
    case S_IFREG:
      filetype = "regular file";
      access[0] = '-';
      break;
    case S_IFSOCK:
      filetype = "socket";
      access[0] = 's';
      break;
    default:
      filetype = "unknown???";
      break;
  }
  fprintf(stdout,
          "  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
          mysb.st_size,
          mysb.st_blocks,
          mysb.st_blksize,
          filetype);
  fprintf(stdout,
          "Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
          mysb.st_dev,
          mysb.st_dev,
          mysb.st_ino,
          mysb.st_nlink);
  if (mysb.st_mode & S_IRUSR) {  //2nd
    access[1] = 'r';
  }
  else {
    access[1] = '-';
  }

  if (mysb.st_mode & S_IWUSR) {  //3rd
    access[2] = 'w';
  }
  else {
    access[2] = '-';
  }

  if (mysb.st_mode & S_IXUSR) {  //4th
    access[3] = 'x';
  }
  else {
    access[3] = '-';
  }

  if (mysb.st_mode & S_IRGRP) {  //5th
    access[4] = 'r';
  }
  else {
    access[4] = '-';
  }

  if (mysb.st_mode & S_IWGRP) {  //6th
    access[5] = 'w';
  }
  else {
    access[5] = '-';
  }

  if (mysb.st_mode & S_IXGRP) {  //7th
    access[6] = 'x';
  }
  else {
    access[6] = '-';
  }

  if (mysb.st_mode & S_IROTH) {  //8th
    access[7] = 'r';
  }
  else {
    access[7] = '-';
  }
  if (mysb.st_mode & S_IWOTH) {  //9th
    access[8] = 'w';
  }
  else {
    access[8] = '-';
  }
  if (mysb.st_mode & S_IXOTH) {  //10th
    access[9] = 'x';
  }
  else {
    access[9] = '-';
  }
  access[10] = '\0';
  fprintf(stdout, "Access: (%04o/%s)\n", mysb.st_mode & ~S_IFMT, access);

  return EXIT_SUCCESS;
}
