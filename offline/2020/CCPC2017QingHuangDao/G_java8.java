// package offline.CCPC2017QingHuangDao;

import java.math.*;
import java.util.Scanner;

public class G_java8
{
    static final public BigInteger two = BigInteger.valueOf(2);
    static final public BigInteger zero = BigInteger.valueOf(0);
    static final public BigInteger one = BigInteger.valueOf(1);

    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        BigInteger[] pow = new BigInteger[3501];
        pow[0] = one;
        for (int i = 1; i <= 3500; ++ i)
            pow[i] = pow[i - 1].multiply(two);
        while (t --> 0)
        {
            BigInteger n = sc.nextBigInteger();
            BigInteger m = sc.nextBigInteger();
            int bit = -1;
            BigInteger tmp = n;
            BigInteger ans = zero;
            while (tmp.compareTo(zero) > 0)
            {
                tmp = tmp.divide(two);
                ++ bit;
            }
            for (int k = bit; k >= 0; -- k)
            {
                BigInteger xx = pow[k].subtract(one);
                if (xx.multiply(m).compareTo(n) < 0)
                {
                    BigInteger zz = n.divide(pow[k]);
                    if (zz.compareTo(m) > 0) zz = m;
                    n = n.subtract(pow[k].multiply(zz));
                    ans = ans.add(pow[k]);
                }
            }
            System.out.println(ans);
        }
        sc.close();
    }
}
