#ifndef dynamic_programming_h
#define dynamic_programming_h
#include "stdlib.h"
#include "limits.h"
#include "bst.h" //see data structures repository

void print_partitions(int **s, int i, int j);
void print_lcs(int n, char b[][n+1], char *x, int i, int j);

//DP PROBLEM: ROD CUTTING PROBLEM

//NAIVE METHOD WITH O(2^n) exponential complexity
//2^(n-1) possibilities to consider for rod of length n.
//r_n = max(p_i + r_n_i) for i in [1, n]
int cr(int *p, int n)
{
    int q;
    if(n == 0)
        return 0;
    q = INT_MIN;
    for(int i = 1; i <= n; i++)
        q = q > p[i] + cr(p, n - i)? q: p[i] + cr(p, n - i);
    return q;
}

//DYNAMIC PROGRAMMING TOP-DOWN IMPLEMENTATION O(n^2)
int cr_td(int *p, int *r, int n)
{
    int q, sp;
   //out lookup table in O(1)
    if(r[n] >= 0)
        return r[n];
    
    if(n == 0)
        q = 0;
    else
        q = INT_MIN;
    for(int i = 1; i <= n; i++)
    {
        sp = p[i] + cr_td(p, r, n - i);
        q = q > sp? q: sp;
    }
    r[n] = q;
    return q;
}

//DYNAMIC PROGRAMMING BOTTOM-UP IMPLEMENTATION IN O(n^2)
int cr_bu(int *p, int n)
{
    int q, sp;
    int r[n+1];
    r[0] = 0;
    for(int j = 1; j <= n; j++)
    {
        q = INT_MIN;
        for(int i = 1; i <= j; i++)
        {
            sp = p[i] + r[j-i];
            q = q > sp? q:sp;
        }
        r[j] = q;
    }
    return r[n];
}

//DYNAMIC PROGRAMMING SOLUTION WITH ACTUAL SOLUTION ("path") that
//leads to an optimal value
int cr_bu_sol(int *p, int *s, int n)
{
    int sp, q;
    int r[n+1];
    
    r[0] = 0;
    for(int j = 1; j <= n; j++)
    {
        q = INT_MIN;
        for(int i = 1; i <= j; i++)
        {
            sp = p[i] + r[j-i];
            if(q < sp)
            {
                q = sp;
                s[j] = i;//saves piece length of subproblem j which gives max r_n
            }
        }
     r[j] = q;
    }
    return q;
}

void cr_bu_with_sol(int *p, int n)
{
    
    int r_n, s[n-1];
    r_n = cr_bu_sol(p,s,n);
    
    printf("r_n = %d\n", r_n);
    printf("comprised of optimal revenues for pieces of length: ");
    while(n > 0)
    {
        printf("%d, ", s[n]);
        n = s[n] - n;
    }
    printf("\n");
}


/** DYNAMIC SOLUTION TO MATRIX CHAINING PROBLEM */
void matrix_chain_order_with_sol(int *p, int n, int **m, int **s)
{
    int j, q;
    
    for(int chain_length = 1; chain_length < n; chain_length++) //minimum chain length = 2: example indecis A_0*A_1
    {
        for(int i = 0; i < (((n - 1) - chain_length) + 1); i++) //i runs from 1 up to j-1
        {
            j = i + chain_length;
            m[i][j] = INT_MAX;
            for(int k = i; k <= j - 1; k++)//EXPLORE ALL POSSIBLE PARTITIONS
            {
                q = m[i][k] + m[k+1][j] + (p[i]*p[k+1]*p[j+1]);
                if(q < m[i][j])
                {
                   // printf("%d,%d: %d\n", i, j, k);
                    m[i][j] = q;//stores minimum number of scalar multiuplicatons
                    s[i][j] = k;//gets updated whenever a parenthesization yields a smaller value.
                }
            
            }
            
        }
    }
    printf("MIN NUMBER OF SCALAR MULTIPLICATIONS TO MULTIPLY MATRICES A0A1A2: %d.\n", m[0][2]);
    printf("USING THIS PARENTHESIZATION: \n");
    print_partitions(s,0,n-1);

}

/* PRINT PARENTHESIZATION WHICH YIELDS MINIMUM NUMBER OF SCALAR MULTIPLICATIONS */
void print_partitions(int **s, int i, int j)
{
    if(i == j)
    {
        printf("A%d", i);
        return;
    }
    else
    {
        printf("(");
        print_partitions(s, i, s[i][j]);
        print_partitions(s, s[i][j] + 1, j);
        printf(")");
        return;
    }
}

