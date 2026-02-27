public class Main {
    public static void main(String[] args) {
        int[] nums = {3, 2, 1, 0, 4};
        System.out.println(canJump(nums));
    }

    public static boolean canJump(int[] nums) {
        int dis = 0;
        for (int i = 0; i <= dis; i++) {
            dis = Math.max(dis, i + nums[i]);
            if (dis >= nums.length - 1) {
                return true;
            }
        }
        return false;
    }

    public static void canJumpBackwards(int A[], int n) {
        int last = n - 1, i, j;
        for (i = n - 2; i >= 0; i--) {
            if (i + A[i] >= last) last = i;
        }
        if (last <= 0) {
            System.out.println(true);
        } else {
            System.out.println(false);
        }
    }

}