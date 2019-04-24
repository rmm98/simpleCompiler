#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isDelimiter(char ch)
{
    if(ch == ' ' || ch == ',' || ch == ';' || ch == '\n' || ch == '\0' || ch == '\t' ||
       ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
       ch == '>' || ch == '<' || ch == '=' ||
       ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}')
    {
        return (true);
    }
    return (false);
}

bool isOperator(char ch)
{
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
       ch == '>' || ch == '<' || ch == '=')
    {
        return (true);
    }
    return (false);
}

bool validIdentifier(char* str)
{
    if(str[0] == '0' ||str[0] == '1' ||str[0] == '2' ||
       str[0] == '3' ||str[0] == '4' ||str[0] == '5' ||
       str[0] == '6' ||str[0] == '7' ||str[0] == '8' ||
       str[0] == '9' || isDelimiter(str[0]))
    {
        return (false);
    }
    return (true);
}

bool isKeyword(char* str)
{
    if(!strcmp(str,"auto")||!strcmp(str,"double")||!strcmp(str,"int")||!strcmp(str,"struct")||
       !strcmp(str,"break")||!strcmp(str,"else")||!strcmp(str,"long")||!strcmp(str,"switch")||
       !strcmp(str,"case")||!strcmp(str,"enum")||!strcmp(str,"register")||!strcmp(str,"typedef")||
       !strcmp(str,"char")||!strcmp(str,"extern")||!strcmp(str,"return")||!strcmp(str,"union")||
       !strcmp(str,"continue")||!strcmp(str,"for")||!strcmp(str,"signed")||!strcmp(str,"void")||
       !strcmp(str,"do")||!strcmp(str,"if")||!strcmp(str,"static")||!strcmp(str,"while")||
       !strcmp(str,"default")||!strcmp(str,"goto")||!strcmp(str,"sizeof")||!strcmp(str,"volatile")||
       !strcmp(str,"const")||!strcmp(str,"float")||!strcmp(str,"short")||!strcmp(str,"unsigned"))
    {
        return (true);
    }

    return (false);
}

bool isInteger(char* str)
{
    int len = strlen(str);

    for(int i = 0;i<len;i++)
    {
        if(str[i] != '0' && str[i] != '1' && str[i] != '2' &&
           str[i] != '3' && str[i] != '4' && str[i] != '5' &&
           str[i] != '6' && str[i] != '7' && str[i] != '8' &&
           str[i] != '9' || (str[i] == '-' && i>0))
        {
            return (false);
        }
    }
    return (true);
}

bool isRealNumber(char* str)
{
    bool hasDecimal = false;
    int len = strlen(str);
    for(int i=0;i<len;i++)
    {
        if(str[i] != '0' && str[i] != '1' && str[i] != '2' &&
           str[i] != '3' && str[i] != '4' && str[i] != '5' &&
           str[i] != '6' && str[i] != '7' && str[i] != '8' &&
           str[i] != '9' && str[i] != '.' || (str[i] == '-' && i>0))
        {
            return (false);
        }
        if(str[i] == '.')
            hasDecimal = true;
    }
    return (hasDecimal);
}

char* subString(char* str,int left,int right)
{
    char* subStr = (char*)malloc(sizeof(char)*(right-left+2));
    for(int i=left;i<=right;i++)
        subStr[i-left] = str[i];
    subStr[right-left+1] = '\0';
    return (subStr);
}

void lex_analysis(char* str,FILE* output)
{
    int left = 0, right = 0;
    int len = strlen(str);
    while(right <= len && left <= right)
    {
        if(isDelimiter(str[right]) == false)
            right++;

        if(isDelimiter(str[right]) == true && left == right)
        {
            if(isOperator(str[right]) == true)
            {
                printf("%20c%20c\n",str[right],str[right]);
                fputc(str[right],output);
            }

            if(str[right] == '(' || str[right] == ')' || str[right] == '{' || str[right] == '}' || str[right] == ',' || str[right] == ';')
            {
                printf("%20c%20c\n",str[right],str[right]);
                fputc(str[right],output);
            }

            right++;
            left = right;
        }

        else if(isDelimiter(str[right]) == true && left != right || (right == len && left != right))
        {
            char* subStr = subString(str,left,right-1);

            if(isKeyword(subStr) == true)
            {
                if(!strcmp(subStr,"int") || !strcmp(subStr,"float"))
                {
                    printf("%20s%20s\n","Datatype",subStr);
                    fputc('d',output);
                }

                else
                {
                    printf("%20s%20s\n","Keyword",subStr);
                    fputc('k',output);
                }

            }

            else if(isInteger(subStr) == true)
            {
                printf("%20s%20s\n","Integer",subStr);
                fputc('n',output);
            }


            else if(isRealNumber(subStr) == true)
            {
                printf("%20s%20s\n","RealNumber",subStr);
                fputc('n',output);
            }


            else if(validIdentifier(subStr) == true)
            {
                if(!strcmp(subStr,"main"))
                {
                    printf("%20s%20s\n","Main",subStr);
                    fputc('m',output);
                }

                else
                {
                    printf("%20s%20s\n","Identifier",subStr);
                    fputc('i',output);
                }

            }

            else if(validIdentifier(subStr) == false)
                printf("%s --> Not a valid identifier\n",subStr);

            left = right;
        }
    }
}

int main()
{
    printf("\t\t\tSYMBOL TABLE\n\n%20s%20s\n","Token","Value");
    FILE *input,*output;

    char str[100] ;//= "a >= b;";

    input = fopen("sample_code.c","r");
    output = fopen("tokens.txt","w");

    if(input == NULL)
    {
        printf("File failed to open.");
    }
    else
    {
        while( fgets(str,100,input) != NULL )
        {
            printf("\n");
            lex_analysis(str,output);
        }
        fclose(input);
        fclose(output);
    }
    return (0);
}
