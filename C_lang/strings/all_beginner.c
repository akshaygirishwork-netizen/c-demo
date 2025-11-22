#include<stdio.h>
#include<string.h>

void reverse(char*s){
    char t;
    char *p1,*p2;
    p1=s;
    p2=s+strlen(s)-1;

    while(p1<p2){
        t=*p1;
        *p1=*p2;
        *p2=t;
        p1++;
        p2--;
    }
    printf("%s\n",s);
}

void checkpal(char*s){
    char*p1=s;
    char*p2=s+strlen(s)-1;

    while(p1<p2){
        if(*p1 != *p2){
            printf("not pallindrome\n");
            return;
        }
        p1++;
        p2--;
    }
    printf("pallindrome\n");
    
}

void count_all(char *s)
{
    int v=0, c=0, d=0, sp=0;

    while (*s)
    {
        if (*s >= 'a' && *s <= 'z')
        {
            if (*s == 'a' || *s == 'e' || *s == 'i' || *s == 'o' || *s == 'u')
            {
                v++;
            }
            else
            {
                c++;
            }
        }
         if (*s >= '0' && *s <= '9')
            {
                d++;
            }
        if(*s == ' '){
            sp++;
        }
        s++;
    }
    printf("vowels=%d:consonets=%d,digits=%d,spaces=%d",v,c,d,sp);
}

void to_upper(char*p){
    char*s=p;
    while(*s){
        if(*s >= 'a' && *s<='z'){
            *s=*s-32;
        }
        s++;
    }
    printf("%s\n",p);
}

void to_lower(char*p){
    char*s=p;
    while(*s){
        if(*s >= 'A' && *s<='Z'){
            *s=*s+32;
        }
        s++;
    }
    printf("%s\n",p);
}

void remove_spaces(char*s){
    
    for(int i=0;s[i];){
        if(s[i]==' '){
            for(int j=i;s[j];j++){
                s[j]=s[j+1];
            }
        }
        else{
            i++;
        }
    }
    printf("%s\n",s);
}

void remove_duplicate(char*s){

    for(int i=0;s[i];i++){
        for(int j=i+1;s[j];){
            if(s[i]==s[j]){
                for(int k=j;s[k];k++){
                    s[k]=s[k+1];
                }
            }
            else{
                j++;
            }
        }
    }
    printf("%s\n",s);
}

void find_first_nonrepeating(char *s)
{
    int j, flag;
    for (int i = 0; s[i]; i++)
    {
        flag = 0;
        for (j = 0; s[j]; j++)
        {
            if (i != j && s[i] == s[j])
            {
                flag = 1;
                break;
            }
        }

        if (!flag)
        {
            printf("Fist non repeating letter is %c\n", s[i]);
            return;
        }
    }
}

void count_frequency(char*s){
    int flag,count=0;

    for(int i=0;s[i];i++){
        flag=0;
        count=0;
        // Check if s[i] appeared before in the string
        for(int k=0;k<i;k++){
            if(s[k]==s[i]){
                flag=1;
                break;
            }
        }
        // not seen before → count its full frequency
        if (!flag){
            for(int j=i;s[j];j++){
                if(s[i]==s[j]){
                    count++;
                }
            }
            printf("%c found %d times\n",s[i],count);
        }
    }

}

void replace_charector(char*s){
    char c,r;
    printf("enter charector want to replace\n");
    scanf(" %c", &c);
    printf("enter charecet to replace with\n");
    scanf(" %c", &r);

    for(int i=0;s[i];i++){
        if(s[i]==c){
            s[i]=r;
        }
    }
    printf("%s\n",s);
}

void check_substring(char *m)
{

    char s[100];
    int k, j;
    printf("enter a substring to check\n");
    scanf("%s", s);

    for (int i = 0; m[i]; i++)
    {
        if (m[i] == s[0])
        {
            for (j = 1, k = i + 1; s[j]; j++, k++)
            {
                if (s[j] != m[k])
                {
                    break;
                }
            }
            if (s[j] == '\0')
            {
                printf("Substring present\n");
                return;
            }
                }
    }
    printf("Substring not present\n");
}

// void reverse_each_word(char *s)
// {

//     char *p, *q, *temp;
//     char t;
//     int i;
//     p = q = s;

//     for (i = 0; p[i]; i++)
//     {
//         if (p[i] == ' ' )
//         {
//             q = p + i - 1;
//             temp = q+2;

//             while (p < q)
//             {
//                 t = *p;
//                 *p = *q;
//                 *q = t;
//                 p++;
//                 q--;
//             }
//             q = temp;
//             p = q;
//             i=0;
//         }
//     }

//     q=p+i-1;

//     while(p<q){
//         t=*p;
//         *p=*q;
//         *q=t;
//         p++;
//         q--;
//     }

//     printf("%s\n",s);
// }

void reverse_each_word(char *s)
{

    char *start, *end;
    char t;
    start = end = s;

    while (*start)
    {
        while (*start == ' ')
            start++;

        end = start;

        while (*end && *end != ' ')
            end++;

        char *left = start;
        char *right = end - 1;

        while (left < right)
        {
            t = *left;
            *left = *right;
            *right = t;

            left++;
            right--;
        }

        start = end;
    }
    printf("%s\n",s);
}

void large_small_sentance(char *s){
    int count=0;
    int l=0,i=0;
    char large[20];
    char small[20];
    int max_lenth=9999;
    int min_lenth=0;

    char * start,*end;
    start=end=s;

    while(*start){

        while(*start ==' ')
            start++;

        end=start;
        
        count=0;

        while(*end && *end != ' '){
            end++;
            count++;
        }
       
        if(count > min_lenth){
            min_lenth=count;
            i=0;
            char*p = start;
            while(p < end){
                large[i++]=*p++;
            }
            large[i]='\0';
        }

        if (count < max_lenth){
            max_lenth=count;
            i=0;
            char*p = start;

            while(p<end){
                small[i++] = *p++;
            }
            small[i] = '\0';
        }

        start = end;
    }
    printf("large=%s\nsmallest=%s\n",large,small);

}

void main(){
    char s[100];
    

    printf("Enter a string\n");
    scanf("%[^\n]",s);
    // reverse(s);
    // checkpal(s);
    // count_all(s);
    // to_upper(s);
    // to_lower(s);
    // remove_spaces(s);
    // remove_duplicate(s);
    // find_first_nonrepeating(s);
    // count_frequency(s);
    // replace_charector(s);
    // check_substring(s);
    // reverse_each_word(s);
    // large_small_sentance(s);


}