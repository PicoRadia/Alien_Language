/* * * * * * * * * * * * * * * * * * * * * * * * *
*	    Tableaux , structures et pointeurs       *
*	                                	         *
*		         Radia EL HAMDOUNI               *	
*		                         	             *
* 	 	                TP6		                 * 
*                   Alien Language               * 
*						                         *
*	            MLOD- IMT LILLE DOUAI            *
*	                         		             *
* * * * * * * * * * * * * * * * * * * * * * * * */ 


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 500

unsigned int wordSize, nbWords, nbTestCases,totalSize ;

void getParameters(const char *filename){
    FILE *fp = fopen(filename, "r");
	  fscanf(fp,"%u %u %u\n", &wordSize, &nbWords, &nbTestCases);
}
 
// creation du dictionnaire 
void creerTableau(const char *filename, char MyArray[totalSize][MAX_SIZE], size_t size)
{
    size_t i;
    const size_t line_size = 600;
    char* line = malloc(line_size);
    FILE *fp = fopen(filename, "r");
   
    if (!fp)
    {
        fprintf(stderr, "File named '%s' could not be opened.\n", filename);
        
    }
    // to skip the first line
    fscanf(fp,"%u %u %u\n", &wordSize, &nbWords, &nbTestCases);
    // peupler les dictionnaires
    for (i =0; i< totalSize; i++)
    {
        if (sscanf(fgets(line, line_size, fp), "%s", MyArray[i]) != 1  )
        {
            fprintf(stderr, "Could not read word from file named '%s'.\n", filename);
            fclose(fp);
            
        }
    }
    // peupler le tableau de tast cases
   
    fclose(fp);
    
}

int OutputFile(int resList[nbTestCases]){
  FILE *fp;
  fp = fopen ("A-large-practice.correct", "w");
  for (int i = 0; i < nbTestCases; i++) {
        /* write to file using fputc() function */
            fprintf(fp, "Case #%d : %d\n",i,resList[i]);
  }
  fclose(fp);
  return 0;
}


int  isAmatch(char word[nbWords],char testCaseWord[MAX_SIZE])
{
  int index = 0;
  for(int i = 0 ; i <strlen(testCaseWord) ;i++ ){ 
    if(testCaseWord[i]=='('){
        int found = 0; // flag down
        while(testCaseWord[++i] != ')'){
            //printf("==>%c\n", testCaseWord[i]);
            //printf("%d**\n",index);
            //printf("%d //\n",i);
            if(testCaseWord[i] == word[index] ){
              found = 1;  // raise flag
            }
        }
        if(found == 0){
          return 0; // not found
        }
        index ++;     
    }
    else
    {
        if(testCaseWord[i] != word[index]){
          return 0;
        }
        index++;
    }
  }
  return 1;
}

// 

int main(int argc, char *argv[]){
	
	char *filename = "A-large-practice.in"; 
  getParameters(filename);
  printf("==================== Starting =================\n");
  printf("Les paramètres sont  : \n");
  printf("%u %u %u\n",wordSize, nbWords, nbTestCases);

  totalSize = nbTestCases + nbWords ;
  char MyArray[totalSize][MAX_SIZE];
  creerTableau(filename, MyArray,totalSize);
  printf("\n---------------------------------------\n");
    printf("Les mots du dictionnaires  : \n\n");
    for(int i = 0; i <nbWords ; i++){
      printf("%s\n",MyArray[i]);
    }
  printf("\n---------------------------------------\n");
  printf("Les testCases  : \n\n");
  for(int i = nbWords; i <=totalSize; i++){
      printf("%s\n",MyArray[i]);
  }

  //OutputFile();

  printf("\n---------------------------------------\n");
  printf("\nMATCHING/content of output file : \n");
  int resList[nbTestCases];
  int count = 0;
  int res;
  for(int j = nbWords ; j<totalSize;j++){
    for(int i=0 ; i< nbWords;i++){
      res = isAmatch(MyArray[i],MyArray[j]);
      count = count+res;
    }
    printf("\nCase #%d : %d\n",j-nbWords,count);
    resList[j-nbWords] = count ;
    count = 0;
  }

  printf("\n+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
  printf("Writing to file\n");
  printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
  OutputFile(resList);
   printf("==================== END =================\n");

	return EXIT_SUCCESS;

}


