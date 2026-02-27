import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        String text1 = new String("abcde");
        String text2 = new String("ace");
        System.out.println(longestCommonSubsequence(text1, text2));
        // test();
    }

    public static int longestCommonSubsequence(String text1, String text2) {
        String s1 = text1;
        String s2 = text2;

        int[][] dp = new int[s1.length() + 1][s2.length() + 1];
        for (int i = 0; i < s1.length(); ++i)
            for (int j = 0; j < s2.length(); ++j)
                if (s1.charAt(i) == s2.charAt(j)) dp[i + 1][j + 1] = 1 + dp[i][j];
                else dp[i + 1][j + 1] = Math.max(dp[i][j + 1], dp[i + 1][j]);

        for (int i = 0; i < s1.length(); ++i) {
            for (int j = 0; j < s2.length(); ++j) {
                System.out.printf("dp[%d][%d] = %d \n", i, j, dp[i][j]);
            }
        }

        return dp[s1.length()][s2.length()];
    }

    public static void test() {
        String text1 = new String("abcde");
        String text2 = new String("ace");
        int[][] dp = new int[text1.length() + 1][text2.length() + 1];
        System.out.printf(Arrays.toString(dp));
    }
}