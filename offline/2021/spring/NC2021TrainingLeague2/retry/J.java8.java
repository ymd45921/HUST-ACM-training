import java.math.BigInteger;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
	    Scanner sc = new Scanner(System.in);
	    int T = sc.nextInt();
	    sc.nextLine();
	    for (int i = 1; i <= T; ++ i)
        {
            String line = sc.nextLine();
            String[] ab = line.split(" ");
            BigInteger a = new BigInteger(ab[0], 16);
            BigInteger b = new BigInteger(ab[1], 16);
            String aa = a.toString(2);
            String bb = b.toString(2);
            int lim = Math.min(aa.length(), bb.length());
            int cur = 0;
            while (cur < lim &&
                aa.charAt(cur) == bb.charAt(cur))
                ++ cur;
            String prefix = aa.substring(0, cur);
            BigInteger c = new BigInteger(prefix, 2);
            System.out.printf("Case #%d: %s\n\n", i, c.toString(16));
        }
    }
}
