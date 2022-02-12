import java.util.concurrent.ThreadLocalRandom;
import java.util.Queue;

public class Producer extends Thread {

  public Producer(int maxSize, Queue<Integer> sharedBuffer) {
    this.maxSize = maxSize;
    this.sharedBuffer = sharedBuffer;
  }

  int maxSize;
  Queue<Integer> sharedBuffer;

  public void proTest() {
    System.out.println("Producer Test");
  }

  public void run() {
    int number;
    while (true) {
      synchronized (sharedBuffer) {
        while (sharedBuffer.size() == maxSize) {
          try {
            System.out.printf("\nQueue is full\n");
            sharedBuffer.wait();
          } catch (InterruptedException e) {
            e.printStackTrace();
          }
        }
        number = ThreadLocalRandom.current().nextInt(-99, 99);
        System.out.printf("Producing value: %3d\r", number);
        sharedBuffer.add(number);
        sharedBuffer.notify();
      }
    }

  }
}
/*
 * //Producer
 *
 *
 * public void run(){
 *
 *
 * while(true) {
 *
 *
 * synchronized (sharedBuffer) {
 *
 *
 *
 * while(sharedBuffer.size()== maxSize) {
 *
 * try { System.out.println("Queue is full"); sharedBuffer.wait(); }
 *
 * catch(InterruptedException e) { e.printStackTrace(); } }
 *
 *
 *
 * System.out.println("Producing value " + number); sharedBuffer.add(number);
 * sharedBuffer.notify(); }
 *
 * }
 */
