import java.io.IOException;
import java.io.InputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Properties;

public class IncomingListener implements Runnable {
    @Override
    public void run() {
        try (ServerSocket serverSocket = new ServerSocket(PORT);
             InputStream loadfile = IncomingListener.class.getClassLoader().getResourceAsStream(propertiesFileName)) {
            pathesToFiles.load(loadfile);
            while(true) {
                System.out.println("waiting for peer");
               var client =  serverSocket.accept();
               try (var is = client.getInputStream();
                    var os = client.getOutputStream()) {
                  var data = is.readAllBytes();
                   System.out.println(new String(data));
               }
               catch (Exception exc) {
                   System.out.println("powel naghuy");
                   System.exit(0);
               }


            }
        }
        catch (IOException exc) {
            exc.printStackTrace();
            System.out.println("y tebya chot s sdiom daunom");
            System.exit(0);
        }
    }

    public static void startListening() {
    }
    private final  int PORT = 9875;
    private Properties pathesToFiles = new Properties();
    private final String propertiesFileName = "files.properties";
}
