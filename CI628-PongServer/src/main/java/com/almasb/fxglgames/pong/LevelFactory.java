package com.almasb.fxglgames.pong;

import com.almasb.fxgl.entity.Entity;
import com.almasb.fxgl.entity.EntityFactory;
import com.almasb.fxgl.entity.SpawnData;
import com.almasb.fxgl.entity.Spawns;
import com.almasb.fxgl.entity.components.CollidableComponent;
import com.almasb.fxgl.physics.PhysicsComponent;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

import static com.almasb.fxgl.dsl.FXGL.entityBuilder;

public class LevelFactory implements EntityFactory {

    int BLOCK_SIZE = 30;
    @Spawns("1")
    public Entity newWall(SpawnData data){
        return entityBuilder(data)
                .viewWithBBox(new Rectangle(BLOCK_SIZE,BLOCK_SIZE, Color.WHITE))
                .with(new PhysicsComponent())
                .build();
    }


    public int getBLOCK_SIZE() {
        return BLOCK_SIZE;
    }
}
