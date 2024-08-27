# So_long - 42 Project

#### So_long is a game developed in C as part of the 42 curriculum, utilizing the MLX Graphics library. This project adheres to the rigorous norms and requirements set by the school, providing an excellent opportunity to deepen my knowledge of the C programming language. It has been one of the most enjoyable projects I've worked on so far.

![Screenshot from 2024-08-27 00-45-59](https://github.com/user-attachments/assets/87cffe26-f7c4-4824-907e-5723c4d4fb73)

#### Game Overview

#### The game features a simple yet engaging concept. The player must navigate through a map that includes essential elements such as walls, pathways, collectables, a player character, and an exit. The objective is to collect all items and reach the exit without losing all of your life points.
#### Key Features:

#### ▶️ Dynamic Map Reading: The game reads a predefined map that includes walls, pathways, collectables, and an exit.
#### ▶️ Player Movement and Textures: The player moves in different directions using predefined keys, either the arrow keys or WASD. When the player changes direction, their texture changes accordingly, providing visual feedback that reflects the direction they are facing. This adds a layer of polish to the gameplay, making the movement feel more dynamic and responsive.
#### ▶️ Enemies (Bonus Feature): In the bonus version, enemies are introduced. If the player encounters an enemy, they lose 10% of their life. The game ends if the player's life reaches 0. Additional features related to enemies include the ability to define their quantity, the randomness of their movements, their speed, and the duration they must wait before moving again. These customizable settings allow for varied and unpredictable gameplay, adding an extra layer of challenge for the player.
#### ▶️ Custom Textures: The collectables are represented as 5 escudos coins, a nod to the pre-Euro currency. The player character is Buzz Lightyear, and the enemies are represented by Zurg, inspired by my 5-year-old son's love for the character.
#### ▶️ Image Scaling: The game supports 32x32, 48x48, and 64x64 pixel image sizes, offering higher resolution for larger images. To change the game's resolution, simply update a single defined variable, TILE_SIZE, to the desired size. This straightforward adjustment makes it easy to scale the game's graphics according to your preference.
#### ▶️ On-Screen Information: The player can see their movement count, the number of collectables left, and their current life percentage. The player can only exit the game after collecting all items.
#### ▶️ Game Rendering: To prevent flickering during gameplay—caused by key presses, mouse movements, or other actions—double buffer rendering has been implemented. Instead of rendering directly to the screen, the game first renders to a buffer. Once complete, the entire image is then displayed on the screen at once. This technique ensures smooth and flicker-free visuals, enhancing the overall gaming experience.

#### This project has been a fantastic experience, allowing me to blend creativity with technical skills while adhering to the educational standards of 42.
