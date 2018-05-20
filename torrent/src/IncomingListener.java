import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Arrays;
import java.util.Properties;

public class IncomingListener implements Runnable {
    @Override
    public void run() {
        try (ServerSocket serverSocket = new ServerSocket(PORT);
             InputStreamReader loadfile = new InputStreamReader(IncomingListener.class.getClassLoader().getResourceAsStream(propertiesFileName),"UTF-8")) {
            pathesToFiles.load(loadfile);
            while(true) {
                System.out.println("waiting for peer");
               var client =  serverSocket.accept();
               try (var is = new BufferedReader(new InputStreamReader(client.getInputStream()));
                    var os = new PrintWriter(new OutputStreamWriter( client.getOutputStream()))) {
                  var request = is.readLine();
                  System.out.println(request);
                  String infos[] = request.split(" ");
                  int pieceLengt = Integer.parseInt(infos[2]);
                  if (pathesToFiles.containsKey(infos[0]) || pathesToFiles.containsKey(infos[0]+infos[1])) {
                      //os.println("shas razdam");
                      String path = pathesToFiles.getProperty(infos[0]);
                      String file = (path + infos[0]);
                      System.out.println(file);
                      RandomAccessFile fileToGive = new RandomAccessFile(file,"r");
                      fileToGive.seek(Long.parseLong(infos[1])*pieceLengt);
                      var fileData = new byte[pieceLengt];
                      fileToGive.read(fileData,0,pieceLengt);
//                      client.getOutputStream().write(fileData);
                      os.write(Arrays.toString(fileData));
                  }
                   else  {
                       os.println("hule tebe nado y menya nichago net");
                       os.flush();
                   }
               }
               catch (Exception exc) {
                   System.out.println("powel naghuy");
                   exc.printStackTrace();
//                   System.exit(0);
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
