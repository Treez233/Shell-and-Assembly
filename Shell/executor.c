/*
   Yi Zhu
   116513081
   yzhu1217
*/

#include <stdio.h>
#include "command.h"
#include "executor.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sysexits.h>
#include <fcntl.h>

#define SUCCESS 0
#define FAILURE 1
#define EXIT -1
static int execute_pipe(struct tree *t, int in_fd, int out_fd);
static int execute_none(struct tree *t, int in_fd, int out_fd);
static int execute_aux(struct tree *t, int in_fd, int out_fd);
static int execute_none(struct tree *t, int in_fd, int out_fd){
   int status;
   pid_t pid;

   if(strcmp(t->argv[0], "cd") == 0){
      if(chdir(t->argv[1]) < 0){
         perror(t->argv[1]);
      }
   }else if(strcmp(t->argv[0], "exit") == 0){
      exit(0);
   }else{
      if((pid = fork()) < 0){
         perror("fork error\n");
      }
      if(pid){
         wait(&status);
         return status;
      }else if (pid == 0){
         if(t->input){
            if((in_fd = open(t->input, O_RDONLY)) < 0){
               perror("Input file failed to open\n");
               exit(EX_OSERR);
            }         
            if((dup2(in_fd, STDIN_FILENO)) < 0){
               perror("dup2 read failed\n");
               exit(EX_OSERR);
            }
            if(close(in_fd) < 0){
               perror("Input file failed to close\n");
               exit(EX_OSERR);
            }
         }
         if(t->output){
            if((out_fd = open(t->output, O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0){
               perror("Output file failed to open\n");
               exit(EX_OSERR);
            }         
            if(dup2(out_fd, STDOUT_FILENO) < 0){
               perror("dup2 write failed\n");
               exit(EX_OSERR);
            }
            if(close(out_fd) < 0){
               perror("Output file failed to close\n");
               exit(EX_OSERR);
            }
         }
         if(execvp(t->argv[0], t->argv) < 0){
            fprintf(stderr, "Failed to execute %s\n", t->argv[0]);
            fflush(stdout);
            exit(EX_OSERR);
         }
      }
   }
   return SUCCESS;
}
static int execute_pipe(struct tree *t, int in_fd, int out_fd){
   int pipe_fd[2], status = 0;
   pid_t pid;
   if(t->left->output){
      fprintf(stdout, "Ambiguous output redirect.\n");
      fflush(stdout);
      return FAILURE;
   }else if(t->right->input){
      fprintf(stdout, "Ambiguous input redirect.\n");
      fflush(stdout);
      return FAILURE;
   }else{
      if(t->input && (in_fd = open(t->input, O_RDONLY)) < 0){
         perror("Input file failed to open\n");
         exit(EX_OSERR);
      }else if (t->output && (out_fd = open(t->output, O_WRONLY | O_CREAT | O_TRUNC, 0664))< 0){
         perror("Output file failed to open\n");
         exit(EX_OSERR);
      }

      if(pipe(pipe_fd) < 0){
         perror("pipe fail\n");
         exit(EX_OSERR);
      }
      if((pid = fork())< 0){
         perror("fork fail\n");
         exit(EX_OSERR);
      }
      if(pid){
         if(close(pipe_fd[1])< 0){
            perror("File failed to close.\n");
            exit(EX_OSERR);
         }
         dup2(pipe_fd[0], in_fd);
         if(execute_aux(t->right,pipe_fd[0], out_fd) != 0){
            close(pipe_fd[0]);
         }
         wait(&status);
         if(WEXITSTATUS(status) < 0){
            return FAILURE;
         }
      }else{
         if(close(pipe_fd[0]) < 0){
            perror("File failed to close.\n");
            exit(EX_OSERR);
         }
         dup2(pipe_fd[1], out_fd);
         if(execute_aux(t->left, in_fd, pipe_fd[1])){
            close(pipe_fd[1]);
            exit(EX_OSERR);
         }else{
            close(pipe_fd[1]);
            exit(SUCCESS);
         }
      }
   }
   return SUCCESS;
}
static int execute_aux(struct tree *t, int in_fd, int out_fd){
   int status;
   pid_t pid;

   if(t -> conjunction == AND){
      if(t->input && (in_fd = open(t->input, O_RDONLY)) < 0){
            perror("Input File failed to open");
      }
      if(t->output && (out_fd = open(t->output, O_WRONLY | O_CREAT | O_TRUNC, 0664))< 0){
            perror("Output File failed to open");
      }
      status = execute_aux(t->left, in_fd, out_fd);
      if(status == SUCCESS){
         execute_aux(t->right, in_fd, out_fd);
      }
   }else if(t -> conjunction == NONE){
      return execute_none(t, in_fd, out_fd);
   }else if(t -> conjunction == PIPE){
      status = execute_pipe(t, in_fd, out_fd);
   }else if(t -> conjunction == SUBSHELL){
      if((pid = fork()) < 0){
         perror("fork error");
         return FAILURE;
      }
      if(t->input && (in_fd = open(t->input, O_RDONLY) < 0)){
            perror("Input file failed to open");
            return FAILURE;
      }
      if(t->output && (out_fd = open(t->output, O_WRONLY | O_CREAT | O_TRUNC, 0664))< 0){
         perror("Output file failed to open");
         return FAILURE;
      }
      if(pid){
         wait(NULL);
      }else{
         execute_aux(t-> left, STDIN_FILENO, STDOUT_FILENO);
         exit(SUCCESS);
      }
   }
   return status;
}
int execute(struct tree *t) {
   if(t){
      return execute_aux(t, STDIN_FILENO, STDOUT_FILENO);
   }

   return SUCCESS;
}



