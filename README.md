# Blasteroids-A-Space-Survival-Game
<p align= "justify">In this project, we have developed <strong>BLASTEROIDS</strong> which is a single player space survival game. The objective of the game is to defend the spaceship (player) from incoming burning Asteroids. Initially, the player is given maximum health of 100 HP. Health can be regained by collecting the First-Aid kits. The spaceship can be defended either by destroying the asteroids by LASER attack or by dodging them. Points are given depending upon the size of the asteroid destroyed.</p>

<p align="center">
  <img src="https://user-images.githubusercontent.com/42888030/146944870-e2a82516-b4bd-4429-88ba-767a41017936.png" alt="Blasteriods: A Space Survival Game">
</p>

<p align= "justify">In this project, we have used GUI concept of OOPs. For this purpose, we have used SFML library of C++. The project is implemented on CodeBlocks IDE. The project contains some Header files and some CPP files. Header files are used to define classes of various types required and CPP files are used to define the methods for the corresponding Header files. Header files used in the project are:</p>

* **Game.h** : Contains attributes related to overall working of game.
* **Player.h** : Contains attributes related to spaceship such as position.
* **Enemy.h** : Contains attributes related to the asteroids such as size.
* **Bullet.h** : Contains attributes related to bullet such as bullet speed.
* **Health.h** : Contains attributes related to the health such as damage.

The game contains the following features:
1. **Window Size**: The game is played in full screen mode at a resolution of 1920 x 1080 with uncapped frame rate. The background image is loaded as a texture.
2. **Spaceship (player)**: The texture for spaceship is loaded as an image from Textures folder. The speed of the spaceship is controlled using movement speed parameter.
3. **Asteroids (enemy)**: The size of the asteroids is generated randomly and varies between 3 - 10. The size determines the damage caused to spaceship on collision as well as the points gained by the player for destroying it. The asteroids spawn depending upon the spawn rate.
4. **First-Aid Kits**: The player regains health by collecting them. They spawn depending upon the spawn rate which is comparatively less. Each first-aid kit increases the health by 4 HP.
5. **Bullets**: Image is loaded as a texture from the Textures folder. The speed of the bullet is controlled using the movement speed parameter. It contains a cool down parameter which controls the fire rate.
6. **Health Bar and Points**: In the top left corner, Health Bar is displayed along with Health percentage which changes dynamically as Health of the spaceship changes. Points are displayed in the top right corner.
7. **Restart Menu**: At the end of the game, the player is given a choice whether to play again or not.
8. **Sound**: The collision between any two objects is marked with a collision sound effect. The sound effect is loaded using sound buffer from audio folder. Similarly, firing of a bullet creates laser sound effect.

<p align="center">
  <img src="https://user-images.githubusercontent.com/42888030/146944988-3968b17c-0ea8-46b4-94e6-693bde5c6580.png" alt="Game Features">
</p>

<p align="center">
  <img src="https://user-images.githubusercontent.com/42888030/146945004-450e1481-dc73-43aa-b908-d60f5f65a453.png" alt="Restart UI">
</p>
