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
  switch (mysb.st_mode & S_IFMT) {
    case S_IFBLK:
      filetype = "block special file";
      break;
    case S_IFCHR:
      filetype = "character special file";
      break;
    case S_IFDIR:
      filetype = "directory";
      break;
    case S_IFIFO:
      filetype = "fifo";
      break;
    case S_IFLNK:
      filetype = "symbolic link";
      break;
    case S_IFREG:
      filetype = "regular file";
      break;
    case S_IFSOCK:
      filetype = "socket";
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
}
