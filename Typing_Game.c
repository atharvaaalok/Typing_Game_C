// check position += (r + 2)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>


#define INNER 5
#define OUTER 20
#define MAX (INNER*OUTER)
#define WORDS_IN_LINE 20
#define MAX_WORD_LEN 20


void rand_num();                 // sets the array random[] to a set of MAX random numbers
void gen_line();                 // sets the line[] array to WORDS_IN_LINE random words
FILE* goto_line(int line_no);
void set_fd_array(FILE* fd);
void input();
void sig_handler(int signum);
void sig_handlers(int signum);
void user_modifier();
char* gen_word_ith(int i);
char* user_word_ith(int i);
int compare();
void tot_user_words();
void result();


int random_array[MAX];
char line[WORDS_IN_LINE][MAX_WORD_LEN];
int fd_array[1000];
char user_input[500];
char gen_input[500];


char user_word_i[20];
char gen_word_i[20];
int keystrokes;
int total_user_words;
int tot_words = 0;
FILE *fd;

int main()
{

    fd = fopen("WordList.txt", "r");
    if (fd == NULL)
    {
        printf("sorry could not open the file\n");
        exit(0);
    }
    
    set_fd_array(fd);
    // printf("fd_array has been set correctly with the correct line positions\n");
    /*
    fseek(fd, fd_array[29], SEEK_SET);
    char wordy[30];
    fscanf(fd, "%s", wordy);
    printf("%s\n", wordy);
    */

    // printf("hey %d\n", MAX);
    rand_num();
    // printf("just after rand_num()\n");
    /*
    for (int i = 0; i < MAX; i++)
    {
        printf("this is element %d : %d\n", i, random_array[i]);
    }
    */
    // printf("we have printed the random_array it is set correctly\n");


    // char wordy[30];
    //FILE* fdd;
    //fdd = fd_array[0];
    //fscanf(fd_array[0], "%s", wordy);
    //fprintf(fdd, "123");
    //printf("here : %s", wordy);
    //fscanf(fd_array[5], "%s", wordy);
    //printf("here : %s", wordy);
/*
    for (int k = 0; k < 10; k++)
    {
        // fseek(fdd,fd_array[k]);
        fscanf(fdd, "%s", wordy);
        printf("hey %s\n", wordy);
    }
*/
  
    input();

     
    fclose(fd);
    return 0;
}





















void gen_line()
{
    char word[MAX_WORD_LEN];
    int line_no;
    FILE *fd_1;
    // printf("inside gen_line() just before for loop\n");
    // printf("i have no idea what is wrong in this next line of code\n");
    // printf("value of  %d\n", MAX);
    for (int i = 0; i < WORDS_IN_LINE; i++)
    {
        // printf("value of tot_words is %d\n", tot_words);
        line_no = random_array[tot_words];
        // printf("line_no is %d\n", line_no);
        fd_1 = goto_line(line_no);
        // printf("just after assignment of fd by goto_line()\n");
        fscanf(fd_1, "%s", word);
        strcpy(line[i], word);
        tot_words++;
        // printf("this is not allowed\n");

    }

    return;
}






FILE* goto_line(int line_no)
{
    FILE* fdd;
    fdd = fd;
    // printf("hey i am inside goto_line function\n");
    // printf("line_no is %d\n", line_no);
    fseek(fdd, fd_array[line_no], SEEK_SET);
    // printf("inside goto_line() after fseek\n");
    return fdd;
}








void set_fd_array(FILE* fd)
{
    char word[MAX_WORD_LEN];
    int r;
    int position = 0;

    for (int i = 0; i < 1000; i++)
    {   
        fd_array[i] = position;
        fscanf(fd, "%s", word);
        r = strlen(word);
        position += (r + 1);            
    }
   
    return;
}




