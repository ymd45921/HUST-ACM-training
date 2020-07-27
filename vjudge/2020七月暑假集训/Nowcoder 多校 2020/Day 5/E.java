/*
 * 确实，并不需要考虑什么取模，根本就不会炸
 * 这波啊，这波考的是睾精度！
 *
 * 你也该熟悉熟悉 Java 算法题的写法了
 * 没想到 Java 竟然自带 gcd 方法，这有点方便
 * 
 * 牛客的 Javac 竟然不支持 var，啊这 ==
 */
import java.math.BigInteger;
import java.util.*;

public class Main
{
    final static int N = (int)(1e5 + 5);
    final static BigInteger zero = new BigInteger("0");

    public static BigInteger gcd(BigInteger a, BigInteger b)
    {
        if (a.compareTo(b) < 0) return gcd(b, a);
        if (b.equals(zero)) return a;
        else return gcd(b, a.mod(b));
    }

    public static void main(String[] args)
    {
        var p = new int[N];
        var vis = new boolean[N];
        var sc = new Scanner(System.in);
        var ans = BigInteger.valueOf(1);
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
        for (var ii : cir)
            ans = ans.multiply(ii.divide(ii.gcd(ans)));
        System.out.println(ans.toString());
    }
}
