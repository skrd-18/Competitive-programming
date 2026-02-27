// Java code to illustrate addAll()

import java.util.*;

public class Main {
    public static void main(String[] args) {

        int[] nums = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};

        Set<Integer> hash_Set = new HashSet<Integer>();

        // Adding all elements to List
        for (int i = 0; i < nums.length; ++i) {
            hash_Set.add(nums[i]);
        }
        System.out.println(nums.length == hash_Set.size() ? false : true);

    }
}