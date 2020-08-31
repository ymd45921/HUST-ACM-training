import java.math.BigInteger;
import java.util.*;

public class Main
{
    public static BigInteger fastPow(BigInteger a, BigInteger b)
    {
        BigInteger ans = BigInteger.valueOf(1);
        while (b.signum() > 0)
        {
            if (b.testBit(0)) ans = ans.multiply(a);
            a = a.multiply(a);
            b = b.shiftRight(1);
        }
        return ans;
    }

    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t --> 0)
        {
            int n = sc.nextInt();
            int[] cnt = new int[10];
            while (n --> 0)
            {
                int x = sc.nextInt();
                ++ cnt[x];
            }
            int bi = 0;
            for (int i = 1; i < 10; ++ i)
                if (cnt[i] > 0)
                {
                    -- cnt[i];
                    bi = i;
                    break;
                }
            StringBuilder sb = new StringBuilder();
            for (int i = 1; i < 10; ++ i)
                while (cnt[i] --> 0) sb.append(i);
            while (cnt[0] --> 0) sb.append(0);
            BigInteger ans = new BigInteger(sb.toString());
            ans = ans.multiply(BigInteger.valueOf(bi));
            System.out.println(ans);
        }
    }
}
