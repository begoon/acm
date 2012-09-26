import java.*;
import java.io.*;
import java.util.Scanner;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws Exception {
        new Main().run();
    }

    void solve() throws Exception {
        int N = nextInt();
        int K = nextInt();
        int[][] m = new int[N][N];
        for (int i = 0; i < N; ++i) {
            String line = reader.readLine();
            for (int j = 0; j < N; ++j) {
                char c = line.charAt(j);
                m[i][j] = c == '0' ? 0 : -1;
            }
        }
        m[0][0] = 1;
        for (int k = 0; k < K; ++k) {
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    if (m[i][j] != -1 && ((i + j) & 1) != (k & 1)) {
                        int v = 0;
                        if (i > 0 && m[i - 1][j] != -1)
                            v += m[i - 1][j];
                        if (i < N - 1 && m[i + 1][j] != -1)
                            v += m[i + 1][j];
                        if (j > 0 && m[i][j - 1] != -1)
                            v += m[i][j - 1];
                        if (j < N - 1 && m[i][j + 1] != -1)
                            v += m[i][j + 1];
                        m[i][j] = v;
                    }
        }

        writer.println(m[N - 1][N - 1]);
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
