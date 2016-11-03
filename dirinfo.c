#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

char * UNITS(int);

int main(int argc, char const *argv[]) {
  int bytetotal = downTheRabbitHole("/");
  printf("Total size: %s\n", UNITS(bytetotal));
}


//Recursively goes through each folder to get the full file size
int downTheRabbitHole(char * filepath) {
  int bytetotal = 0;
  DIR * dd = opendir(filepath);
  struct dirent * getdir = readdir(dd);
  while (getdir != 0) {
    char * getdirstuff = (char *) malloc(sizeof(char) + sizeof(getdir->d_name) + 1);
    strcat(getdirstuff, filepath);
    strcat(getdirstuff, getdir->d_name);

    struct stat * stbuf = (struct stat *) malloc(sizeof(struct stat));;
    stat(getdirstuff, stbuf);
    //printf("Path: <%s>, File: %s, Size = %s\n", getdirstuff, getdir->d_name, UNITS(stbuf->st_size));
    if (S_ISDIR(stbuf->st_mode)) {
      printf("Directory: %s, Size: %s\n", getdir->d_name, UNITS(stbuf->st_size));
    }
    else {
      printf("File: %s, Size: %s\n", getdir->d_name, UNITS(stbuf->st_size));
    }
    if (S_ISDIR(stbuf->st_mode) && getdir->d_name != '.' && getdir->d_name[0] != '.') {
      strcat(getdirstuff, "/");
      bytetotal += downTheRabbitHole(getdirstuff);
    }
    else {
      bytetotal = bytetotal + stbuf->st_size;
    }
    getdir = readdir(dd);
  }

  return bytetotal;
}

//This function will only run if you say it in Mr. Strasser's voice
char * UNITS(int bytes) {
  char * ret = (char *) malloc(sizeof(char));
  if (bytes < 1024) {
    sprintf(ret, "%d B", bytes);
  }
  else if (bytes < 1024 * 1024) {
    sprintf(ret, "%d KB" , bytes / 1024);
  }
  else if (bytes < 1024 * 1024 * 1024) {
    sprintf(ret, "%d MB" , bytes / (1024*1024));
  }
  else {
    sprintf(ret, "%d GB" , bytes / (1024 * 1024 * 1024));
  }
  return ret;
}
