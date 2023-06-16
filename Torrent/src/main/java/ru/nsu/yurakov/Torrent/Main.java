package ru.nsu.yurakov.Torrent;

import ru.nsu.yurakov.Torrent.Client.Client;
import ru.nsu.yurakov.Torrent.Server.Server;

import java.io.IOException;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        Thread serv = new Thread(() -> {
            try {
                Server server = new Server(args[0]);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        });

        Thread clie = new Thread(() -> {
            try {
                Client client = new Client();

            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        });

        serv.start();
        Thread.sleep(4000);
        clie.start();
    }
}