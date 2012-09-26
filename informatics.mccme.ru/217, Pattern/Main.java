import java.io.*;
import java.util.*;

public class Main {
    private Scanner is;
    private PrintWriter os;

    String a, b;

    int match(int i, int j) {
        if (i >= a.length() || j >= b.length())
            return 0;
        int c1 = a.charAt(i);
        int c2 = b.charAt(j);
        if (c1 == '?' || c2 == '?')
            return 1 + match(i + 1, j + 1);
        if (c1 != '*' && c2 != '*')
            return c1 == c2 ? 1 + match(i + 1, j + 1) : 0;
        if (c1 == '*')
            return
    }

    void solve() {
        a = is.nextLine();
        b = is.nextLine();
        os.println(match(0, 0));
    }

    void run() {
        is = new Scanner(System.in);
        os = new PrintWriter(System.out);
        solve();
        os.close();
    }

    static public void main(String[] args) {
        new Main().run();
    }
}
