import java.math.BigInteger;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
	    var sc = new Scanner(System.in);
	    int T = sc.nextInt();
	    sc.nextLine();
	    for (int i = 1; i <= T; ++ i)
        {
            var line = sc.nextLine();
            var ab = line.split(" ");
            var a = new BigInteger(ab[0], 16);
            var b = new BigInteger(ab[1], 16);
            var aa = a.toString(2);
            var bb = b.toString(2);
            int lim = Math.min(aa.length(), bb.length());
            int cur = 0;
            while (cur < lim &&
                aa.charAt(cur) == bb.charAt(cur))
                ++ cur;
            var prefix = aa.substring(0, cur);
            var c = new BigInteger(prefix, 2);
            System.out.printf("Case #%d: %s\n\n", i, c.toString(16));
        }
    }
}
