import java.*;
import java.io.*;
import java.math.BigInteger;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws Exception {
        new Main().run();
    }

    void solve() throws Exception {
        int N = nextInt();
        BigInteger[] dp = new BigInteger[N + 1];
        dp[0] = new BigInteger("1");
        for (int i = 1; i <= N; ++i) {
            dp[i] = new BigInteger("0");
            dp[i] = dp[i].add(dp[i - 1]);
            if (i - 2 >= 0)
                dp[i] = dp[i].add(dp[i - 2]);
            if (i - 3 >= 0)
                dp[i] = dp[i].add(dp[i - 3]);
        }
        writer.println(dp[N]);
    }

    StringTokenizer tokenizer;
    BufferedReader reader;
    PrintWriter writer;

    void run() throws Exception {
        reader = new BufferedReader(new InputStreamReader(new FileInputStream("input.txt")));
        writer = new PrintWriter(new FileOutputStream("output.txt"));
        solve();
        writer.close();
    }

    int nextInt() throws Exception {
        return Integer.parseInt(nextToken());
    }

    String nextToken() throws Exception {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            tokenizer = new StringTokenizer(reader.readLine());
        }
        return tokenizer.nextToken();
    }
}