void input()
{
    printf("GAME RULES : \n");
    sleep(1);
    printf("You will be shown a line on the screen, you have to type the exact line down below\n");
    sleep(4);
    printf("As soon as you have typed the line press enter and you will be shown the next line\n");
    sleep(4);
    printf("You will be given a minute to type as many words as you can\n");
    sleep(4);
    printf("Your score will depend on a mix of the number of words you type and how accurately you type them\n");
    sleep(4);
    printf("GOOD LUCK!!!\n\n\n");
    sleep(1);
    printf("Press ENTER to start the game : ");
    char enter;
    scanf("%c", &enter);
    fflush(stdin);
    // printf("we are inside input() just after scanf statement\n");

    signal(SIGALRM, sig_handler); // Register signal handler
    alarm(60);  // Scheduled alarm after 2 seconds

    // printf("inside input() just before while loop\n");
    
    char user_line[(MAX_WORD_LEN)*(WORDS_IN_LINE) + 1];
    
    
    // strcpy(,"");
    // strcpy(,"");

    while(1)                          // ((stop - start) / CLOCKS_PER_SEC) < 60
    {
        
        
        // printf("inside while loop just before gen_line()\n");
        gen_line();              // generate the line
        // printf("just after gen_line() inside while loop\n");
        printf("GENERATED LINE : ");
        for (int k = 0; k < WORDS_IN_LINE; k++)                   // print the line
        {
            printf("%s ", line[k]);
            strcat(gen_input, line[k]);
            strcat(gen_input, " ");
        }       
        printf("\nTYPE HERE      : ");
        
        fflush(stdin);
        fgets(user_line,((MAX_WORD_LEN)*(WORDS_IN_LINE) + 1), stdin);
        // printf("%s\n", user_line);
        strcat(user_input, user_line);
        
        fflush(stdin);
        sleep(1);

    }

    return;
}

void sig_handler(int signum)
{
    char left_over[(MAX_WORD_LEN)*(WORDS_IN_LINE) + 1];
    char ch;
    
    ungetc('\n', stdin);
    fgets(left_over,(MAX_WORD_LEN)*(WORDS_IN_LINE) + 1 , stdin);
    // printf("\nwhat is happening %s\n", left_over);
    printf("\n\nPress ENTER to get RESULTS!\n");
    char word[20];
    scanf("%s", word);
    // printf("%s", word);

    strcat(user_input, word);

    fgets(left_over,(MAX_WORD_LEN)*(WORDS_IN_LINE) + 1 , stdin);
    // printf("\nwhat is happening %s\n", left_over);

    strcat(user_input, left_over);
    

    signal(SIGALRM,sig_handlers);                     // Register signal handler
    alarm(1);                                         // Scheduled alarm after 2 seconds    

/*
    for (int k = 0; k < 10; k++)
    {
        ch = getchar();
        if (ch == EOF)
        {
            printf("we came here\n");
            break;
        }
        // printf("%d : %c\n", k, ch);
        left_over[k] = ch;
        for (int m = 0; m < 5; m++)
        {
            for (int n = 0; n < 10; n++)
            {

            }
        }
    }
    */
    // printf("\nwhat is happening %s\n", left_over);
    /*
    ungetc('\n', stdin);
    fgets(left_over,(MAX_WORD_LEN)*(WORDS_IN_LINE) + 1 , stdin);
    printf("\nwhat is happening %s\n", left_over);
    // fseek(stdin,-1,SEEK_CUR);
    fgets(left_over,(MAX_WORD_LEN)*(WORDS_IN_LINE) + 1 , (stdin));
    printf("\nwhat is happening %s\n", left_over);
*/
    

    // ungetc('\n', stdin);
/*
    for (int k = 0; k < 1; k++)
    {
        ch = fgets(stdin);
        printf("%c\n", ch);
        // left_over[k] = ch;
    }

    printf("are we passing this point?\n");
*/





    
    
    // printf("\nwhat is happening %s\n", left_over);
/*
    printf("\nSorry your TIME is OVER\n");
    // fclose(fd);
    exit(0);
*/

}


void sig_handlers(int signum)
{

    printf("%s\n", gen_input);
    user_modifier();
    printf("%s\n", user_input);

    printf("\n\nSORRY your TIME is OVER\n\n\n\n");
    

    result();
    fclose(fd);

    char again;
    printf("To play again press Y");
    scanf("%c", &again);
    if (again == 'Y')
    {
        system("cls");
        main();
    }
    exit(0);

}




