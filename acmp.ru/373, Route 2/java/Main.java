import java.io.*;
import java.util.*;
import java.math.BigInteger;

/**
 * @author Alexander Demin (alexande@demin.ws)
 */
public class Main {
    private InputReader is;
    private PrintWriter os;

    private void solve() {
        int N = is.readInt();
        int K = is.readInt();
        int a[][] = is.readIntTable(N, N);
        int dp[][] = new int[N + 2][N + 2];
        dp[1][1] = a[0][0];
        int best = 0;
        for (int k = 2; k <= K; ++k) {
            best = 0;
            for (int i = 1; i <= N; ++i) {
                for (int j = 1; j <= N; ++j) {
                    if (((i + j) & 1) != (k & 1)) {
                        int g = Math.max(Math.max(dp[i - 1][j], dp[i + 1][j]), Math.max(dp[i][j - 1], dp[i][j + 1]));
                        if (g > 0) {
                            dp[i][j] = g + a[i - 1][j - 1];
                            best = Math.max(best, dp[i][j]);
                        }
                    }
                }
            }
        }
        os.println(best);
    }

    private Main() {
    }

    private void run(boolean debug) {
        if (!debug) {
            // is = new InputReader(System.in);
            // os = new PrintWriter(System.out);
            try {
                is = new InputReader(new FileInputStream("INPUT.TXT"));
                os = new PrintWriter(new FileOutputStream("OUTPUT.TXT"));
            } catch (FileNotFoundException e) {
                System.out.println(e.toString());
            }
            solve();
            os.close();
        } else {
            int n = 1;
            while (true) {
                String name = String.format("test-%02d.tst", n);
                n += 1;
                try {
                    BufferedReader inputReader = new BufferedReader(new FileReader(name));
                    System.out.print("Case " + name + "... ");

                    Scanner scanner = new Scanner(inputReader);
                    scanner.useDelimiter("~+\r\n");
                    String input = scanner.next();
                    String expectedOutput = scanner.next();

                    is = new InputReader(new ByteArrayInputStream(input.getBytes()));
                    ByteArrayOutputStream actualOutputStream = new ByteArrayOutputStream();
                    os = new PrintWriter(actualOutputStream);

                    long startTime = System.currentTimeMillis();
                    solve();
                    long duration = System.currentTimeMillis() - startTime;

                    String durationMessage = "";
                    if (duration > 1000)
                        durationMessage = String.format(" (%f sec.)", 1.0 * duration / 1000.0);

                    os.close();

                    String actualOutput = actualOutputStream.toString().replaceAll("\r\n", "\n");
                    boolean okay = expectedOutput.replaceAll("\r\n", "\n").equals(actualOutput);
                    System.out.println((okay ? "OK" : "FAILED!") + durationMessage);

                    if (!okay) {
                       System.out.println("EXPECTED:");
                       System.out.println(expectedOutput);
                       System.out.println("ACTUAL:");
                       System.out.println(actualOutput);
                    }
                } catch (FileNotFoundException e) {
                    break;
                } catch (IOException e) {
                    System.out.println(e.toString());
                }
            }
        }
        exit();
    }

    private void exit() {
        System.exit(0);
    }

    public static void main(String[] args) throws IOException {
        boolean debug = args.length > 0 && args[0].equals("test");
        new Main().run(debug);
    }

    @SuppressWarnings({"UnfieldDeclaration"})
    public static class InputReader {
        private InputStream stream;
        private byte[] buf = new byte[1024];
        private int curChar, numChars;

        public InputReader(InputStream stream) {
            this.stream = stream;
        }

        public int read() {
            if (numChars == -1)
                throw new InputMismatchException();
            if (curChar >= numChars) {
                curChar = 0;
                try {
                    numChars = stream.read(buf);
                } catch (IOException e) {
                    throw new InputMismatchException();
                }
                if (numChars <= 0)
                    return -1;
            }
            return buf[curChar++];
        }

