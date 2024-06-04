# Cub3d ![boggart](./assets/images/boggart.png)![gnome](./assets/images/gnome.png)![imp](./assets/images/imp.png)![giant](./assets/images/giant.png)![bone](./assets/images/bone_sprite.png)![bone](./assets/images/diamond_sprite.png)

## Developed with [toke5](https://github.com/toke5) 

Cub3d is a Doom-like game that uses raycasting to transform a 2D space into a 3D world. It employs the painter's algorithm to render sprites and items, providing players with various abilities as they navigate through the game.

### Rendering Techniques

- **Billboarding**: All sprites and items use billboarding, which means they always face the player, providing a consistent visual experience.
- **Distance Calculation**: The game calculates the distance of each entity (sprites, items) from the player to determine the rendering order.
- **Sorting / Painters Algotihm**: Entities are sorted based on their distance from the player, ensuring that closer objects are rendered in front of farther ones.

## Features

- **Raycasting Engine**: Converts 2D maps into a 3D first-person perspective.
- **Painter's Algorithm**: Ensures correct rendering order of sprites and items.
- **Billboarding**: All sprites and items are rendered using billboarding, which makes them always face the player.
- **Diverse Items and Guns**: Various items and guns that provide different abilities and weapons to the player.

## Items and Abilities

- **Health Potion**: Restores player's health.![bone](./assets/images/health.png)
- **Poison Potion**: Decreases player's health.![bone](./assets/images/poison.png)
- **Boots**: Increases player's movement speed.![bone](./assets/images/boots.png)
- **Cloak**: Enemies will run away from player.![bone](./assets/images/cloak.png)
- **Bread**: Restores a small amount of health.![bone](./assets/images/bread.png)
- **Book of Wisdom**: Spawns when all enemies (sprites, spawners, bosses) are defeated, signifying the end of the game.![bone](./assets/images/book.png)

## Guns

- **Akimbo Pistols**: Standard firearm with moderate damage and range.
- **Minigun**: High rate of fire, but smaller damage.
- **Raygun**: Deals thankful amount of damage, also ability to destroy walls.
- **Crowbar / Wrench**: If theres way to destroy walls we need something to build them also!


## Gameplay

 **Navigate trough the awesome maps defeating various kinds of enemies. Defeat all enemies to spawn the "Book of Wisdom" and complete the game.**

## Maps

## Installation

1. Clone the repository:
 ```bash
    git clone https://github.com/yourusername/cub3d.git
```

## Here are some of the maps included in the game:

### Hell map with demons to be defeated!
![Map 1](./assets/images/hell_map.png)

### Blue map with blue boggarts!
![Map 2](./assets/images/blue_map.png)

### The first map created with the best sprites boggarts!
![Map 3](./assets/images/boggart_map.png)

## Diamond map with futuristic enemies !
![Map 3](./assets/images/diamond_map.png)

## Bone map with skeletons !
![Map 3](./assets/images/bone_map.png)

### Flesh map with cyclop giants!
![Map 3](./assets/images/flesh_map.png)

