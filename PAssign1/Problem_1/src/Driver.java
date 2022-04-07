import java.util.Queue;
import java.util.LinkedList;

public class Driver {
    public static void main(String[] args) {
        // int sharedBuffer[] = new int[100];
        Queue<Integer> sharedBuffer = new LinkedList<Integer>();
        int maxSize = 5;
        Producer chef = new Producer(maxSize, sharedBuffer, 250);
        // Producer chef2 = new Producer(maxSize, sharedBuffer);
        Consumer client = new Consumer(sharedBuffer, 1000);
        // Consumer client2 = new Consumer(sharedBuffer);
        boolean exit = false;
        boolean first = false;
        System.out.println("PRODUCER FASTER THAN CONSUMER");
        chef.start();
        client.start();
        while (!exit) {
            synchronized (sharedBuffer) {
                if (sharedBuffer.size() == maxSize) {
                    System.out.println("BUFFER MAX SIZE");
                    System.out.println("CONSUMER FASTER THAN PRODUCER");
                    chef.setWaitTimer(1000);
                    client.setWaitTimer(250);
                    // chef.setStop(true);
                    // client.setStop(true);
                    first = true;
                    exit = true;
                }
                if (sharedBuffer.isEmpty() && first) {
                    chef.setWaitTimer(250);
                    client.setWaitTimer(1000);
                }
            }
        }
    }
}
