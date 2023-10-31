/*
 * The MIT License (MIT)
 *
 * FXGL - JavaFX Game Library
 *
 * Copyright (c) 2015-2017 AlmasB (almaslvl@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.almasb.fxglgames.pong;

import com.almasb.fxgl.animation.Interpolators;
import com.almasb.fxgl.app.ApplicationMode;
import com.almasb.fxgl.app.GameApplication;
import com.almasb.fxgl.app.GameSettings;
import com.almasb.fxgl.core.math.FXGLMath;
import com.almasb.fxgl.entity.Entity;
import com.almasb.fxgl.entity.SpawnData;
import com.almasb.fxgl.entity.level.Level;
import com.almasb.fxgl.entity.level.text.TextLevelLoader;
import com.almasb.fxgl.input.UserAction;
import com.almasb.fxgl.net.*;
import com.almasb.fxgl.physics.CollisionHandler;
import com.almasb.fxgl.physics.HitBox;
import com.almasb.fxgl.time.TimerAction;
import com.almasb.fxgl.ui.UI;
import javafx.geometry.Point2D;
import javafx.scene.input.KeyCode;
import javafx.scene.paint.Color;
import javafx.scene.text.Text;
import javafx.util.Duration;
import org.jetbrains.annotations.NotNull;

import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

import static java.util.Map.entry;
import static com.almasb.fxgl.dsl.FXGL.*;
import static com.almasb.fxglgames.pong.NetworkMessages.*;

import java.util.Timer;
import java.util.TimerTask;

/**
 * A simple clone of Pong.
 * Sounds from https://freesound.org/people/NoiseCollector/sounds/4391/ under CC BY 3.0.
 *
 * @author Almas Baimagambetov (AlmasB) (almaslvl@gmail.com)
 */
public class PongApp extends GameApplication implements MessageHandler<String> {

    @Override
    protected void initSettings(GameSettings settings) {
        settings.setTitle("Pong");
        settings.setVersion("1.0");
        settings.setFontUI("pong.ttf");
        settings.setTicksPerSecond(60);
        settings.setApplicationMode(ApplicationMode.DEBUG);
        settings.setDeveloperMenuEnabled(true);
    }

    private Entity player1;
    private Entity player2;
    private Entity ball;
    private BatComponent player1Bat;
    private BatComponent player2Bat;

    public int gameTime = 5;
    public int maxGameTime = 0;

    public TimerAction maxGameTimer;

    // Last 4 inputs will be logged
    public HashMap<String, Integer> firstPlayerKeyMap = new HashMap<String, Integer>() {{
        put("W", 0);
        put("A", 0);
        put("S", 0);
        put("D", 0);
    }};

    public HashMap<String, Integer> secondPlayerKeyMap = new HashMap<String, Integer>() {{
        put("W", 0);
        put("A", 0);
        put("S", 0);
        put("D", 0);
    }};

    HashMap<String, Integer> currentKeyMap = new HashMap<>();

    private Server<String> server;

/*    @Override
    protected void initInput() {
        getInput().addAction(new UserAction("Up1") {
            @Override
            protected void onAction() {
                player1Bat.up();
            }

            @Override
            protected void onActionEnd() {
                player1Bat.stop();
            }
        }, KeyCode.W);

        getInput().addAction(new UserAction("Down1") {
            @Override
            protected void onAction() {
                player1Bat.down();
            }

            @Override
            protected void onActionEnd() {
                player1Bat.stop();
            }
        }, KeyCode.S);

        getInput().addAction(new UserAction("Left1") {
            @Override
            protected void onAction() {
                player1Bat.left();
            }

            @Override
            protected void onActionEnd() {
                player1Bat.stop();
            }
        }, KeyCode.A);

        getInput().addAction(new UserAction("Right1") {
            @Override
            protected void onAction() { player1Bat.right(); }

            @Override
            protected void onActionEnd() {
                player1Bat.stop();
            }
        }, KeyCode.D);

        getInput().addAction(new UserAction("Up2") {
            @Override
            protected void onAction() {
                player2Bat.up();
            }

            @Override
            protected void onActionEnd() {
                player2Bat.stop();
            }
        }, KeyCode.I);

        getInput().addAction(new UserAction("Down2") {
            @Override
            protected void onAction() {
                player2Bat.down();
            }

            @Override
            protected void onActionEnd() {
                player2Bat.stop();
            }
        }, KeyCode.K);

        getInput().addAction(new UserAction("Left2") {
            @Override
            protected void onAction() {
                player2Bat.left();
            }

            @Override
            protected void onActionEnd() {
                player2Bat.stop();
            }
        }, KeyCode.J);

        getInput().addAction(new UserAction("Right2") {
            @Override
            protected void onAction() {
                player2Bat.right();
            }

            @Override
            protected void onActionEnd() {
                player2Bat.stop();
            }
        }, KeyCode.L);
    }*/



