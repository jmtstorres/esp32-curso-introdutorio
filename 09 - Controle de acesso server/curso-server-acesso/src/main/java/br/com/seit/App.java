package br.com.seit;

import java.net.InetSocketAddress;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import sun.net.httpserver.HttpServer;

public class App {
    public static void main(String[] args) {
        HttpServer server;
        ExecutorService excutor;
        InetSocketAddress addr = new InetSocketAddress(ipAdd, ipPort);
        server = HttpServer.create(addr, 0);
        server.createContext("/", new RequestHandler());
        excutor = Executors.newCachedThreadPool();
        server.setExecutor(excutor);
        server.start();
    }
}
