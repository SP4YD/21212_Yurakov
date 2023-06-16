package ru.nsu.yurakov.Torrent.ConnecterToChannels;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.SocketChannel;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class ConnecterToChannels {
    public ConnecterToChannels(File fileListIP) throws FileNotFoundException {
        Scanner scanIP = new Scanner(fileListIP);
        ListIP = new ArrayList<>();
        while (scanIP.hasNextLine()) {
            String[] str = scanIP.nextLine().split(":");
            InetSocketAddress address = new InetSocketAddress(str[0], Integer.parseInt(str[1]));
            ListIP.add(address);
        }
        MapConnected = new HashMap<>();
    }

    public void UpdatingConnections(Selector selector) throws IOException {
        for (InetSocketAddress address : ListIP) {
            if (!MapConnected.containsKey(address) || !MapConnected.get(address)) {
                SocketChannel socket = SocketChannel.open();
                socket.configureBlocking(false);
                socket.connect(address);
                socket.register(selector, SelectionKey.OP_CONNECT);
                MapConnected.put(address, true);
            }
        }
    }

    public void DeleteConnection (SocketChannel channel) {
        MapConnected.put((InetSocketAddress) channel.socket().getRemoteSocketAddress(), false);
    }

    private ArrayList<InetSocketAddress> ListIP;
    private HashMap<InetSocketAddress, Boolean> MapConnected;
}
