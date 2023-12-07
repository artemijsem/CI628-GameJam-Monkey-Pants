package com.almasb.fxglgames.pong;

import com.almasb.fxgl.entity.Entity;
import com.almasb.fxgl.entity.component.Component;
import com.almasb.fxgl.physics.PhysicsComponent;

public class PowerUpComponent extends Component {

    private PhysicsComponent physics;

    public void givePower(Entity player)
    {
        player.getComponent(PlayerComponent.class).bombRadius++;
    }

}
