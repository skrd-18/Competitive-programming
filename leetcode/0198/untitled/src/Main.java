import java.util.Arrays;

public class Main {
    public static void main(String[] args) {
        int[] nums = new int[]{1, 2,3};
        System.out.println(rob(nums));
    }
    /* the order is: prev2, prev1, num  */
    public static int rob(int[] nums) {
        if (nums.length == 0) return 0;
        int prev1 = 0;
        int prev2 = 0;

        for (int num : nums) {
            System.out.printf("num = %d \n", num);
            int tmp = prev1;
            prev1 = Math.max(prev2 + num, prev1);
            prev2 = tmp;
        }
        return prev1;
    }
}