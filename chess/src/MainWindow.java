import javax.swing.*;
import java.awt.*;
public class MainWindow extends JFrame {
    private JPanel panel1;

    public MainWindow(String x) {
        super(x);
        setContentPane(panel1);
        setVisible(true);
        setSize(640,640);

//        setResizable(false);
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        panel1.setLayout(new GridLayout(8,8));
        //repaint();
        for (int i = 0 ;  i< 8;i++)
            for (int j = 0; j < 8 ;j++)
                panel1.add(new ChessCell(i+j));
    }

//    @Override
//    public void paint(Graphics g) {
//        super.paint(g);
//        for (int j = 0; j < 8; j ++)
//            for (int i = 0; i< 8;i++) {
//                if ((i+j) % 2 == 1)
//                    g.setColor(Color.MAGENTA);
//                else
//                    g.setColor(Color.blue);
//                g.drawRect( i*40, j*40, 80, 80);
//                g.fillRect( i*40, j*40, 80, 80);
//            }
//    }
}
