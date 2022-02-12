import java.util.Queue;

public class Consumer extends Thread {

  public Consumer(Queue<Integer> sharedBuffer) {
    this.sharedBuffer = sharedBuffer;
  }

  Queue<Integer> sharedBuffer;

  // Consumer Stuff here
  public void consTest() {
    //
    System.out.println("Consumer Test");
  }

  public void run() {
    int number = 0;
    while (true) {
      synchronized (sharedBuffer) {
        while (sharedBuffer.isEmpty()) {
          try {
            System.out.printf("\nQueue is Empty\n");
            sharedBuffer.wait();
          } catch (InterruptedException e) {
            e.printStackTrace();
          }
        }
        number = sharedBuffer.remove();
        System.out.printf("Removed   value: %3d\r", number);
        sharedBuffer.notify();
      }
    }
  }
}
