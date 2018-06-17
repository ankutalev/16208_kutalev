import java.io.*;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.*;

public class IncomingListener implements Runnable {

    @Override
    public void run() {
        try (InputStreamReader loadfile = new InputStreamReader(IncomingListener.class.getClassLoader().getResourceAsStream(propertiesFileName), "UTF-8")) {
            pathesToFiles.load(loadfile);
            Selector selector = Selector.open();
            ServerSocketChannel ssc = ServerSocketChannel.open();
            ssc.bind(new InetSocketAddress("192.168.0.198",PORT));
            ssc.configureBlocking(false);
            int ops = ssc.validOps();
            ssc.register(selector, ops,null);
            int connections;
            ByteBuffer readBuffer = ByteBuffer.allocate(this.ASYNC_BUFF_LENGTH);
            SocketChannel is = null;
            String keyIp = " null";
            while (true) {
                connections = selector.select(10000);
                System.out.println("zdras'te");
                if (connections == 0) {
                    if (heh.position()==messageLen) {
                        System.out.println(new String(heh.array()));
                        System.out.println("krasivo");
                        System.exit(0);
                    }
                    System.out.println(heh.position());
                    System.out.println("waiting for peer");
                    continue;
                }
                Set<SelectionKey> keys = selector.selectedKeys();
                Iterator<SelectionKey> it = keys.iterator();

                while (it.hasNext()) {
                    SelectionKey key = it.next();
                    if (key.isAcceptable()) {
                        SocketChannel socket = ssc.accept();
                        keyIp = socket.getRemoteAddress().toString();
                        peersStatus.put(keyIp,true);
                        socket.configureBlocking(false);
                        socket.register(selector, SelectionKey.OP_READ );
                        System.out.println("got one!");
                    }
//                    if (key.) {
//                        System.out.println("ya ne validny!");
//                        keys.remove(key);
//                    }
                    if (key.isReadable()) {
                            if (peersStatus.get(keyIp)) {
                                is = (SocketChannel) key.channel();
                                System.out.println(is);
                                int len = is.read(readBuffer);
                                System.out.println(len);
                                readBuffer.rewind();
                                messageLen = readBuffer.getInt();
                                System.out.println(messageLen);
                                peersStatus.replace(keyIp, false);
                            }
                            else {
                                if (heh.position()==0) {
                                    System.out.println("KACJAU!");
                                    System.out.println(heh);
                                    heh.flip();
                                    heh.compact();


                                    is.read(heh);

                                    System.out.println(heh.position());
                                    for (int i = 0; i < 20000; i++) {
                                        System.out.println("kachau");
                                    }
                                    System.out.println(heh.position());


                                    System.out.println(heh);
                                    try {
                                        Thread.sleep(20000);
                                    } catch (InterruptedException e) {
                                        e.printStackTrace();
                                    }
                                }
                               else if (heh.position()==messageLen) {
                                    System.out.println(heh);
                                    heh.clear();
                                    System.out.println("YA SKACHAL!");
                                    peersStatus.replace(keyIp,true);
                                }
                                else {
                                    System.out.println("YA EWE NE SKACHAL!");
                                    System.out.println(heh.position());
                                }
                            }
//                        System.out.println(len);
//                        switch (len) {
//                            case 0:
//                                readBuffer.clear();
//                                break;
//                            case -1:
//                                System.out.println("chelik sdoh");
//                                is.close();
//                                break;
//                            default:
//                                for (byte b: readBuffer.array()) {
//                                    tmpBuffer.add(b);
//                                }
////                                System.out.println(new String(readBuffer.array()).trim());
//                                if (len==ASYNC_BUFF_LENGTH) {
//                                    readBuffer.clear();
//                                }
//                                else {
//                                    System.out.println(tmpBuffer);
//                                    tmpBuffer.clear();
//                                    readBuffer.clear();
//                                }
//                        }

//                        byte data[] = new byte[4];
//                        readBuffer.get(data);
//                        System.exit(0);
//                        System.out.println(new String(data));
//                        System.out.println("heh")
                    }
//                    if (key.isWritable()) {
//                        SocketChannel is = (SocketChannel) key.channel();
//                        is.write(ByteBuffer.wrap("sosi huy! like esli bi(d)lo".getBytes()));
//
//                    }
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

    private ByteBuffer heh = ByteBuffer.allocate(50000);
    private final int ASYNC_BUFF_LENGTH = 1024;
    private List<Byte> tmpBuffer = new ArrayList<>();
    private Map<String, ArrayList<Integer>> tableOfAvailability = new HashMap<>();
    private Map <String,Boolean> peersStatus = new HashMap<>();
    private List<Integer> myPieces = new ArrayList<>();
    private int messageLen;
    private final  int PORT = 9875;
    private Properties pathesToFiles = new Properties();
    private final String propertiesFileName = "files.properties";
}
