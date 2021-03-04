// package offline.CCPC2017QingHuangDao;

import java.math.*;
import java.util.Scanner;

public class G
{
    public static void main(String[] args)
    {
        var sc = new Scanner(System.in);
        var t = sc.nextInt();
        while (t --> 0)
        {
            var n = sc.nextBigInteger();
            var m = sc.nextBigInteger();
            int bit = -1;
            var tmp = n;
            var ans = BigInteger.ZERO;
            while (tmp.compareTo(BigInteger.ZERO) > 0)
            {
                tmp = tmp.divide(BigInteger.TWO);
                ++ bit;
            }
            for (int k = bit; k >= 0; -- k)
            {
                var xx = BigInteger.TWO.pow(k).subtract(BigInteger.ONE);
                if (xx.multiply(m).compareTo(n) < 0)
                {
                    var zz = n.divide(BigInteger.TWO.pow(k));
                    if (zz.compareTo(m) > 0) zz = m;
                    n = n.subtract(BigInteger.TWO.pow(k).multiply(zz));
                    ans = ans.add(BigInteger.TWO.pow(k));
                }
            }
            System.out.println(ans);
        }
        sc.close();
    }
}