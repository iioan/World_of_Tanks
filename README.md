# World of Tanks
### Ioan Teodorescu - 333CB

This is a simple yet captivating game where you control a tank on a horizontal plane filled with enemy tanks and buildings. The objective of the game is to destroy as many enemy tanks as possible within a limited time interval (2 minutes). You earn points for each enemy tank destroyed. The game is implemented in C++, using OpenGL interface for rendering 2D and 3D objects.

When the game starts, a random number of enemies are generated. For convenience, at the top, the remaining time and the number of enemies still alive are displayed.
![gameplay](/readmeimgs/gameplay.png "gameplay")

## Gameplay Mechanics

- **Controls**: Use arrow keys or WASD to move the tank and rotate its turret.
- **Objective**: Destroy as many enemy tanks as possible before time runs out.
- **Scoring**: Earn points for each enemy tank destroyed.
- **Projectile**: Fire projectiles from the tank's cannon to destroy enemy tanks and buildings.
- **Tank Health**: Enemy tanks can withstand a minimum of 4 hits before being destroyed.
- **Damage Visuals**: Enemy tanks become increasingly damaged, visually represented by deformations and darkening, as they sustain hits.
- **End of Game**: The game ends when either the time limit is reached or the player's tank is destroyed.

## Advanced Features

- **Turret Rotation**: Rotate the turret to aim at enemies (advanced requirement).
  ![arunca-tureta](/readmeimgs/arunca-tureta.gif "arunca-tureta")
- **Enemy Tank Movement**: Enemy tanks move randomly (advanced requirement).
  ![atac](/readmeimgs/atac.gif "atac")
- **Enemy Tank Attack**: Enemy tanks rotate their turrets towards the player to shoot projectiles.
  ![inamicu-urmareste](/readmeimgs/inamicu-urmareste.gif "inamicu-urmareste")

## End of Game

- **Time Limit Reached**: If the time limit is reached, the game ends, displaying the final score.
  ![won](/readmeimgs/won.png "won")
- **Player Tank Destroyed**: If the player's tank is destroyed, a corresponding message is displayed.
  ![lost](/readmeimgs/lost.png "lost")


To run the project, open the `gtx-framework-master` folder and follow the rules!