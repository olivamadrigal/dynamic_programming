#include <stdio.h>
#include "dynamic_programming.h"

int main(int argc, const char * argv[]) {
    
    puts("DYNAMIC PROGRAMMING IS A SYNOMYM FOR TABULATION:\n");
/*
    puts("ROD CUTTING PROBLEM");
    int p[] = {0, 1, 5, 8, 9};
    int n, r_n;
    n = 4;
    printf("NAIVE CUT ROD:\n");
    r_n = cr(p, n);
    printf("r_n=%d\n", r_n);
    printf("DP TOP-DOWN:\n");
    int *r = (int*)calloc(n+1,sizeof(int));
    for(int i = 0; i <= n; i++)
        r[i] = -1;
    r_n = cr_td(p, r, n);
    printf("r_n=%d\n", r[n]);
    printf("DP BOTTOM-UP:\n");
    r_n = cr_bu(p, n);
    printf("r_n=%d\n", r[n]);
    printf("DP BOTTOM-UP:\n");
    cr_bu_with_sol(p,n);
*/

/*
    puts("MATRIX CHAINING PROBLEM");
    //A1(30x35), A2(35x15), A3(15x5), A(5x10)
    int n = 3;
    int p[] = {30,35,15,5};//,10};
    int **m = (int**)calloc(n, sizeof(int*));
    for(int i = 0; i <  n; i++)
        m[i] = (int*)calloc(n, sizeof(int));
    int **s = (int**)calloc(n, sizeof(int*));
    for(int i = 0; i <  n; i++)
        s[i] = (int*)calloc(n, sizeof(int));
    matrix_chain_order_with_sol(p, n, m, s);
 
    printf("\nMATRIX M\n");
    for(int i = 0; i < n; i++)
    {
 
        for(int j = 0; j < n; j++)
        {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    printf("MATRIX S\n");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%d ",s[i][j]);
        }
        printf("\n");
    }
*/
 
 /*
    puts("LEAST COMMON SUBSEQUENCE PROBLEM");
    char *X, *Y;
    int m, n;
    //X = "ABCB";
    //Y = "BDC";
    X =  "ABCBDAB";
    Y = "BDCABA";
    m = 7;//4;
    n = 6;//3;
    int  c[m+1][n+1];//lengths of lcs
    char b[m+1][n+1];//solution matrix
    lcs(X, Y, m, n, c, b);
  
    X = "AB";
    Y = "DAK";
    m = 2;
    n = 3;
   // X = "AB";
   // Y = "BCD";
   // m = 2;//4;
    //n = 3;//3;
    int  d[m+1][n+1];//lengths of lcs
    char f[m+1][n+1];//solution matrix
    int len = lcs_recursive_version(X, Y, m, n);
    printf("\nls len=%d\n", len);
    print_lcs(n, f, X, m, n);
    printf("\n");
*/
    puts("OPTIMAL BST DYNAMIC PROGRAMMING");
    //          0    1    2    3       4    5  (k nodes in sorted order)
    double p[] = {0, 0.15, 0.10, 0.05, 0.10, 0.20};//PROBABILITY p_i that search is for key k_i
    double q[] = {0.05, 0.10, 0.05,  0.05, 0.05, 0.10};//PROBABILITY q_i that search corresponds to q_i
    int n = 5;
    double e[n+2][n+1];// an entry e[i][j] = estmates bst cost with nodes i through j.
    int root[n+1][n+1];
    optimal_bst(p, q, n, e, root);
    
    printf("\nBST OPTIMAL COST BOTTOM UP: e(i,j) = Σ(δ(k_i)+1)p_i + Σ(δ(d_i)+1)q_i  for i=1 to n.\n");
    for(int i = 1; i <= n+1; i++)
    {
        for(int j = 0; j <= n; j++)
            printf("%.2f ", e[i][j]);
        printf("\n");
    }
    printf("\nSOLUTION: e[1,n] = %.2f\n", e[1][n]);
    print_bst_solution(1, 5, 5, root);
    puts("\n");
    
    return 0;
}