    @Override
    protected void initGameVars(Map<String, Object> vars) {
        vars.put("player1score", 0);
        vars.put("player2score", 0);
        vars.put("numOfConnections", 0);
    }

    @Override
    protected void initGame() {
        Writers.INSTANCE.addTCPWriter(String.class, outputStream -> new MessageWriterS(outputStream));
        Readers.INSTANCE.addTCPReader(String.class, in -> new MessageReaderS(in));

        server = getNetService().newTCPServer(55555, new ServerConfig<>(String.class));

        server.setOnConnected(connection -> {
            connection.addMessageHandlerFX(this);
            if (connection.getConnectionNum() == 1) {
                connection.send("SETUP,1," + player1Bat.getEntity().getHeight());
            } else if (connection.getConnectionNum() == 2) {
                connection.send("SETUP,2," + player2Bat.getEntity().getHeight());
            }
            inc("numOfConnections", 1);
            System.out.println((int)player1.getWidth() + "," + (int)player1.getHeight() + "," + (int)player2.getWidth() + "," + (int)player2.getHeight());
        });

//        run()
        eventBuilder().when(() -> geti("numOfConnections") == 1)
                .thenRun(() -> maxGameTimer=run(getMaxGameTimeReached(), Duration.seconds(1)))
                .buildAndStart();


        getGameWorld().addEntityFactory(new PongFactory());
        getGameWorld().addEntityFactory(new LevelFactory());
        Level level = getAssetLoader().loadLevel("level_01.txt", new TextLevelLoader(30, 30,'0'));
        getGameWorld().setLevel(level);
        getGameScene().setBackgroundColor(Color.rgb(0, 0, 5));

        initScreenBounds();
        initGameObjects();

        var t = new Thread(server.startTask()::run);
        t.setDaemon(true);
        t.start();
    }

    @NotNull
    private Runnable getMaxGameTimeReached() {
        return () -> {
            gameTime--;
            System.out.println("Current Game Time: " + gameTime);
            Text gameTimerText = geto("gameTimerText");
            gameTimerText.setText(gameTime + "");

            animationBuilder()
                    .interpolator(Interpolators.ELASTIC.EASE_IN_OUT())
                    .duration(Duration.seconds(0.5))
                    .scale(gameTimerText)
                    .from(new Point2D(1, 1))
                    .to(new Point2D(2, 2))
                    .buildAndPlay();

            animationBuilder()
                    .interpolator(Interpolators.SMOOTH.EASE_IN())
                    .duration(Duration.seconds(0.5))
                    .rotate(gameTimerText)
                    .from(0)
                    .to(360)
                    .buildAndPlay();

            server.broadcast("TIMER, " + gameTime + "");

            if (gameTime <= maxGameTime) {
                System.out.println("Max Game Time Reached");
                server.broadcast("GAME_TIME_OVER");
                maxGameTimer.expire();
            }
        };
    }

