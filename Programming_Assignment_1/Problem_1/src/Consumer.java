import java.util.Queue;

public class Consumer extends Thread {

  public Consumer(Queue<Integer> sharedBuffer, int waitTimer) {
    this.sharedBuffer = sharedBuffer;
    this.waitTimer = waitTimer;
    this.stop = false;
  }

  public boolean isStop() {
    return stop;
  }

  public void setStop(boolean stop) {
    this.stop = stop;
  }

  private Queue<Integer> sharedBuffer;
  private int waitTimer;
  private boolean stop;

  public int getWaitTimer() {
    return waitTimer;
  }

  public void setWaitTimer(int waitTimer) {
    this.waitTimer = waitTimer;
  }

  // Consumer Stuff here
  public void consTest() {
    //
    System.out.println("Consumer Test");
  }

  public void run() {
    int number = 0;
    while (!stop) {
      synchronized (sharedBuffer) {
        while (sharedBuffer.isEmpty()) {
          try {
            System.out.printf("\nQueue is Empty\n");
            sharedBuffer.wait();
          } catch (InterruptedException e) {
            e.printStackTrace();
          }
        }
        //
        number = sharedBuffer.remove();
        System.out.printf("Removed   value: %3d\n", number);
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
