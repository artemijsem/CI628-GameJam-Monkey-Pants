package com.almasb.fxglgames.pong;

import com.almasb.fxgl.entity.Entity;
import com.almasb.fxgl.entity.EntityFactory;
import com.almasb.fxgl.entity.SpawnData;
import com.almasb.fxgl.entity.Spawns;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

import static com.almasb.fxgl.dsl.FXGL.entityBuilder;

public class LevelFactory implements EntityFactory {

    @Spawns("1")
    public Entity newWall(SpawnData data){
        return entityBuilder(data)
                .viewWithBBox(new Rectangle(30,30, Color.WHITE))
                .build();
    }
}
