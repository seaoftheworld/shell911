0.00 0.00 0000000000000000000000000000000000000000000000000000000000000000000


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_prompt(void);
void get_input(char *);
void deploy_input(char * buf, char arg_deployed[5][11], int *argc);
void print_args( char arg_deployed[5][11] );



int main(int argc, char **argv){

  int i;
  int argcount;
  char arg_deployed[5][11];
  char  *buf = NULL;
//char **arg = NULL;

  buf = (char *)malloc(22);
  if(buf == NULL){
    printf("Failed to malloc.\n");
    exit(-1);
  }

  while(1){
    argcount = 0;
    memset(buf, 0x31, 22);
    for(i=0; i<5; i++){
      memset(arg_deployed[i], 0x31, 11);
    }
    for(i=0; i<5; i++){
      arg_deployed[i][10] = '\0';
    }
    //printf("starting print prompt\n");
    print_prompt();
    
    get_input(buf);
    if( strcmp(buf, "We go then!\n")==0 ){
      break;
    }

    printf("CMD Entered:\n");
    printf("%s\n", buf);
    //printf("__printing_cmd_over__\n");

    deploy_input(buf, arg_deployed, &argcount);
    print_args( arg_deployed );
    //print_args( arg_deployed );
  }

  free(buf);
  return 0;
}

//---------------------------------prinf_prompt
void print_prompt(void){
  printf("shell911$$ ");
}

//---------------------------------get_input
void get_input(char *buf){

  int len=0;
  char ch = '\0';

  for(len=0; len<21 && ch != '\n'; len++){
    ch = getchar();
    buf[ len ] = ch;
  }                 //                                [0       ...         19 20     21]
                    //len == 21 trigered at least by " 0123456789 0123456789 'enter' ".
  if( len == 21 && buf[20]!='\n' )
    ch = getchar(); //if len==21 by now, ch stores the buff[21] value, in order to confirm wether it's '\n' latter.
  buf[ len ] = '\0';//then wites to last byte of arry to be '\0', whether it's buff[21] or buf[1~20]

  if( len == 21 && buf[20] == '\n' ){    //if buf[20] == '\n', 
    printf("Warning0: cmd buffer[0~21],\n\
            valid input exactly fills [0~19],\n\
            buf[20] == '\\n',\n\
            buf[21]== '\\0'.\n");
  }
  else if( len == 21 && ch == '\n' ){    //check wether the former buff[21] value was '\n' before it was written '\0' when len==21
    printf("Warning1: cmd buffer[0~21],\n\
            valid input exactly fills [0~20],\n\
            buf[21] used to be '\\n',\n\
            buf[21] is writen '\\0' now.\n");
  }
  else if( len ==21 ){                   //                     if buff[21] != '\n', write its value to be '\0' and omitt the latter input.
    printf("Warning2: cmd buffer[0~21],\n\
            valid input already filled [0~20],\n\
            buf[21] used to be '%c',\n\
            buf[21] is writen '\\0' now,\n\
            latter input ommitted.\n", ch);
  }

  while(ch != '\n')//consume the input in stream from stream[22...)
      ch = getchar();
}

//---------------------------------deploy_input
void deploy_input(char *buf, char arg_deployed[5][11], int *argc){

  char *p;
  char *q;
  int   n;

  p = buf;
  *argc==0;
  
  while(1){
    if ( *p == '\n' || *p == '\0' )
      break;

    if ( *p == ' ' )
      p++;

    else{
      if( *argc>5 ){
        printf("there's already 5 args, the rest args ignored.\n");
        break;
      }
      q = p; n=0;
      
      while(*q!='\0' && *q!='\n' && *q!=' '){
        n++; q++;
      }

      if( *argc !=0 && n>10 ){
        printf("Argument too long.\n");
        n = 10;
      }

      if( *argc !=0 ){
        strncpy(arg_deployed[(*argc)-1], p, n);
        arg_deployed[(*argc)-1][n] = '\0';
      }

      *argc+=1; p = q;
    }
  }
}



//---------------------------------print_args
void print_args( char arg_deployed[5][11] ){

  int i;
  for(i=0; i<5; i++)
    printf( "arg[%d] = \"%s\"\n", i, arg_deployed[i] );
}




















/*
  //char array[4] = {'a', 'b', 'c', '\0'};
  //char array2[5] = {'a', 'b', 'c', 'd', '\0'};

  while(1){
    putchar('=');
    printf("%s", array2);
    array2[0] = '\a';
    putchar(array2[0]);
    printf(".\n");

    while(1){

      printf("__1__.\n");
      for(c=0; c<5; c++){
        putchar('=');
        putchar('\r');
        printf("===.");
        sleep(1);
      }

      printf("_2_2__");
      //for(c=0; c<5; c++){
        putchar('\b');
        //sleep(1);
        putchar('\b');
        //sleep(1);
        putchar('\b');
        //sleep(1);
        putchar('\b');
        sleep(1);
      //}
    }


    c = getchar();

    switch(c){
      case '\a':
      break;

      default:
      printf("%c, 0x%x\n", c, c);
      break;
    }

//*/
