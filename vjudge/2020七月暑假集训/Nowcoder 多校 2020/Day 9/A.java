import java.math.BigInteger;
import java.util.*;

public class Main
{
    final static int N = (int)(1e5 + 5);
    final static BigInteger two = BigInteger.valueOf(2);
    final static BigInteger zero = BigInteger.valueOf(0);
    static String s;

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

    public static BigInteger process(int st, int ed)
    {
        int cur = st;
        if (ed - st == 1)
        {
            if (s.charAt(st) == '2') return BigInteger.TWO;
            else return BigInteger.ZERO;
        }
        BigInteger ret = BigInteger.ZERO;
        while (cur < ed)
        {
            if (s.charAt(cur) != '2') {++ cur; continue;}
            ++ cur;
            if (cur >= ed) {ret = ret.add(two); break;}
            if (s.charAt(cur) == '+')
            {
                ret = ret.add(two);
                ++ cur;
            }
            else
            {
                int cnt = 0, start = cur + 1;
                while (cnt >= 0)
                {
                    ++ cur;
                    if (s.charAt(cur) == '(') ++ cnt;
                    else if (s.charAt(cur) == ')') -- cnt;
                }
                BigInteger tmp = process(start, cur);
                ret = ret.add(fastPow(two, tmp));
                while (cur < ed && s.charAt(cur) != '2') ++ cur;
            }
        }
        return ret;
    }

    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        s = sc.nextLine();
        BigInteger ans = process(0, s.length());
        System.out.println(ans);
    }
}
