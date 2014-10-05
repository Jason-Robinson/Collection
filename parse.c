#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#define LBUFSIZ 1000
#define BSIZE 24

void copyToFile( char *temp,int j, char *line1);
void createDir(char *entry2);
int parse();

int parse()
{ 
char *temp;
char location[20] = "./";
char *line1;
char line2[LBUFSIZ];
char line3[LBUFSIZ]; 
char *stptr;
int flag = 0;
int idx = 0;
int lcount = 0; /* Cell Seperator */
struct dirent **namelist;
int j = 2;
int i;
int n;


//defines which directory to find assignments
temp = "assignment_files";
strcat(location, temp);


//grabs files in given directory, returns number of files in directory
 n = scandir(location, &namelist, 0, alphasort);
 
//loops through files in directory until it reachs the number of files in the directory
while( j < n )     
{ lcount = 0;
 //assigns file from directory to line1
 line1 = namelist[j]->d_name; 
 //while loop increment
j++;
  
strcpy(line2,line1);
stptr = line2;

/* start going character by character through the line */
while (*stptr != '\0')
{ lcount++;

// If field begins with " 
	if (*stptr == '"')
	{ 
		int flag = 0;
		idx = 0;
		while (flag == 0)
		{ 

			stptr++;
			/* Find corresponding closing " */
			while (*stptr != '"')
				{ line3[idx] = *stptr;
					idx++;
					stptr++;
				}

			stptr++;
			//if line doesn't equal null and the line separates with '-'
			if (*stptr != '\0' && *stptr == '-')
			{ 

				line3[idx] = '\0';
				
				
				printf("%s\n",line3);
				flag = 1;
			}
			//if line doesn't equal null and the line separates with '"'
			else if (*stptr != '\0' && *stptr == '"')
				{ line3[idx] = *stptr;
					idx++;
				}
			
			else
			{

				line3[idx] = '\0';
				
				printf("%s\n",line3);
				flag = 1;
			}
		} 
	}
	//if the line only starts with characters, normal
	else
	{ idx = 0;
		// if line isnt null and collects all data up to '-'
		while (*stptr != '\0' && *stptr != '-')
		{ line3[idx] = *stptr;
			idx++;
			stptr++;
		}
	line3[idx] = '\0';
	
	if (lcount == 3){
	//assignment
		
		//cleans string of ??
		for ( i = 0; i<strlen(line3) ; i++){
			if (line3[i]=='?'){
			line3[i]=' ';}}
			 
		}
	else if ( lcount == 5 ){
	//pawprint
		//removes file extension
		for ( i = 0; i<strlen(line3) ; i++){
			if (line3[i]=='.' ){
			line3[i]='\0';
			line3[i+1]='\0';
			line3[i+2]='\0';
			line3[i+3]='\0';}}
		
	}	
	//call to create directory for every iteration of loop
	
	createDir( line3);
	
	if(lcount == 5){
		copyToFile( temp,j, line1);
		//goes back to beginning of folder hierarchy for new file
		chdir("..");//back to assignment name
		chdir("..");//back to pawprint
		chdir("..");//back to assignment key
		chdir("..");//back to course name
		chdir("..");//back to collection/parent directory
		//resets for new file
		lcount = 0;
	}
	
	
	
	}
	//keeps track of the location of the current string 
	if (*stptr != '\0' && *stptr == '-')
		stptr++;
		strcpy(line2,stptr);
		stptr = line2;
		}

 

	
}

 free(namelist);
 //cleans up directory
 system("rm -rf assignment_files");
return 0;
}
//creates a directory from parameters
void createDir(char *entry2){
	
	//creates directory from entry2 name
	mkdir(entry2, S_IRWXU|S_IRGRP|S_IXGRP);
	//changes into new directory for next iteration
	chdir(entry2);
    
	
	
}
/*reads in second argument, writes a file containing assignment*/
void copyToFile( char *temp,int j, char *line1){

char ch[BSIZE];
	FILE *fout;
	FILE *fin;
	int i=0;
	char *tmp_line = malloc(strlen(line1) + 1);
	//char unzip[20] = "unzip -j ";
	strcpy(tmp_line, line1);
	
	
	//goes back to folder with the assignment_files 
	chdir("..");//back to assignment name
	chdir("..");//back to pawprint
	chdir("..");//back to assignment key
	chdir("..");//back to course name
	chdir("..");//back to collection/parent directory
	
	
	//changes to assignment file directory
	chdir(temp);
	
	
	
	
	//opens line1 that contains file data, and reads "r" from it
	 
	
	if (!(fin = fopen(line1, "r")))
	{
		fputs("could not open file!\n", stderr);
		//exit(EXIT_FAILURE);
	}
	//loops through tmp_line
	for ( i = 0; i<strlen(tmp_line) ; i++){
	//modifies arguments to make folder path, removes '-', replaces with '/'
    if (tmp_line[i]=='-'){
        tmp_line[i]='/';}
		//removes file extension
	if (tmp_line[i]=='.' ){
			tmp_line[i]='\0';
			tmp_line[i+1]='\0';
			tmp_line[i+2]='\0';
			tmp_line[i+3]='\0';}}
	
	
	//changes to directory that will hold the student file
	chdir("..");
	chdir(tmp_line);
	
	 //opens file to write "w" to 
	if (!(fout = fopen(line1, "w")))
	{
		fputs("could not open output file!\n", stderr);
		//exit(EXIT_FAILURE);
	}
	
	//writes to specified file
	while (fwrite(ch, sizeof(char), fread(ch, sizeof(char), BSIZE, fin), fout))
	{
	}
	printf("The file %s has been sent to \n%s\n", line1, tmp_line);

	
	
	fclose(fout);
	fclose(fin);
	free(tmp_line);
	//------------------------------------------------------------------------------------^
}
