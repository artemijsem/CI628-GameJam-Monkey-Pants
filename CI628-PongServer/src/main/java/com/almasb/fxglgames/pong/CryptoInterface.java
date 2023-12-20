package com.almasb.fxglgames.pong;

public interface CryptoInterface {


    String encryptDecrypt(String data_string);

    void generateKey();

    int getSecretKey();
}