    @Override
    protected void initPhysics() {
        getPhysicsWorld().setGravity(0, 0);

        getPhysicsWorld().addCollisionHandler(new CollisionHandler(EntityType.BALL, EntityType.WALL) {
            @Override
            protected void onHitBoxTrigger(Entity a, Entity b, HitBox boxA, HitBox boxB) {
                if (boxB.getName().equals("LEFT")) {
                    inc("player2score", +1);

                    server.broadcast("SCORES," + geti("player1score") + "," + geti("player2score"));

                    server.broadcast(HIT_WALL_LEFT);
                } else if (boxB.getName().equals("RIGHT")) {
                    inc("player1score", +1);

                    server.broadcast("SCORES," + geti("player1score") + "," + geti("player2score"));

                    server.broadcast(HIT_WALL_RIGHT);
                } else if (boxB.getName().equals("TOP")) {
                    server.broadcast(HIT_WALL_UP);
                } else if (boxB.getName().equals("BOT")) {
                    server.broadcast(HIT_WALL_DOWN);
                }


            }
        });

        CollisionHandler ballBatHandler = new CollisionHandler(EntityType.BALL, EntityType.PLAYER_BAT) {
            @Override
            protected void onCollisionBegin(Entity a, Entity bat) {
                playHitAnimation(bat);

                server.broadcast(bat == player1 ? BALL_HIT_BAT1 : BALL_HIT_BAT2);
            }
        };

        CollisionHandler batBatHandler = new CollisionHandler(EntityType.PLAYER_BAT, EntityType.ENEMY_BAT) {
            @Override
            protected void onCollisionBegin(Entity a, Entity b) {
                server.broadcast(BAT1_HIT_BAT2);
            }
        };

        getPhysicsWorld().addCollisionHandler(ballBatHandler);
        getPhysicsWorld().addCollisionHandler(ballBatHandler.copyFor(EntityType.BALL, EntityType.ENEMY_BAT));
        getPhysicsWorld().addCollisionHandler(batBatHandler);
    }

    @Override
    protected void initUI() {
        MainUIController controller = new MainUIController();
        UI ui = getAssetLoader().loadUI("main.fxml", controller);

        controller.getLabelScorePlayer().textProperty().bind(getip("player1score").asString());
        controller.getLabelScoreEnemy().textProperty().bind(getip("player2score").asString());

        getGameScene().addUI(ui);
    }

    @Override
    protected void onUpdate(double tpf) {
        if (!server.getConnections().isEmpty()) {
            var message = "GAME_DATA," + player1.getY() + "," + player1.getX() + "," +
                    player2.getY() + "," + player2.getX();
                        server.broadcast(message);
        }
    }

    private void initScreenBounds() {
        Entity walls = entityBuilder()
                .type(EntityType.WALL)
                .collidable()
                .buildScreenBounds(150);

        getGameWorld().addEntity(walls);
    }

    private void initGameObjects() {

        player1 = spawn("bat", new SpawnData(getAppWidth() / 4, getAppHeight() / 2 - 30).put("isPlayer", true));
        player2 = spawn("bat", new SpawnData(getAppWidth() / 2 - 20, getAppHeight() / 2 - 30).put("isPlayer", false));

        player1Bat = player1.getComponent(BatComponent.class);
        player2Bat = player2.getComponent(BatComponent.class);
    }

    private void playHitAnimation(Entity bat) {
        animationBuilder()
                .autoReverse(true)
                .duration(Duration.seconds(0.5))
                .interpolator(Interpolators.BOUNCE.EASE_OUT())
                .rotate(bat)
                .from(FXGLMath.random(-25, 25))
                .to(0)
                .buildAndPlay();
    }

