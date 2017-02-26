public int rank(int M, int N, int[][] a, int[] b, int p) {
    // M equations, N variables, modulo p
    int ans = 0;
     
    boolean used[] = new boolean[M];
     
    // Using Gauss-Jordan in [ A : b ] to make it in row-echellon form.
    // So that we can find the rank. We also need to make sure that the
    // rank of [ A ] is equal to the rank of [A : b], else there are
    // no solutions
    for (int j=0; j<N; j++){
        int i = 0;
        while ( (i < M) && (used[i] || (a[i][j] == 0) ) ) {
            i++;
        }
        if(i == M) continue;
        ans++;
        used[i] = true;
        for (int k=0; k<M; k++) if(!used[k]){
            // Find a value of coef equal to (-a[k][j] / a[i][j]);
            // we can just try 0,1,..,p-1 until we find one.
            int coef = 0;
            while ( (a[i][j] * coef + a[k][j]) % p != 0) {
                coef++;
            }
            for (int l=0; l<N; l++) {
                 a[k][l] = (a[k][l] + a[i][l] * coef) % p;
            }
            b[k] = (b[k] + b[i] * coef) % p;
        }
    }
     
    // If rank of [A] is not equal to the rank of [A : b]
    for (int i=0; i<M; i++) {
         if(!used[i] && b[i] != 0) {
              return -1;
         }
    }
          
    return ans;
}
 
final int BITS = 60; //more than enough for 10^15
 
long numberOfExactWays(long[] number, long must)
{
    int n = number.length;
    long res = 0;
    // make the system of equations
    int M = BITS; //one equation per bit
    int N = n   ; // one variable per card
    int[][] A = new int[M][N];
    int[]   b = new int[M];
     
    for (int i=0; i<M; i++) {
        for (int j=0; j<N; j++) {
            if ( (number[j] & (1L << i)) != 0) {
                A[i][j] = 1;
            } else {
                A[i][j] = 0;
            }
        }
        if ( (must & (1L << i)) != 0) {
            b[i] = 1;
        } else {
            b[i] = 0;
        }
    }
    // Find the rank of the system of equations:
    int r = rank(M, N, A, b, 2);
    // Number of free variables is equal to N minus rank.
    return (r == -1) ? 0 : (1L << (N - r) );
}
 
public long numberOfWays(long[] number, long limit)
{
    long res = numberOfExactWays(number, limit); //the equal case
    int n = number.length;
    // Each of the O(BITS) lesser cases:
    for (int i=0; i<BITS; i++) {
        if ( (limit & (1L<<i)) != 0 ) {
            //Truncate the last i bits, set bit #i to 0.
            long l2 = limit >> (i+1) << 1;
            //Truncate the last i bits of each of the cards:
            long[] number2 = new long[n];
            for (int j = 0; j < n; j++) {
                number2[j] = number[j] >> i;
            }
            //Solve the exact case, add the result.
            res += numberOfExactWays(number2, l2);
        }
         
    }
    return res;
}

// https://community.topcoder.com/stat?c=problem_statement&pm=12079&rd=15702