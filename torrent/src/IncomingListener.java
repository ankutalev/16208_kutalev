import java.io.*;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Arrays;
import java.util.Iterator;
import java.util.Properties;
import java.util.Set;

public class IncomingListener implements Runnable {
    @Override
    public void run() {
        try (InputStreamReader loadfile = new InputStreamReader(IncomingListener.class.getClassLoader().getResourceAsStream(propertiesFileName), "UTF-8")) {


            pathesToFiles.load(loadfile);
            Selector selector = Selector.open();
            ServerSocketChannel ssc = ServerSocketChannel.open();
            ssc.bind(new InetSocketAddress("192.168.0.195",PORT));
            ssc.configureBlocking(false);
            int ops = ssc.validOps();
            ssc.register(selector, ops,null);
            int connections;
            ByteBuffer readBuffer = ByteBuffer.allocate(1);
            while (true) {
                connections = selector.select(3000);
                if (connections == 0) {
                    System.out.println("waiting for peer");
                    continue;
                }
                Set<SelectionKey> keys = selector.selectedKeys();
                Iterator<SelectionKey> it = keys.iterator();
                while (it.hasNext()) {
                    SelectionKey key = it.next();
                    if (key.isAcceptable()) {
                        SocketChannel socket = ssc.accept();
                        socket.configureBlocking(false);
                        socket.register(selector, SelectionKey.OP_READ);
                        System.out.println("got one!");
                    }
//                    if (key.) {
//                        System.out.println("ya ne validny!");
//                        keys.remove(key);
//                    }
                    if (key.isReadable()) {
                        SocketChannel is = (SocketChannel) key.channel();
                        int len = is.read(readBuffer);
//                        System.out.println(len);
                        switch (len) {
                            case 0:
                                readBuffer.clear();
                                break;
                            case -1:
                                System.out.println("chelik sdoh");
                                is.close();
                                break;
                            default:
                                System.out.println(new String(readBuffer.array()).trim());

                        }

//                        byte data[] = new byte[4];
//                        readBuffer.get(data);
//                        System.exit(0);
//                        System.out.println(new String(data));
//                        System.out.println("heh");
                    }
                    it.remove();
                }
//               try (var is = new BufferedReader(new InputStreamReader(client.getInputStream()));
//                    var os = new PrintWriter(new OutputStreamWriter( client.getOutputStream()))) {
//                  var request = is.readLine();
//                  System.out.println(request);
//                  String infos[] = request.split(" ");
//                  int pieceLengt = Integer.parseInt(infos[2]);
//                  if (pathesToFiles.containsKey(infos[0]) || pathesToFiles.containsKey(infos[0]+infos[1])) {
//                      //os.println("shas razdam");
//                      String path = pathesToFiles.getProperty(infos[0]);
//                      String file = (path + infos[0]);
//                      System.out.println(file);
//                      RandomAccessFile fileToGive = new RandomAccessFile(file,"r");
//                      fileToGive.seek(Long.parseLong(infos[1])*pieceLengt);
//                      var fileData = new byte[pieceLengt];
//                      fileToGive.read(fileData,0,pieceLengt);
////                      client.getOutputStream().write(fileData);
//                      os.write(Arrays.toString(fileData));
//                  }
//                   else  {
//                       os.println("hule tebe nado y menya nichago net");
//                       os.flush();
//                   }
//               }
////               catch () {
////                   System.out.println("powel naghuy");
////                   exc.printStackTrace();
////                   System.exit(0);
////               }
//               catch (SocketTimeoutException exc) {
//                   System.out.println("Client umer!");
//               }
//
//
//            }
//        }
//        catch (IOException exc) {
//            exc.printStackTrace();
//            System.out.println("y tebya chot s sdiom daunom");
//            System.exit(0);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    public static void startListening() {
    }
    private final  int PORT = 9875;
    private Properties pathesToFiles = new Properties();
    private final String propertiesFileName = "files.properties";
}
