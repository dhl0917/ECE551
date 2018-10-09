#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>  //For major and minor in Step 6
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
//Step 1
void printFirst3Lines(struct stat mysb, char * access, char * filename) {
  char * filetype;
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

  if (S_ISLNK(mysb.st_mode)) {  //Step 7
    char target[256];
    ssize_t len = readlink(filename, target, 256);
    target[len] = '\0';
    fprintf(stdout, "  File: %s -> %s\n", filename, target);
  }
  else {
    fprintf(stdout, "  File: %s\n", filename);
  }
  fprintf(stdout,
          "  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
          mysb.st_size,
          mysb.st_blocks,
          mysb.st_blksize,
          filetype);
  if (S_ISCHR(mysb.st_mode) || S_ISBLK(mysb.st_mode)) {  //Step 6
    fprintf(stdout,
            "Device: %lxh/%lud\tInode: %-10lu  Links: %-5lu Device type: %d,%d\n",
            mysb.st_dev,
            mysb.st_dev,
            mysb.st_ino,
            mysb.st_nlink,
            major(mysb.st_rdev),
            minor(mysb.st_rdev));
  }
  else {
    fprintf(stdout,
            "Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
            mysb.st_dev,
            mysb.st_dev,
            mysb.st_ino,
            mysb.st_nlink);
  }
}

//Step 2
void permissons(struct stat mysb, char * access) {
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
}

//Step 3
void printAccess(struct stat mysb, char * access) {
  struct passwd * mypasswd = getpwuid(mysb.st_uid);
  struct group * mygroup = getgrgid(mysb.st_gid);
  fprintf(stdout,
          "Access: (%04o/%s)  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
          mysb.st_mode & ~S_IFMT,
          access,
          mysb.st_uid,
          mypasswd->pw_name,
          mysb.st_gid,
          mygroup->gr_name);
}

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
//Step 4
void printTimes(struct stat mysb) {
  char * atim = time2str(&mysb.st_atime, mysb.st_atim.tv_nsec);
  char * mtim = time2str(&mysb.st_mtime, mysb.st_mtim.tv_nsec);
  char * ctim = time2str(&mysb.st_ctime, mysb.st_ctim.tv_nsec);
  fprintf(stdout, "Access: %s\n", atim);
  fprintf(stdout, "Modify: %s\n", mtim);
  fprintf(stdout, "Change: %s\n", ctim);
  fprintf(stdout, " Birth: -\n");
  free(atim);
  free(mtim);
  free(ctim);
}

int main(int argc, char ** argv) {
  //Step 1
  if (argc == 1) {
    fprintf(stderr, "NOT Enough Arguments!\n");
    return EXIT_FAILURE;
  }
  for (int i = 1; i < argc; i++) {  //Step 5
    struct stat mysb;
    if (lstat(argv[i], &mysb) == -1) {
      fprintf(stderr, "lstat error\n");
      return EXIT_FAILURE;
    }
    char * filename = argv[i];
    char access[11];
    printFirst3Lines(mysb, access, filename);
    //Step 2
    permissons(mysb, access);
    //Step 3
    printAccess(mysb, access);
    //Step 4
    printTimes(mysb);
  }
  return EXIT_SUCCESS;
}
