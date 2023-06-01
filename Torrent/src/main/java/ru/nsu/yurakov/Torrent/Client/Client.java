package ru.nsu.yurakov.Torrent.Client;

import ru.nsu.yurakov.Torrent.Handler.Handler;
import ru.nsu.yurakov.Torrent.Message.HandShake;
import ru.nsu.yurakov.Torrent.Message.Message;
import ru.nsu.yurakov.Torrent.Message.Piece;
import ru.nsu.yurakov.Torrent.Message.Request;
import ru.nsu.yurakov.Torrent.ParserTorrent.ParserTorrent;
import ru.nsu.yurakov.Torrent.ParserTorrent.TorrentInfo;
import ru.nsu.yurakov.Torrent.Peer.Peer;
import ru.nsu.yurakov.Torrent.PiecesManager.PiecesManager;
import ru.nsu.yurakov.Torrent.Sender.Sender;

import java.io.File;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;
import java.util.*;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import static ru.nsu.yurakov.Torrent.Peer.Peer.Status.*;

public class Client {
    public Client () throws IOException {
        Run();
    }

    public void Run() throws IOException {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter torrent file name: ");
        TorrentFile = scanner.nextLine();//"IMG.torrent"; //
        Scanner scanIP = new Scanner(new File("./ListIP.txt"));
        ArrayList<InetSocketAddress> ListIP = new ArrayList<>();

        while (scanIP.hasNextLine()) {
            String[] str = scanIP.nextLine().split(":");
            System.out.println("str " + Arrays.toString(str));
            InetSocketAddress address = new InetSocketAddress(str[0], Integer.parseInt(str[1]));
            ListIP.add(address);
        }

        ParserTorrent parser = new ParserTorrent();
        File torrent = new File(PATH_TO_TORRENTS + TorrentFile);
        if (!torrent.isFile()) {
            System.out.println("Client: There is no such file (" + PATH_TO_TORRENTS + TorrentFile + ")");
            return;
        }

        INFO = parser.getInfo(PATH_TO_TORRENTS + TorrentFile);
        Peers = new HashMap<>();
        piecesManager = new PiecesManager(INFO, new File(PATH_TO_FILES + INFO.nameFile));

        Selector selector = Selector.open();

        for (InetSocketAddress address : ListIP) {
            SocketChannel socket = SocketChannel.open();
            socket.configureBlocking(false);
            socket.connect(address);
            socket.register(selector, SelectionKey.OP_CONNECT);
        }

        boolean isFileUploaded = false;

        while (!isFileUploaded) {
            selector.select(150);
            Set<SelectionKey> selectedKeys = selector.selectedKeys();
            Iterator<SelectionKey> iterator = selectedKeys.iterator();

            while (iterator.hasNext()) {
                SelectionKey key = iterator.next();
                iterator.remove();
                SocketChannel channel = (SocketChannel) key.channel();

                if (key.isConnectable()) {
                    if (channel.finishConnect()) {
                        key.interestOps(SelectionKey.OP_READ | SelectionKey.OP_WRITE);
                        Peers.put(channel, new Peer(channel, INFO));
                        Peers.get(channel).status = CONNECTION_IS_ESTABLISHED;
                    }
                } else {
                    Peer peer = Peers.get(channel);

                    if (key.isReadable()) {
                        switch (peer.status) {
                            case SENT_HANDSHAKE -> {
                                if (HandShake.VerificationClient(channel, INFO) == 0) {
                                    peer.status = WAITING_FOR_BITSET;
                                } else {
                                    throw new RuntimeException();/////////////////////////////////////////////////////////////////////////////
                                }
                            }

                            case WAITING_FOR_BITSET -> {
                                Message message = Message.RecvMessage(channel);
                                if (message.getType() == 5) {
                                    //executor.submit(new Handler(message, peer));
                                    Message.HandleMessage(message, Peers.get(channel));

                                    piecesManager.setBitSetChannel(Peers.get(channel).getBitSet());
                                    peer.status = RECEIVING_FILE;
                                } else {
                                    throw new RuntimeException();/////////////////////////////////////////////////////////////////////////////
                                }
                            }

                            case RECEIVING_FILE -> {
                                Message message = Message.RecvMessage(channel);

                                if (message.getType() == 7) {
                                    //System.out.println("AAAAAAAAAAAAAAAAA");
                                    Piece piece = (Piece) message;
                                    if (!piecesManager.getWhatHave().get(piece.getIndex())) {
                                        executor.submit(new Handler(message, peer));
                                        //Message.HandleMessage(message, Peers.get(channel));
                                        piecesManager.setPieceReceived(piece.getIndex());
                                        System.out.println("Загружено: " + (int)(((piece.getIndex() + 1) / (double) piecesManager.getCountPieces()) * 100) + "%");
                                        peer.ReducingCountRequests();
                                    }
                                } else {
                                    throw new RuntimeException();//////////////////////////////////////////////////////////////////////////////
                                }
                            }
                        }
                    }

                    if (key.isWritable()) {
                        switch (peer.status) {
                            case CONNECTION_IS_ESTABLISHED -> {
                                HandShake.Send(channel, INFO);
                                peer.status = SENT_HANDSHAKE;
                            }

                            case RECEIVING_FILE -> {
                                int indexNeedPiece = piecesManager.getIndexPiece();

                                if (indexNeedPiece >= 0) {

                                    if (peer.PossibleMakeRequest()) {
                                        int sizePiece = piecesManager.getSizePiece(indexNeedPiece);
                                        Request request = new Request(indexNeedPiece, 0, sizePiece);

                                        peer.IncreasingCountRequests();
                                        executor.submit(new Sender(request, peer));
                                        //Message.SendMessage(request, channel);
                                    }
                                } else if (piecesManager.isFileUploaded()) {
                                    isFileUploaded = true;
                                    Peers.remove(peer.getChannel());
                                    channel.close();
                                }
                            }
                        }
                    }
                }
            }
        }

        System.out.println("Client: Файл загружен успешно");
        System.out.println("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    }

    private final ExecutorService executor = Executors.newFixedThreadPool(2);
    private final static int CONNECTION_PORT = 1299;
    private final static String SERVER_IP = "localhost"; //the same as 127.0.0.1
    private static final String PATH_TO_TORRENTS = "./TorrentFiles/"; // "./src/main/resources/TorrentFiles/"
    private static final String PATH_TO_FILES = "./Files/"; // "./src/main/resources/UploadedFiles/"
    private static String TorrentFile;
    private static TorrentInfo INFO = null;
    private static PiecesManager piecesManager;
    private static Map<SocketChannel, Peer> Peers;
}