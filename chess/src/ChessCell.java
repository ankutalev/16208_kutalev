import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;

public class ChessCell extends JButton {
    ChessCell (int x) {
        colour = x;
        Image img = null;
        try {
             img = ImageIO.read(getClass().getResource("icons8-pawn-filled-50.png"));
        }
        catch (Exception exc) {}
        setIcon(new ImageIcon(img));
        if (x%2 == 0)
            setBackground(Color.orange);
        else
            setBackground(Color.GRAY);
    }
//    protected void paintComponent(Graphics g) {
//        super.paintComponent(g);
//       if  (colour==1)
//           g.setColor(Color.BLACK);
//       else
//           g.setColor(Color.GRAY);
//       g.fillRect(a,a,a,a);
//    }
    private final int a = 50;
    private int colour;
}
