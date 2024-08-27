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

# So_long - Functions explained

#### ▶️ 1) First, the main function checks whether the argc is equal to two (program + map file).

#### ▶️ 2) It initializes the function that contains the game structure variables (init_game_struct_variables).

#### ▶️ 3) The file descriptor (map) is read and checked.

#### ▶️ 4) The map_read function (located in support_functions.c) is called, which uses the get_next_line function. This function defines the line_count (row number) variable and the max_line_length (length of each row) variable within a loop.

#### ▶️ 5) The map_mem_allocate function (in support_functions.c) is executed, called by start_map_mem_allocate (in so_long.c). Since we already know the number of rows and columns in the map, memory for the map can be allocated.

#### ▶️ 6) Next, the main function calls the add_print_lines function (support_functions.c). This function uses get_next_line to read all the map lines. Each map row index is filled with the content of each line read by get_next_line. At the end, it prints out the content of each row (this part is not required by the project).

#### ▶️ 7) In the main function, the bonus "enemy" variables are initialized in the init_handle_enemy_vars function (handle_enemy_funcs.c).

#### ▶ First, it calls the check_map_dimensions function (handle_enemy_funcs.c), which checks if the map has the minimum rows and columns to handle "enemies." Some game structure variables are initialized or assigned (min_rows, min_columns, game->enemies, game->num_enemies, and game->lives). The necessary memory for enemies (t_enemy structure) is allocated.
#### ▶ The enemies are then initialized by looping through the enemies array. Each enemy position starts at (x:1, y:1), and an inner loop checks if the enemy is being placed on a position different from '0' (road). If it's not on the road, it keeps trying until it finds a valid position. The x and y positions of the enemy are defined by adding a random number to the max_line_length and line_count, subtracting 2 (to account for the map's wall boundaries). Once an enemy's starting position is defined, this value is assigned to the enemy's position. Additionally, a speed variable is assigned, determining the number of tiles an enemy moves in each movement (making it faster or slower). Each enemy's movement direction is determined by the rand function % 4 (one for each direction). The last variable, life, starts at 100.

#### ▶️ 8) Next, the main function calls the start_validations function (so_long.c), which in turn calls the validate_map function. If the map is valid, start_validations calls validate_reachability (check_reachability.c).

#### ➡️ 8a) validate_map (map_validator.c): This function checks if the map is a rectangle (check_rectangle), if it contains only valid characters (check_full_fill), if it has the required number of elements (check_map_element), and if the walls are closed off.

#### ➡️ 8b) validate_reachability (check_reachability.c): This function checks whether all items and exits are reachable and if the player is not blocked. It declares a variable f from the t_flood_fill_vars structure, which holds pointers to the map, its row and column sizes, and a visited grid. The init_visited function allocates memory for a 2D array at f->visited and sets all its values to 0, indicating that the positions haven't been visited yet.
#### ➡ The player's starting position is defined by the define_player_position function, with its coordinates stored in the game->player_x and game->player_y variables.
#### ➡ With the player's position set and the vars->visited array initialized, the flood_fill function searches the map to determine if every position can be reached by the player. It checks if the x and y coordinates are out of bounds, if the map content at each coordinate is '1' (wall), or if the position has already been visited. If any of these conditions are true, the function returns without further recursion and moves on to the next position. The recursive calls continue until no more positions can be explored.
#### ➡ The function then checks if the player's position is still 0. If so, it indicates that the player ('P') is either surrounded by walls, preventing any movement, or that a move was made in one direction, but it was impossible to return to the original position, marking it as 1.
#### ➡ Finally, check_c_e_reachability checks if all collectibles and exits are reachable by the player ('P'). It inspects the map coordinates to see if each was visited (i.e., if it is 1 or still 0).
#### ➡ An external function, free_flood_mem (free_mem_reachability.c), frees the memory allocated for f->visited. If the flag is 0 (indicating 'P', 'C', and 'E' are reachable), the memory is freed. If any elements are unreachable, the program exits, but before doing so, it frees the memory allocated for f->visited, game->map, and the enemy_array by calling this function with flag = 1.

#### ▶️ 9) The last function called in main is start_mlx_functions (so_long.c), which invokes several other functions:

#### ➡️ 9a) init_game_player_images function (mlx_and_player_images_init_load_clean.c) - First, it allocates memory and checks the allocation for the t_pl_im structure (abbreviated from t_player_images due to norminette indentation constraints in so_long.h when declaring this structure inside the game structure). It initializes the four player images to NULL (one for each direction), ensuring the program doesn't access uninitialized memory.

#### ➡️ 9b) init_mlx function (mlx_and_player_images_init_load_clean.c) - This function initializes the MiniLibX (MLX) graphics library, which is responsible for creating windows and handling graphical elements in the game. It assigns the result of mlx_init() to the game->mlx variable, initializing the connection to the graphical system. If it fails to initialize, the program exits. If successful, it assigns the creation of a window to the game->window variable using the mlx_new_window function. This function uses the game->mlx variable, calculates the window size (based on the number of columns and rows multiplied by TILE_SIZE, as defined in the so_long header), and sets the window title. If the window fails to be created, it calls mlx_destroy_display(game->mlx) to clean up resources associated with MLX, frees its memory, and exits the program.

#### ➡️ 9c) load_image function (player_images_funcs.c) - This function is responsible for loading various game images (textures). It assigns image variables, such as game->img_wall, by calling the mlx_xpm_file_to_image function, which reads from game->mlx, the image path in XPM format, and its size (height and width, with values derived from the predefined game->img_width and game->img_height).

#### ➡ The player images are imported separately because a single variable handles the player's four positions. After each player image is loaded, it checks for any errors. If an error occurs, it calls the free_game_resources function (mlx_and_player_images_init_load_clean.c), frees the img_player variable's memory, and exits. If successful, it destroys the image before loading the next one. After successfully loading all four player images, it reads a predefined player image to start the game. The last action of the load_image function is to check for errors in reading images other than the player's. In case of any errors, it frees game resources and exits.

###### ➡ free_game_resources function: This function calls cleanup_mlx, which checks if images are not NULL and destroys them. This includes destroying game->buffer (used in the double buffer function), the created window (game->window), and game->mlx by calling mlx_destroy_display and freeing this variable. It then cleans up player_images if game->player_images is not NULL. It cleans the non-NULL variables game->player->images->img_player_up, down, left, and right by calling the mlx_destroy_image function. It then frees game->player_images and sets this last variable to NULL. The free_game_resources function then proceeds to free both game->map and game->enemies if they are not NULL.

#### ➡️ 9d) init_double_buffer function (double_buffer_funcs.c) - The double buffer's purpose is to prevent rendering the entire map every time the player moves or a key or mouse event triggers rendering. Rendering each frame directly to the screen results in visible partial updates, causing screen blinking and flickering, an issue resolved by implementing a double buffer. The double buffer solves this problem by rendering all updates to an off-screen image (the buffer) first. Once the entire frame is ready, it is drawn to the screen in one go. This process repeats in a loop: render to the buffer, display the buffer, and repeat.

#### ➡ init_double_buffer function behavior: Using mlx_new_image, a new image is created, sized to match the window, using the game->mlx data to calculate the window size. It checks if the image is correctly created. The img_endian variable is initialized to 0, which is typically the default, especially for x86 architectures. A value of '0' usually means that the image data is stored in little-endian format (least significant byte first). The img_bits_per_pixel value is set to 32, meaning 32 bits (4 bytes) are used for each pixel for color information.
