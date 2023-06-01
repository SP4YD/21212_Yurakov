package ru.nsu.yurakov.Torrent.Server;

import ru.nsu.yurakov.Torrent.Handler.Handler;
import ru.nsu.yurakov.Torrent.Message.*;
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
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import static ru.nsu.yurakov.Torrent.Peer.Peer.Status.*;

public class Server {
    public Server () throws IOException {
        Run();
    }

    public  void Run() throws IOException {
        try (ServerSocketChannel serverSocket = ServerSocketChannel.open()) {
            Selector selector = Selector.open();
            serverSocket.bind(new InetSocketAddress("localhost", CONNECTION_PORT));
            serverSocket.configureBlocking(false);
            serverSocket.register(selector, SelectionKey.OP_ACCEPT);

            Peer.Status status = null;
            Message NeedToSend = null;
            Peers = new HashMap<>();

            while (true) {
                selector.select(50);
                Set<SelectionKey> selectedKeys = selector.selectedKeys();
                Iterator<SelectionKey> iterator = selectedKeys.iterator();

                while (iterator.hasNext()) {
                    SelectionKey key = iterator.next();
                    iterator.remove();

                    if (key.isAcceptable()) {
                        SocketChannel client = serverSocket.accept();
                        client.configureBlocking(false);
                        client.register(selector, SelectionKey.OP_READ | SelectionKey.OP_WRITE);

                        status = CONNECTION_IS_ESTABLISHED;
                    } else {
                        SocketChannel channel = (SocketChannel) key.channel();

                        if (key.isReadable()) {
                            switch (status) {
                                case CONNECTION_IS_ESTABLISHED -> {
                                    TorrentFile = HandShake.VerificationServer(channel);
                                    if (TorrentFile != null) {
                                        ParserTorrent parser = new ParserTorrent();
                                        File torrent = new File(PATH_TO_TORRENTS + TorrentFile);
                                        if (!torrent.isFile()) {
                                            throw new RuntimeException();/////////////////////////////////////////////////////////////////////////////
                                        }

                                        INFO = parser.getInfo(PATH_TO_TORRENTS + TorrentFile);
                                        Peer peer = new Peer(channel, INFO);
                                        Peers.put(channel, peer);

                                        status = HANDSHAKE_RECEIVED;
                                    } else {
                                        throw new RuntimeException();/////////////////////////////////////////////////////////////////////////////
                                    }
                                }

                                case SENDING_FILE -> {
                                    Request req = (Request) Message.RecvMessage(channel);
                                    executor.submit(new Handler(req, Peers.get(channel)));
                                    //NeedToSend = Message.HandleMessage(req, Peers.get(channel));
                                }
                            }
                        }

                        if (key.isWritable()) {
                            switch (status) {
                                case HANDSHAKE_RECEIVED -> {
                                    HandShake.Send(channel, INFO);
                                    status = SENT_HANDSHAKE;
                                }

                                case SENT_HANDSHAKE -> {
                                    PiecesManager piecesManager = new PiecesManager(INFO, new File(PATH_TO_FILES + INFO.nameFile));
                                    BitField bitField = new BitField(piecesManager.getWhatHave());
                                    executor.submit(new Sender(bitField, Peers.get(channel)));
                                    //Message.SendMessage(bitField, channel);

                                    status = SENDING_FILE;
                                }

                                case SENDING_FILE -> {
                                    if (NeedToSend != null) {
                                        if (NeedToSend.getType() == 7) {
                                            System.out.println("AAAAAAAAAAAAAAAAA");
                                            Piece piece = (Piece) NeedToSend;
                                            executor.submit(new Sender(piece, Peers.get(channel)));
                                            //Message.SendMessage(piece, channel);
                                            NeedToSend = null;
                                        } else {
                                            throw new RuntimeException();/////////////////////////////////////////////////////////////////////////////
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    private final ExecutorService executor = Executors.newFixedThreadPool(2);
    private final  int CONNECTION_PORT = 3333;
    private final String PATH_TO_TORRENTS = "./TorrentFiles/" ; //"./src/main/resources/TorrentFiles/"
    private final String PATH_TO_FILES = "./Files/"; //"./src/main/resources/DistributedFiles/"
    private String TorrentFile;
    private TorrentInfo INFO;
    private Map<SocketChannel, Peer> Peers;
}

//String ClientIP = socket.getInetAddress().getHostAddress();
