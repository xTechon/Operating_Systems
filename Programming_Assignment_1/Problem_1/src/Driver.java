import java.util.Queue;
import java.util.LinkedList;

public class Driver {
  public static void main(String[] args) {
    // this is a test

    // int sharedBuffer[] = new int[100];
    Queue<Integer> sharedBuffer = new LinkedList<Integer>();
    int maxSize = 100000;
    Producer chef = new Producer(maxSize, sharedBuffer);
    Producer chef2 = new Producer(maxSize, sharedBuffer);
    Consumer client = new Consumer(sharedBuffer);
    Consumer client2 = new Consumer(sharedBuffer);

    chef.start();
    chef2.start();
    client.start();
    client2.start();
  }
}
