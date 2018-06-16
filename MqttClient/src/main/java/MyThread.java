/**
 * Created by Apex_WS on 2018/6/5.
 */
public class MyThread extends Thread {

    private Client client;
    private UI ui;

    public MyThread(Client client) {
        this.client = client;
        //System.out.println("11111111111111111111111111");
        ui = new UI(client);
    }

    public void run() {
        //System.out.println("9999999999999999999999999");
        final long timeInterval = 2000;
        Runnable runnable = new Runnable() {
            public void run() {
                while (true) {
                    updateInfo();
                    try {
                        Thread.sleep(timeInterval);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        };
        Thread thread = new Thread(runnable);
        thread.start();
    }

    private void updateInfo() {
        if(Constant.info==null) return;
        //System.out.println(Constant.info+" 8888888888888888888888");
        ui.showInfo(Constant.info);
    }
}
