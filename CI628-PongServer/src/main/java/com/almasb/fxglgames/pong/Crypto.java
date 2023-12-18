package com.almasb.fxglgames.pong;



import java.nio.charset.StandardCharsets;

public class Crypto  implements CryptoInterface{

    private int secretKey;

    @Override
    public String encrypt(String data_string) {
        // Convert string to byte array
        byte[] data = data_string.getBytes(StandardCharsets.UTF_8);
        byte[] encoded_data = new byte[data.length];

        for (int i = 0; i < data.length; i++)
        {
            // If number is even then add the key step if off then decrement the key step
            encoded_data[i] = (byte)((i % 2 == 0) ? data[i] + secretKey : data[i] - secretKey);
        }

        // Convert bytes back to string using defined Charset to ensure the correct serialising
        String encoded_data_string = new String(encoded_data, StandardCharsets.UTF_8);

        return encoded_data_string;
    }

    @Override
    public String decrypt(String data_string) {
        byte[] data = data_string.getBytes(StandardCharsets.UTF_8);
        byte[] decoded_data = new byte[data.length];

        for (int i = 0; i < data.length; i++)
        {
            decoded_data[i] = (byte)((i % 2 == 0) ? data[i] - secretKey : data[i] + secretKey);
        }

        String decoded_data_string = new String(decoded_data, StandardCharsets.UTF_8);

        return decoded_data_string;
    }

    @Override
    public void generateKey() {
        secretKey = (int)(Math.random() * 10);
    }

    @Override
    public int getSecretKey() {
        return secretKey;
    }
}
