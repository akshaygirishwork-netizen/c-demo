1.
    #include <stdio.h>
    
    int main()
    {
        int i = 0;
        do
        {
            i++;
            if (i == 2)
                continue;
                printf("In while loop ");
        } while (i < 2);
        printf("%d\n", i);
    }


Important:
continue in a do–while:
Skips the rest of the loop body
Jumps directly to the while (condition) check

Ans: In while loop 2

2.  #include <stdio.h>
    int func()
    {
        return (double)(char)5.0;
    }
cast is from right->left

return type is int5.0 is first cast to char → 5, then cast to double → 5.0, and finally converted to int when returned.
So the function returns 5.


3. #include <stdio.h>
   main()
   {
       if (sizeof(int) > -1)
           printf("True");
       else
           printf("False");
   }

sizeof returns an unsigned value, so sizeof(int) > -1 is always true due to unsigned conversion of -1.

4.    #include <stdio.h>
    int main()
    {
        float f = 0.1;
        if (f == 0.1)
            printf("True");
        else
            printf("False");
    }

Comparison becomes:

(float approximation of 0.1) == (double approximation of 0.1)

Due to precision differences → not exactly equal

So the condition is false.

5.     #include <stdio.h>
    void main()
    {
        int x = 97;
        int y = sizeof(x++);
        printf("x is %d", x);
    }

x is 97
🧠 Key rule (very important)
Expressions inside sizeof are not evaluated (no side effects).

6. 