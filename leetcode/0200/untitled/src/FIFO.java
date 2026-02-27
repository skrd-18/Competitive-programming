import java.util.LinkedList;
import java.util.Queue;
public class FIFO {
    public void test(String args[]){

        Queue<String> myQueue = new LinkedList<String>();
        myQueue.add("US");
        myQueue.offer("Canada");

        for(String element : myQueue){
            System.out.println("Element : " + element);
        }
    }
}