    @Override
    public void onReceive(Connection<String> connection, String message) {
        var tokens = message.split(",");
        Arrays.stream(tokens).skip(1).forEach(key -> {
            BatComponent playerEntity = null;
            var stopPlayer = key.substring(0, 1).equals(("W")) || key.substring(0,1).equals("S")
                    || key.substring(0,1).equals("A") || key.substring(0,1).equals("D");
            System.out.println(key.startsWith("W"));

            if (connection.getConnectionNum() == 1) {
                playerEntity = player1Bat;
                currentKeyMap = firstPlayerKeyMap;
                System.out.println("CONNECTION 1 DETECTED");
            }
            else if (connection.getConnectionNum() == 2) {
                playerEntity = player2Bat;
                currentKeyMap = secondPlayerKeyMap;
                System.out.println("CONNECTION 2 DETECTED");
            }
            else {
                playerEntity = player1Bat;
            }

            if (key.endsWith("_DOWN")) {
                if (key.substring(0,1).equals("W")) {
                    currentKeyMap.put("W", 1);
                    playerEntity.up();
                    System.out.println("COMMAND TO MOVE UP");
                }
                if (key.substring(0,1).equals("S")) {
                    currentKeyMap.put("S", 1);
                    playerEntity.down();
                    System.out.println("COMMAND TO MOVE DOWN");
                }
                if (key.substring(0,1).equals("A")) {
                    currentKeyMap.put("A", 1);
                    playerEntity.left();
                    System.out.println("COMMAND TO MOVE LEFT");
                }
                if (key.substring(0,1).equals("D")) {
                    currentKeyMap.put("D", 1);
                    playerEntity.right();
                    System.out.println("COMMAND TO MOVE RIGHT");
                }
                //getInput().mockKeyPress(KeyCode.valueOf(key.substring(0, 1)));
            }
            if (key.endsWith("_UP")) {
                currentKeyMap.put(key.substring(0,1), 0);
                System.out.println("Are Keys Up: " + areKeysUp(currentKeyMap));
                if(stopPlayer && !areKeysUp(currentKeyMap)){
                    playerEntity.stop();
                    System.out.println("COMMAND TO STOP");
                }
            }

            if (connection.getConnectionNum() == 1) {
                updateKeyMap(firstPlayerKeyMap, currentKeyMap);
                System.out.println("UPDATED 1 PLAYER KEYMAP");
            }
            else if (connection.getConnectionNum() == 2) {
                playerEntity = player2Bat;
                currentKeyMap = secondPlayerKeyMap;
                System.out.println("UPDATED 2 PLAYER KEYMAP");
            }
            else {playerEntity = player1Bat;}

            if (key.equals("CLOSED"))
            {
                System.out.println("Client Closed");
            }

            System.out.printf("First Player Key Map: " + firstPlayerKeyMap);
        });
    }


    public boolean areKeysUp (HashMap<String, Integer> currentKeyMap)
    {
        var pressedKeyNum = 0;
        for (Integer i : currentKeyMap.values()){
            if(i > 0)
            {
                pressedKeyNum++;
            }

        }
        if(pressedKeyNum > 0)
        {
            return true;
        }
        else {return false;}
    }

    public void updateKeyMap (HashMap<String, Integer> oldMap, HashMap<String,Integer> newMap)
    {
        for (String newKey : newMap.keySet())
        {
            for (String oldKey : oldMap.keySet())
            {
                if(newKey.equals(oldKey))
                {
                    oldMap.put(oldKey, newMap.get(oldKey));
                }
            }
        }
    }

    static class MessageWriterS implements TCPMessageWriter<String> {

        private OutputStream os;
        private PrintWriter out;

        MessageWriterS(OutputStream os) {
            this.os = os;
            out = new PrintWriter(os, true);
        }

        @Override
        public void write(String s) throws Exception {
            out.print(s.toCharArray());
            out.flush();
        }
    }

    static class MessageReaderS implements TCPMessageReader<String> {

        private BlockingQueue<String> messages = new ArrayBlockingQueue<>(50);

        private InputStreamReader in;

        MessageReaderS(InputStream is) {
            in =  new InputStreamReader(is);

            var t = new Thread(() -> {
                try {

                    char[] buf = new char[36];

                    int len;

                    while ((len = in.read(buf)) > 0) {
                        var message = new String(Arrays.copyOf(buf, len));

                        System.out.println("Recv message: " + message);

                        messages.put(message);
                    }

                } catch (Exception e) {
                    e.printStackTrace();
                }
            });

            t.setDaemon(true);
            t.start();
        }

        @Override
        public String read() throws Exception {
            return messages.take();
        }
    }

    public static void main(String[] args) {
        launch(args);
    }
}
