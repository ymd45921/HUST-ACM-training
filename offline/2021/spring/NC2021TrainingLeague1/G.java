import java.math.BigInteger;
import java.util.*;

class G 
{
    final int N = 365 * 100;
    
    public static void main()
    {
        var sc = new Scanner(System.in);
        int n = sc.nextInt(), sum = 0;
        int[] a = new int[n], cnt = new int[101];
        int[][] 
        for (int i = 0; i < n; ++ i)
        {
            sum += a[i] = sc.nextInt();   
            ++ cnt[a[i]];
        }
        var fact = BigInteger.ONE;
        var ff = new BigInteger[101];
        ff[1] = BigInteger.ONE;
        for (int i = 2; i <= 100; ++ i)
            ff[i] = ff[i - 1].multiply(BigInteger.valueOf(i));
        for (int m = sum; m > 0; -- m)
            fact = fact.multiply(BigInteger.valueOf(m));

        sc.close();
    }
}
