#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>


int main(void)
{
	struct dirent *de; 
    int max_roll=1;
    
    char sub[12]="CP_Lab_01_CE";
	
    int results[100]={2};

    for(int i=0;i<100;++i)results[i]=2;

	DIR *dr = opendir("lab_01");

	if (dr == NULL) 
	{
		printf("Could not open current directory" );
		return 0;
	}
    int current_student, is_valid_string;
    char* string=de->d_name;


    
	while ((de = readdir(dr)) != NULL)
    {
        string=de->d_name;
        is_valid_string=1;
        if(string[0]=='.')
            continue;

        
        for(int i=0;i<11;++i)
        {
            if(sub[i]!=string[i])
            {
                is_valid_string=0;
                break;
            }
        }

        if(is_valid_string==1)
        {
            printf("match : %s\n",string);
            current_student=(string[13]-'0')*10;
            current_student+=(string[14]-'0');

            if(current_student>max_roll)
                max_roll=current_student;
            results[current_student]=1;
    
        }
        else
        {
            current_student=((string[strlen(string)-6]-'0')*10);
            current_student+=(string[strlen(string)-5]-'0');
            
            if(current_student>max_roll)
                max_roll=current_student;

            printf("don't match : %s\n",string);

            results[current_student]=0;
            
        }
    }    
        
    printf("\n");

    FILE *fp;
    fp = fopen ("results.txt", "w");

   
    for(int i=1;i<=max_roll;++i)
    {
        

        if(results[i]==1 || results[i]==0)
        {
            char c1,c2;
            fputs("roll_no = ",fp);
            
            c1=(i/10 + '0');
            c2=(i%10 + '0');
            
            if(c1=='0')
                fputc(c2,fp);
            else
            {
                fputc(c1,fp);
                fputc(c2,fp);
            }
            fputs(" score = ",fp);
            fputc(results[i]+'0',fp);
            fputs("\n",fp);

        }
        
    }

    printf("Contents to file written Successfuly !\n");
    printf("\nReading file\n\n");

    fclose(fp);
    char buffer[30],c;
    FILE *fp2;

    fp2 = fopen("results.txt", "r"); 
        
    while ((c = getc(fp2)) != EOF) 
        printf("%c", c);
        
    
	fclose(fp2);		

	closedir(dr);	
	return 0;
    
}