        public int readInt() {
            int c = read();
            while (isSpaceChar(c))
                c = read();
            int sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = read();
            }
            int res = 0;
            do {
                if (c < '0' || c > '9')
                    throw new InputMismatchException();
                res *= 10;
                res += c - '0';
                c = read();
            } while (!isSpaceChar(c));
            return res * sgn;
            }

        public long readLong() {
            int c = read();
            while (isSpaceChar(c))
                c = read();
            int sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = read();
            }
            long res = 0;
            do {
                if (c < '0' || c > '9')
                    throw new InputMismatchException();
                res *= 10;
                res += c - '0';
                c = read();
            } while (!isSpaceChar(c));
            return res * sgn;
        }

        public String readString() {
            int c = read();
            while (isSpaceChar(c))
                c = read();
            StringBuffer res = new StringBuffer();
            do {
                res.appendCodePoint(c);
                c = read();
            } while (!isSpaceChar(c));
            return res.toString();
        }

        private boolean isSpaceChar(int c) {
            return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
        }

        private String readLine0() {
            StringBuffer buf = new StringBuffer();
            int c = read();
            while (c != '\n' && c != -1) {
                if (c != '\r')
                    buf.appendCodePoint(c);
                c = read();
            }
            return buf.toString();
        }

        public String readLine() {
            String s = readLine0();
            while (s.trim().length() == 0)
                s = readLine0();
            return s;
        }

        public String readLine(boolean ignoreEmptyLines) {
            if (ignoreEmptyLines)
                return readLine();
            else
                return readLine0();
        }

        public BigInteger readBigInteger() {
            try {
                return new BigInteger(readString());
            } catch (NumberFormatException e) {
                throw new InputMismatchException();
            }
        }

        public char readCharacter() {
            int c = read();
            while (isSpaceChar(c))
                c = read();
            return (char) c;
        }

        public double readDouble() {
            int c = read();
            while (isSpaceChar(c))
                c = read();
            int sgn = 1;
            if (c == '-') {
                sgn = -1;
                c = read();
            }
            double res = 0;
            while (!isSpaceChar(c) && c != '.') {
                if (c == 'e' || c == 'E')
                    return res * Math.pow(10, readInt());
                if (c < '0' || c > '9')
                    throw new InputMismatchException();
                res *= 10;
                res += c - '0';
                c = read();
            }
            if (c == '.') {
                c = read();
                double m = 1;
                while (!isSpaceChar(c)) {
                    if (c == 'e' || c == 'E')
                        return res * Math.pow(10, readInt());
                    if (c < '0' || c > '9')
                        throw new InputMismatchException();
                    m /= 10;
                    res += (c - '0') * m;
                    c = read();
                }
            }
            return res * sgn;
        }

        public int[] readIntArray(int size) {
            int[] array = new int[size];
            for (int i = 0; i < size; i++)
                array[i] = readInt();
            return array;
        }

        public long[] readLongArray(int size) {
            long[] array = new long[size];
            for (int i = 0; i < size; i++)
                array[i] = readLong();
            return array;
        }

        public double[] readDoubleArray(int size) {
            double[] array = new double[size];
            for (int i = 0; i < size; i++)
                array[i] = readDouble();
            return array;
        }

        public String[] readStringArray(int size) {
            String[] array = new String[size];
            for (int i = 0; i < size; i++)
                array[i] = readString();
            return array;
        }

        public char[][] readTable(int rowCount, int columnCount) {
            char[][] table = new char[rowCount][columnCount];
            for (int i = 0; i < rowCount; i++) {
                for (int j = 0; j < columnCount; j++)
                    table[i][j] = readCharacter();
            }
            return table;
        }

        public int[][] readIntTable(int rowCount, int columnCount) {
            int[][] table = new int[rowCount][columnCount];
            for (int i = 0; i < rowCount; i++) {
                for (int j = 0; j < columnCount; j++)
                    table[i][j] = readInt();
            }
            return table;
        }

        public void readIntArrays(int[]... arrays) {
            for (int i = 0; i < arrays[0].length; i++) {
                for (int j = 0; j < arrays.length; j++)
                    arrays[j][i] = readInt();
            }
        }
    }
}