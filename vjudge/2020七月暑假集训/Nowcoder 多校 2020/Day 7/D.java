import java.math.BigInteger;
import java.util.*;

public class Main
{
    final static int N = (int)(1e5 + 5);
    final static BigInteger zero = new BigInteger("0");
    final static String yes = "Fake news!";
    final static String no = "Nobody knows it better than me!";
    final static BigInteger one = BigInteger.valueOf(1);
    final static BigInteger two = BigInteger.valueOf(2);
    final static BigInteger six = BigInteger.valueOf(6);

    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        while (t --> 0)
        {
            BigInteger n = sc.nextBigInteger();
            BigInteger sum = n.multiply(n.add(one)).multiply(n.multiply(two).add(one)).divide(six);
            BigInteger sq = sum.sqrt();
            BigInteger sq2 = sq.multiply(sq);
            if (sq2.equals(sum)) System.out.println(yes);
            else System.out.println(no);
        }
    }
}
