# Abbreviations

- TPS: Tile Per Second
- FOW: Fog of War

# Client / Server Information

## Server

- Game Time
- Entity Position.
- Input From Clients.

## Client

- Players' FOW.
    - FOW will always reveal the same amount of tiles. 
    - Exploring the map and revealing all will make the game never-ending, as both players will always be able to see one another.
- Update Entities / Timer.
- Render Game.

# Players' Information

## Monkey

- Poop: Incremental increase from 0 - 100.
    - 1 per second.
- Speed: 1 TPS
- Task: Catch Magic Pants.
- FOW: 5 Tiles.
- Find Toilet To Reset Poop Level.

## Magic Pants

- Task: Avoid Monkey.
- FOW: 7 Tiles.
- Speed: 0.5 TPS.

# Collectables Information

## Toilets

- Single Use.
- Reset Poop Level.

## Bananas

- Single Use.
- Increase Monkey Speed.

# Map Information

- Map Size: 64x64.
- Top Down, 2D.