/* DYNAMIC PROGRAMMING SOLUTION TO LONGEST COMMONON SUBSEQUENCE PROBLEM */
//void lcs(char *x, char *y, int m, int n, int **c, char b[][n])
void lcs(char *x, char *y, int m, int n, int c[][n+1], char b[][n+1])
{
    //initialize col 0 and row 0
    for(int j = 0; j <= n; j++)
        c[0][j] = 0;
    for(int i = 1; i <= m; i++)
        c[i][0] = 0;

    //process for x_i increasing y_j
    for(int i = 1; i <= m; i++)//1, 2, 3, 4: 0, 1, 2, 3
    {
        for(int j = 1; j <= n; j++)//1, 2, 3: 0, 1, 2
        {
            printf("x_i %c =? y_i %c\n", x[i-1], y[j-1]);
            if(x[i-1] == y[j-1])
            {
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = 'd';//diagonal look to cell in direction of upper left corner
                printf("c[%d][%d] = c[%d][%d] + 1 = %d\n", i, j, i-1, j-1, c[i-1][j-1] + 1);
                printf("b[%d][%d] = %c\n",i,j, b[i][j]);

            }
            else if(c[i-1][j] >= c[i][j-1])
            {
                c[i][j] = c[i-1][j];
                b[i][j] = 'u';//look to cell up
                printf("c[%d][%d] = c[%d][%d] = %d\n", i, j, i-1, j, c[i-1][j]);
                printf("b[%d][%d] = %c\n",i,j, b[i][j]);
            }
            else
            {
                c[i][j] = c[i][j-1];
                b[i][j] = 'l';//look to cell on left
                printf("c[%d][%d] = c[%d][%d] = %d\n", i, j, i, j-1, c[i][j-1]);
                printf("b[%d][%d] = %c\n",i,j, b[i][j]);
            }
        }
    }
    
    for(int j =0; j <=n; j++)
        printf("(%d) ", c[0][j]);
    printf("\n");
    for(int i=1; i <= m; i++)
    {
        printf("(%d) ", c[i][0]);
        for(int j=1; j <=n; j++)
            printf("(%d:%c) ", c[i][j], b[i][j]);
        printf("\n");
    }
    
    print_lcs(n, b, x, m, n);
    printf("\n");

}


void print_lcs(int n, char b[][n+1], char *x, int i, int j)
{
    if(i == 0 || j == 0)
        return;
    
    if(b[i][j] == 'd')
    {
        print_lcs(n, b, x, i-1, j-1);
        printf("%c", x[i-1]);
        return;
    }
    else if(b[i][j] == 'u')
        return print_lcs(n, b, x, i-1, j);
    else
        return print_lcs(n, b, x, i, j-1);
}


//AB
//BCD
int lcs_recursive_version(char *x, char *y, int i, int j)
{
    int sum;
    if(i== 0 || j == 0)
    {
        printf("%d %d\n", i, j);
        sum =  0;
    }
    else if(x[i-1] == y[j-1])
    {
        printf("%d %d %c\n", i, j, x[i-1]);
        sum = lcs_recursive_version(x, y, i-1, j-1) + 1;
    }
    else
    {
        printf("%d %d\n", i-1, j);
        int up = lcs_recursive_version(x, y, i-1, j);
        printf("%d %d\n", i, j-1);
        int left = lcs_recursive_version(x, y, i, j-1);
        sum =  up >= left ? up: left;
    }
    return sum;
}

void optimal_bst(double *p, double *q, int n, double e[][n+1], int root[][n+1])
{
    double w[n+2][n+1];
    int j;
    double t;
    for(int i = 1; i <= n+1; i++)
    {
            e[i][i-1] = q[i-1];
            w[i][i-1] = q[i-1];
    }
    
    //bottom up.
    for(int l = 1; l <= n; l++)//possible lengths: 1 node, 2 nodes, 3 nodes, ... up to n nodes.
    {
        for(int i = 1; i <= n - l + 1; i++)
        {
            j = i + l - 1;
            e[i][j] = INT_MAX;
            w[i][j] = w[i][j-1] + p[j] + q[j];
            for(int r = i; r <= j; r++)
            {
                t = e[i][r-1] + e[r+1][j] + w[i][j];
                if(t < e[i][j])
                {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            
            }
            
        }
    
    }

    printf("PROBABLITY MATRIX: w(i,j) = Σp_k + Σq_k for k= i to j\n");
    for(int i = 1; i <= n+1; i++)
    {
        for(int j = 0; j <= n; j++)
        {
            printf("%.2f ", w[i][j]);
        }
        printf("\n");
    }
    printf("\nSOLUTION ROOT MATRIX: K_r \n");
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            printf("%d ", root[i][j]);
        }
        printf("\n");
    }
 }


// k_r      LS:1....K_r-1       RS:k_r+1....n
 void print_bst_solution(int i, int j, int n, int root[n+1][n+1])
{
    int k_r;
    if(i > n) //if j == 0 || j > n, return
        return;
    if(j - i >= 0)
    {
        k_r =  root[i][j];
        
        printf("root %d \n", k_r);
    }
    else
        return;
    printf("left:");
    print_bst_solution(i, k_r - 1, n, root);//left
    printf("right:");
    print_bst_solution(k_r + 1, j, n, root);//right

}
#endif /* dynamic_programming_h */

