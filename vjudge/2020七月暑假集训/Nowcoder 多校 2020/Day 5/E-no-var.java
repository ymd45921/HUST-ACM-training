import java.math.BigInteger;
import java.util.*;

public class Main
{
    final static int N = (int)(1e5 + 5);
    final static BigInteger zero = new BigInteger("0");

    public static void main(String[] args)
    {
        int[] p = new int[N];
        boolean[] vis = new boolean[N];
        Scanner sc = new Scanner(System.in);
        BigInteger ans = BigInteger.valueOf(1);
        List<BigInteger> cir = new Vector<>();
        int n = sc.nextInt();

        for (int i = 1; i <= n; ++ i)
            p[i] = sc.nextInt();
        for (int i = 1; i <= n; ++ i)
            if (!vis[i])
            {
                vis[i] = true;
                int cnt = 1, cc = i;
                while (!vis[p[cc]])
                {
                    cc = p[cc];
                    vis[cc] = true;
                    ++ cnt;
                }
                if (cnt > 1) cir.add(BigInteger.valueOf(cnt));
            }
        for (BigInteger ii : cir)
            ans = ans.multiply(ii.divide(ii.gcd(ans)));
        System.out.println(ans.toString());
    }
}