void rand_num()
{
    int even_odd = rand();
    srand((unsigned)time(NULL));
    int x = 0;
    int a, b;
    a = 0;
    b = 0;
    for (int s = 0; s < OUTER; s++)
    {
        for(int k = 0; k < INNER; k++, even_odd++)
        {
            int i, j;
       
            for (int m = 0; m < 200; m++)
            {
                for (int n = 0; n < 200; n++)
                {
                    // a = b * 10;
                    
                }
            }
            
            i = (((((((rand() % 2417)*63607)%1873)*17851)%9479)*19763)%1000);
            j = ((((((((rand() + i) % 7213)*56113)%1471)*87103)%13723)*14593)%1000);

            if (even_odd % 2 == 0)
            {
                random_array[x] = i;
                x++;
                // printf("%d\t", i);
            }
            else
            {
                random_array[x] = j;
                x++;
                // printf("%d\t", j);
            }
        }
    }
    return;
}




void user_modifier()
{
    int len;
    len = strlen(user_input);
    for (int i = 0; i < len; i++)
    {
        if (user_input[i] == '\n')
        {
            user_input[i] = ' ';
        }
    }
    return;
}



int compare()
{
    tot_user_words();
    int score = 0;
    char user_word[20];
    char gen_word[20];
    int i, j;
    i = 1;
    j = 1;
    
    while (i < (total_user_words + 1))
    {
        strcpy(gen_word, gen_word_ith(i));
        strcpy(user_word, user_word_ith(i));
        if (strcmp(user_word, gen_word) == 0)
        {
            score++;
            keystrokes += strlen(user_word);
        }
        i++;
        j++;

    }
    
    return score;
}




char* gen_word_ith(int i)
{
    int j = 0;
    int k = 1;
    while(1)
    {
        if (gen_input[j] == ' ')
        {
            k++;
        }
        if (k == i)
        {
            int s = 0;
            j++;
            while(gen_input[j + s] != ' ' && gen_input[j + s] != '\0')
            {
                gen_word_i[s] = gen_input[j];
                s++;
            }
            gen_word_i[s] = '\0';
            break;
            
        }
        j++;

    }
    return gen_word_i;

}



char* user_word_ith(int i)
{
    int j = 0;
    int k = 1;
    while(1)
    {
        if (user_input[j] == ' ')
        {
            k++;
        }
        if (k == i)
        {
            int s = 0;
            j++;
            while(user_input[j + s] != ' ' && user_input[j + s] != '\0')
            {
                user_word_i[s] = user_input[j];
                s++;
            }
            user_word_i[s] = '\0';
            break;
            
        }
        j++;

    }
    return user_word_i;

}


void tot_user_words()
{
    int i = 0;
    while (user_input[i] != '\0')
    {
        if (user_input[i] == ' ')
        {
            total_user_words++;

        }
        i++;
    }
    total_user_words++;

    return;
}



void result()
{
    int score;
    score = compare();
    float accuracy;
    accuracy = ((float)(score)) / total_user_words;
    accuracy = accuracy * 100;
    printf("\t\t\t\tRESULTS!!!\n");
    sleep(3);
    printf("Total words typed : %d\n", total_user_words);
    printf("Total words typed correctly : %d\n", score);
    printf("Accuracy : %f\n", accuracy);
    
    keystrokes += total_user_words;
    int wpm;
    wpm = ((float)keystrokes) / 5;
    printf("WPM : %d\n", wpm);
}



/*
FILE* fd;
    fd = stdin;
    char ch;
    int r;
    int i = 0;
    while(1)
    {
        r = fscanf(fd, "%c", &ch);
        if ((r == 0) || (r == EOF))
        {
            break;
        }
        left_over[i] = ch;
        i++;
    }
    left_over[i] = '\n';
*/



/*
for (int k = 0; k < 25; k++)
    {
        ch = fgetc(stdin);
        printf("%c", ch);
    }
*/
