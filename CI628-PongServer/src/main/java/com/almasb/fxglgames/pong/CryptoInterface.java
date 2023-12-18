package com.almasb.fxglgames.pong;

public interface CryptoInterface {


    String encrypt(String data_string);

    String decrypt(String data_string);

    void generateKey();

    int getSecretKey();
}
