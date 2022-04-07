import java.util.concurrent.ThreadLocalRandom;
import java.util.Queue;

public class Producer extends Thread {

  public Producer(int maxSize, Queue<Integer> sharedBuffer, int waitTimer) {
    this.maxSize = maxSize;
    this.sharedBuffer = sharedBuffer;
    this.waitTimer = waitTimer;
  }

  private int maxSize;
  private int waitTimer;
  private boolean stop;

  public boolean isStop() {
    return stop;
  }

  public void setStop(boolean stop) {
    this.stop = stop;
  }

  public int getWaitTimer() {
    return waitTimer;
  }

  public void setWaitTimer(int waitTimer) {
    this.waitTimer = waitTimer;
  }

  private Queue<Integer> sharedBuffer;

  public void proTest() {
    System.out.println("Producer Test");
  }

  public void run() {
    int number;
    while (!stop) {
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
        System.out.printf("Producing value: %3d\n", number);
        sharedBuffer.add(number);
        sharedBuffer.notify();
      }
      try {
        sleep(waitTimer);
      } catch (InterruptedException e) {
        System.out.println("could not put producer to sleep");
        System.out.println(e);
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
