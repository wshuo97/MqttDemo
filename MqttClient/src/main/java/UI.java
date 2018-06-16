/**
 * Created by Apex_WS on 2018/6/4.
 */

import com.sun.corba.se.impl.orbutil.ObjectUtility;
import org.omg.CORBA.PUBLIC_MEMBER;

import java.awt.Font;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.swing.*;

public class UI extends JFrame {

    private static final long serialVersionUID = -30969714760891598L;
    private JFrame frame; // 主窗口
    private JButton connect; // connect
    private JButton shutdown; // shutdown
    private JTextArea ip; // IP
    private JTextArea port; // PORT
    private JTextArea username;//USERNAME
    private JTextArea passwd;//PASSWD
    private JTextArea topic;//TOPIC
    private JTextArea clientid;//CLIENTID
    private static JTextArea output;//OUTPUT

    private JLabel ipl;
    private JLabel portl;
    private JLabel usernamel;
    private JLabel passwdl;
    private JLabel topicl;
    private JLabel clientidl;
    private JLabel outputl;


    private Client client;

    public UI(Client client) {
        this.client = client;
        initUI();
    }

    public void initUI() {
        frame = new JFrame();
        connect = new JButton("连接");
        shutdown = new JButton("断开");
        ip = new JTextArea();
        port = new JTextArea();
        username = new JTextArea();
        passwd = new JTextArea();
        topic = new JTextArea();
        clientid = new JTextArea();
        output = new JTextArea();

        ipl = new JLabel();
        portl = new JLabel();
        usernamel = new JLabel();
        passwdl = new JLabel();
        topicl = new JLabel();
        clientidl = new JLabel();
        outputl = new JLabel();

        //default
        ip.setText("127.0.0.1");
        port.setText("6789");
        username.setText("usern");
        passwd.setText("passwd");
        topic.setText("mqtt");
        clientid.setText("test");

        // 主窗口
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(800, 420);
        frame.getContentPane().setLayout(null);
        frame.setTitle("MqttClient");
        frame.setLocationRelativeTo(null);
        // JPanel panel = new JPanel();
        // panel.setLayout(new GridLayout());
        // frame.add(panel);

        // 连接
        connect.setBounds(320, 50, 100, 50);
        connect.addActionListener(new listenConnect());
        frame.add(connect);

        // 断开
        shutdown.setBounds(320, 200, 100, 50);
        shutdown.addActionListener(new listenShutdown());
        frame.add(shutdown);

        // ip
        ipl.setText("IP   :");
        ipl.setBounds(10, 10, 70, 50);
        ipl.setFont(new Font("宋体", Font.BOLD, 20));
        frame.add(ipl);

        ip.setFont(new Font(null, Font.BOLD, 17));
        JScrollPane jsp1 = new JScrollPane(ip);
        jsp1.setAutoscrolls(true);
        jsp1.setBounds(80, 10, 200, 50);

        frame.add(jsp1);

        // port
        portl.setText("PORT :");
        portl.setBounds(10, 70, 70, 50);
        portl.setFont(new Font("宋体", Font.BOLD, 20));
        frame.add(portl);

        port.setFont(new Font(null, Font.BOLD, 17));
        JScrollPane jsp2 = new JScrollPane(port);
        jsp2.setAutoscrolls(true);
        jsp2.setBounds(80, 70, 200, 50);
        frame.add(jsp2);

        //username
        usernamel.setText("USER :");
        usernamel.setBounds(10, 130, 70, 50);
        usernamel.setFont(new Font("宋体", Font.BOLD, 20));
        frame.add(usernamel);

        username.setFont(new Font(null, Font.BOLD, 17));
        JScrollPane jsp3 = new JScrollPane(username);
        jsp3.setAutoscrolls(true);
        jsp3.setBounds(80, 130, 200, 50);

        frame.add(jsp3);

        //passwd
        passwdl.setText("PASS :");
        passwdl.setBounds(10, 190, 70, 50);
        passwdl.setFont(new Font("宋体", Font.BOLD, 20));
        frame.add(passwdl);

        passwd.setFont(new Font(null, Font.BOLD, 17));
        JScrollPane jsp4 = new JScrollPane(passwd);
        jsp4.setAutoscrolls(true);
        jsp4.setBounds(80, 190, 200, 50);

        frame.add(jsp4);

        //topic
        topicl.setText("TOPIC:");
        topicl.setBounds(10, 250, 70, 50);
        topicl.setFont(new Font("宋体", Font.BOLD, 20));
        frame.add(topicl);

        topic.setFont(new Font(null, Font.BOLD, 17));
        JScrollPane jsp5 = new JScrollPane(topic);
        jsp5.setAutoscrolls(true);
        jsp5.setBounds(80, 250, 200, 50);

        frame.add(jsp5);

        //clientid
        clientidl.setText("C_ID :");
        clientidl.setBounds(10, 310, 70, 50);
        clientidl.setFont(new Font("宋体", Font.BOLD, 20));
        frame.add(clientidl);

        clientid.setFont(new Font(null, Font.BOLD, 17));
        JScrollPane jsp6 = new JScrollPane(clientid);
        jsp6.setAutoscrolls(true);
        jsp6.setBounds(80, 310, 200, 50);

        frame.add(jsp6);

        //output
        outputl.setText("The Sensor Info");
        outputl.setBounds(550, 330, 280, 50);
        outputl.setFont(new Font("宋体", Font.BOLD, 20));
        frame.add(outputl);

        output.setFont(new Font(null, Font.BOLD, 17));
        JScrollPane jsp7 = new JScrollPane(output);
        jsp7.setAutoscrolls(true);
        jsp7.setBounds(480, 10, 280, 330);

        frame.add(jsp7);

        //System.out.printf("======================================");
        frame.setVisible(true);
    }

    private class listenConnect implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            client.setArgs(ip.getText(), port.getText(), username.getText(), passwd.getText(), topic.getText(), clientid.getText());
            client.start();
        }
    }

    private class listenShutdown implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            client.close();
        }
    }

    public void showInfo(String msg) {
        String[] array=msg.split(":");
        if(array.length<3) return ;
        Date day=new Date();
        SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

        String info=df.format(day)+"\n"+
                    "温度: "+array[0]+"\n"+
                    "湿度: "+array[1]+"\n"+
                    "亮度: "+array[2];
        output.append(info);
        output.setCaretPosition(output.getDocument().getLength());
    }
}
