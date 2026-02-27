import java.util.Arrays;
import java.util.Stack;

public class Main {
    public static void main(String[] args) {
        MyQueue obj = new MyQueue(); // instantiate a MyQueue class object
        obj.push(7);
        obj.push(6);
        obj.push(5);

        System.out.println(obj.pop());
        System.out.println(obj.peek());
        System.out.println(obj.empty());

//        Stack<Integer> s1 = new Stack();
//        for (int i = 0; i < 5; i++) {
//            s1.push(i);
//        }
//        s1.push(12);
//        s1.push(20);
//        System.out.println(s1.pop());
//        System.out.printf("%d \n", s1.peek());
//        System.out.println(Arrays.toString(s1.toArray()));
    }
}


/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue obj = new MyQueue();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.peek();
 * boolean param_4 = obj.empty();
 */