# So_long - 42 Project

#### So_long is a game developed in C as part of the 42 curriculum, utilizing the MLX Graphics library. This project adheres to the rigorous norms and requirements set by the school, providing an excellent opportunity to deepen my knowledge of the C programming language. It has been one of the most enjoyable projects I've worked on so far.

![Screenshot from 2024-08-27 00-45-59](https://github.com/user-attachments/assets/87cffe26-f7c4-4824-907e-5723c4d4fb73)

#### Game Overview

##### The game features a simple yet engaging concept. The player must navigate through a map that includes essential elements such as walls, pathways, collectables, a player character, and an exit. The objective is to collect all items and reach the exit without losing all of your life points.
#### Key Features:

##### ▶️ Dynamic Map Reading: The game reads a predefined map that includes walls, pathways, collectables, and an exit.
##### ▶️ Player Movement and Textures: The player moves in different directions using predefined keys, either the arrow keys or WASD. When the player changes direction, their texture changes accordingly, providing visual feedback that reflects the direction they are facing. This adds a layer of polish to the gameplay, making the movement feel more dynamic and responsive.
##### ▶️ Enemies (Bonus Feature): In the bonus version, enemies are introduced. If the player encounters an enemy, they lose 10% of their life. The game ends if the player's life reaches 0. Additional features related to enemies include the ability to define their quantity, the randomness of their movements, their speed, and the duration they must wait before moving again. These customizable settings allow for varied and unpredictable gameplay, adding an extra layer of challenge for the player.
##### ▶️ Custom Textures: The collectables are represented as 5 escudos coins, a nod to the pre-Euro currency. The player character is Buzz Lightyear, and the enemies are represented by Zurg, inspired by my 5-year-old son's love for the character.
##### ▶️ Image Scaling: The game supports 32x32, 48x48, and 64x64 pixel image sizes, offering higher resolution for larger images. To change the game's resolution, simply update a single defined variable, TILE_SIZE, to the desired size. This straightforward adjustment makes it easy to scale the game's graphics according to your preference.
##### ▶️ On-Screen Information: The player can see their movement count, the number of collectables left, and their current life percentage. The player can only exit the game after collecting all items.
##### ▶️ Game Rendering: To prevent flickering during gameplay—caused by key presses, mouse movements, or other actions—double buffer rendering has been implemented. Instead of rendering directly to the screen, the game first renders to a buffer. Once complete, the entire image is then displayed on the screen at once. This technique ensures smooth and flicker-free visuals, enhancing the overall gaming experience.

##### This project has been a fantastic experience, allowing me to blend creativity with technical skills while adhering to the educational standards of 42.

# So_long - Functions explained

#### ▶️ 1) First, the main function checks whether the argc is equal to two (program + map file).

#### ▶️ 2) It initializes the function that contains the game structure variables (init_game_struct_variables).

#### ▶️ 3) The file descriptor (map) is read and checked.

#### ▶️ 4) The map_read function (located in support_functions.c) is called, which uses the get_next_line function. This function defines the line_count (row number) variable and the max_line_length (length of each row) variable within a loop.

#### ▶️ 5) The map_mem_allocate function (in support_functions.c) is executed, called by start_map_mem_allocate (in so_long.c). Since we already know the number of rows and columns in the map, memory for the map can be allocated.

#### ▶️ 6) Next, the main function calls the add_print_lines function (support_functions.c). This function uses get_next_line to read all the map lines. Each map row index is filled with the content of each line read by get_next_line. At the end, it prints out the content of each row (this part is not required by the project).

#### ▶️ 7) In the main function, the bonus "enemy" variables are initialized in the init_handle_enemy_vars function (handle_enemy_funcs.c).

###### ▶ First, it calls the check_map_dimensions function (handle_enemy_funcs.c), which checks if the map has the minimum rows and columns to handle "enemies." Some game structure variables are initialized or assigned (min_rows, min_columns, game->enemies, game->num_enemies, and game->lives). The necessary memory for enemies (t_enemy structure) is allocated.
###### ▶ The enemies are then initialized by looping through the enemies array. Each enemy position starts at (x:1, y:1), and an inner loop checks if the enemy is being placed on a position different from '0' (road). If it's not on the road, it keeps trying until it finds a valid position. The x and y positions of the enemy are defined by adding a random number to the max_line_length and line_count, subtracting 2 (to account for the map's wall boundaries). Once an enemy's starting position is defined, this value is assigned to the enemy's position. Additionally, a speed variable is assigned, determining the number of tiles an enemy moves in each movement (making it faster or slower). Each enemy's movement direction is determined by the rand function % 4 (one for each direction). The last variable, life, starts at 100.

#### ▶️ 8) Next, the main function calls the start_validations function (so_long.c), which in turn calls the validate_map function. If the map is valid, start_validations calls validate_reachability (check_reachability.c).

##### ➡️ 8a) validate_map (map_validator.c): This function checks if the map is a rectangle (check_rectangle), if it contains only valid characters (check_full_fill), if it has the required number of elements (check_map_element), and if the walls are closed off.

##### ➡️ 8b) validate_reachability (check_reachability.c): This function checks whether all items and exits are reachable and if the player is not blocked. It declares a variable f from the t_flood_fill_vars structure, which holds pointers to the map, its row and column sizes, and a visited grid. The init_visited function allocates memory for a 2D array at f->visited and sets all its values to 0, indicating that the positions haven't been visited yet.
###### ➡ The player's starting position is defined by the define_player_position function, with its coordinates stored in the game->player_x and game->player_y variables.
###### ➡ With the player's position set and the vars->visited array initialized, the flood_fill function searches the map to determine if every position can be reached by the player. It checks if the x and y coordinates are out of bounds, if the map content at each coordinate is '1' (wall), or if the position has already been visited. If any of these conditions are true, the function returns without further recursion and moves on to the next position. The recursive calls continue until no more positions can be explored.
###### ➡ The function then checks if the player's position is still 0. If so, it indicates that the player ('P') is either surrounded by walls, preventing any movement, or that a move was made in one direction, but it was impossible to return to the original position, marking it as 1.
###### ➡ Finally, check_c_e_reachability checks if all collectibles and exits are reachable by the player ('P'). It inspects the map coordinates to see if each was visited (i.e., if it is 1 or still 0).
###### ➡ An external function, free_flood_mem (free_mem_reachability.c), frees the memory allocated for f->visited. If the flag is 0 (indicating 'P', 'C', and 'E' are reachable), the memory is freed. If any elements are unreachable, the program exits, but before doing so, it frees the memory allocated for f->visited, game->map, and the enemy_array by calling this function with flag = 1.

#### ▶️ 9) The last function called in main is start_mlx_functions (so_long.c), which invokes several other functions:

##### ➡️ 9a) init_game_player_images function (mlx_and_player_images_init_load_clean.c) - First, it allocates memory and checks the allocation for the t_pl_im structure (abbreviated from t_player_images due to norminette indentation constraints in so_long.h when declaring this structure inside the game structure). It initializes the four player images to NULL (one for each direction), ensuring the program doesn't access uninitialized memory.

##### ➡️ 9b) init_mlx function (mlx_and_player_images_init_load_clean.c) - This function initializes the MiniLibX (MLX) graphics library, which is responsible for creating windows and handling graphical elements in the game. It assigns the result of mlx_init() to the game->mlx variable, initializing the connection to the graphical system. If it fails to initialize, the program exits. If successful, it assigns the creation of a window to the game->window variable using the mlx_new_window function. This function uses the game->mlx variable, calculates the window size (based on the number of columns and rows multiplied by TILE_SIZE, as defined in the so_long header), and sets the window title. If the window fails to be created, it calls mlx_destroy_display(game->mlx) to clean up resources associated with MLX, frees its memory, and exits the program.

##### ➡️ 9c) load_image function (player_images_funcs.c) - This function is responsible for loading various game images (textures). It assigns image variables, such as game->img_wall, by calling the mlx_xpm_file_to_image function, which reads from game->mlx, the image path in XPM format, and its size (height and width, with values derived from the predefined game->img_width and game->img_height).

###### ➡ The player images are imported separately because a single variable handles the player's four positions. After each player image is loaded, it checks for any errors. If an error occurs, it calls the free_game_resources function (mlx_and_player_images_init_load_clean.c), frees the img_player variable's memory, and exits. If successful, it destroys the image before loading the next one. After successfully loading all four player images, it reads a predefined player image to start the game. The last action of the load_image function is to check for errors in reading images other than the player's. In case of any errors, it frees game resources and exits.

###### ➡ free_game_resources function: This function calls cleanup_mlx, which checks if images are not NULL and destroys them. This includes destroying game->buffer (used in the double buffer function), the created window (game->window), and game->mlx by calling mlx_destroy_display and freeing this variable. It then cleans up player_images if game->player_images is not NULL. It cleans the non-NULL variables game->player->images->img_player_up, down, left, and right by calling the mlx_destroy_image function. It then frees game->player_images and sets this last variable to NULL. The free_game_resources function then proceeds to free both game->map and game->enemies if they are not NULL.

##### ➡️ 9d) init_double_buffer function (double_buffer_funcs.c) - The double buffer's purpose is to prevent rendering the entire map every time the player moves or a key or mouse event triggers rendering. Rendering each frame directly to the screen results in visible partial updates, causing screen blinking and flickering, an issue resolved by implementing a double buffer. The double buffer solves this problem by rendering all updates to an off-screen image (the buffer) first. Once the entire frame is ready, it is drawn to the screen in one go. This process repeats in a loop: render to the buffer, display the buffer, and repeat.

###### ➡ init_double_buffer function behavior: Using mlx_new_image, a new image is created, sized to match the window, using the game->mlx data to calculate the window size. It checks if the image is correctly created. The img_endian variable is initialized to 0, which is typically the default, especially for x86 architectures. A value of '0' usually means that the image data is stored in little-endian format (least significant byte first). The img_bits_per_pixel value is set to 32, meaning 32 bits (4 bytes) are used for each pixel for color information.


#### ➡️ 9e) The next function the program will read in start_mlx_functions is mlx_key_hook, an MLX function that handles keyboard input for the game. It listens for key events within the specified window and passes control to update_map_moves (mlx_render_hook_keys.c) whenever a key is pressed. This function then processes the key input and updates the game state accordingly.

###### ➡ update_map_moves function (mlx_render_hook_keys.c)
###### ➡ window_esc_key_press (escape_and_close_window.c): This function is triggered when the ESC key is pressed, which calls a new function to exit the window after freeing game resources.
###### ➡ cursor_move_key_press (move_player_key_define.c): This function defines the player’s movements when keys are pressed. The player moves according to the UP, DOWN, LEFT, or RIGHT keys using either the arrow keys or the WASD keys. It calls four functions—move_player_left, move_player_right, etc.—which check if the player’s intended direction is within bounds and not obstructed by a wall. If the move is valid, the player moves one position in the chosen direction. The function then creates a new image using the mlx_xpm_file_to_image function. If img_player is already defined, it is destroyed before the new image is assigned to img_player.
###### ➡ The function begins by defining the current element and setting the previous element (the TILE the player is moving from) to '0'. This is to update the image shown at the player's previous position after they move to a new position.
###### ➡ game->new_x and game->new_y are assigned the values of game->player_x and game->player_y, respectively. new_x and new_y represent the potential new position of the player, while game->player_x and game->player_y represent the current position before the move is confirmed.
###### ➡ The function then enters an if clause that governs the rest of its behavior. It checks if new_x or new_y are different from player_x or player_y, indicating that the player has moved. The cur_element variable represents the map image at the player’s new position coordinates. The next line calls the handle_items_and_exit function (in the same C file), which checks the value of cur_element. If cur_element is 'C', it updates the item_collected value. If cur_element is 'E', the function checks whether the player has collected all items; if so, the game exits. If not, the game continues. The function also increments the move_count variable by one for each movement, as required by the project specifications.
###### ➡ Returning to update_map_moves in the if clause, the player's new position on the map is assigned the value 'P'. The previous position (player_y and player_x) is assigned to prev_element, and then player_x and player_y (the previous positions) are updated to new_x and new_y (the new positions).
###### ➡ A new if clause checks the value of cur_element. If cur_element is 'C' or '0', prev_element is assigned the value '0'. If cur_element is '0', it remains '0'; if it is 'C', the item is collected by the player and must be changed to '0'. If cur_element is 'E', it remains 'E'.
###### ➡ The last line of the function calls check_player_lives (handle_enemy_funcs.c). This function loops through the defined number of enemies to check if, at any point, the player and an enemy occupy the same map coordinates. If they do, 10 points are deducted from the player’s total of 100. If the player’s life points reach 0 or less, the game exits after freeing or destroying all allocated memory and opened images.

#### ➡️ 9f) Back in start_mlx_functions, the next function is mlx_hook, which handles events like closing the window when the 'X' button is clicked. This function has five arguments:

###### ➡ The first argument specifies the game window where the event occurs.
###### ➡ The second argument is the event code DESTROY_NOTIFY, which has a value of 17 and is triggered when the window is about to be destroyed.
###### ➡ The third argument is set to 0 (no mask).
###### ➡ The fourth argument calls the close_window function to free resources.
###### ➡ The final argument is a pointer to the data passed to the function.

#### ➡️ 9g) The next function in start_mlx_functions is mlx_loop_hook, which continuously updates the game's state and rendering. It essentially sets up a loop that runs throughout the game's execution, repeatedly calling a function (loop_hook) to handle rendering and other tasks. This loop ensures that the game screen is refreshed and any necessary updates are made, such as moving objects or updating the player's position. Additionally, it can handle displaying text or updating the HUD (heads-up display) on the screen.

###### ➡ The loop_hook function (window_put_image_and_text.c)

###### ➡ The function begins by calling mlx_clear_window, which clears and refreshes the display of the game.

###### ➡ Next, it loads the render_game function (mlx_render_hook_keys.c). At the beginning of the render_game function, the variable buffer_data is assigned the result of mlx_get_data_addr. This is an MLX function for accessing and manipulating the pixel data of an image created with mlx_new_image. This function retrieves the address of the first byte of the image's data buffer, along with other important information about the image's format.
##### ➡ Arguments:
###### ➡ game->buffer: Off-screen buffer where the game will render graphics before displaying them on the screen.
###### ➡ &game->img_bits_per_pixel: A pointer to an integer where mlx_get_data_addr will store the number of bits used to represent a single pixel in the image. Typically, this is 32 bits (4 bytes).
###### ➡ &game->img_line_length: A pointer to an integer where the function will store the length of a line in bytes.
###### ➡ &game->img_endian: A value of 0 indicates that the data will be stored in little-endian format (least significant byte first).

###### ➡ The render_game function then loops across all the map's lines and columns, calling render_game_support_lines. Based on the content of each game map coordinate (tile), such as '1', '0', 'P', etc., it will call the function draw_tile_to_buffer at the appropriate x, y coordinates.

###### ➡ After completing the game map loop, the function proceeds to do the same with the render_enemy function. It loops through the number of enemies and uses draw_tile_to_buffer (double_buffer_funcs.c) to draw enemy images to the buffer.

##### ➡ draw_tile_to_buffer (double_buffer_funcs.c) is responsible for copying a tile image to a specific location within a larger image buffer, representing the entire game screen. This process renders each tile in the correct position on the screen. It has three arguments:
###### ➡ game: A pointer to the game structure containing all data related to the game.
###### ➡ image: A pointer to the tile image that will be drawn onto the buffer.
###### ➡ x, y: The coordinates (in tiles) where this tile should be drawn on the screen.

##### ➡ Variables:
###### ➡ tile_data: A pointer to the raw pixel data of the tile image.
###### ➡ buffer_pos: The position in the screen buffer where the pixel data should be copied.
###### ➡ tile_pos: The position in the tile image where the pixel data is taken from (retrieves color data from a pixel).
###### ➡ img_line_length: The length of a single line of the image in bytes (width of the buffer line).
###### ➡ pos: A loop counter that iterates over each pixel in the tile.

###### ➡ The line tile_data = mlx_get_data_addr(image, &game->img_bits_per_pixel, &img_line_length, &game->img_endian) retrieves the memory address of the raw pixel data for the image (the tile to be drawn) and fills in details like bits per pixel, line length, and endian settings.

##### ➡ A local variable pos is initialized to 0. This variable is used to loop through all the TILE bits. For example, if a TILE is 32x32, it will loop 1024 times (1024 bits). Inside this loop, two more local variables are defined: buffer_pos and tile_pos.
###### ➡ buffer_pos: buffer_pos = ((y * TILE_SIZE + pos / TILE_SIZE) * game->img_line_length + (x * TILE_SIZE + pos % TILE_SIZE) * (game->img_bits_per_pixel / 8));
###### ➡ This calculates the exact top-left corner position in the buffer where the pixel from the tile should be placed.
###### ➡ tile_pos: tile_pos = (pos / TILE_SIZE) * game->img_width + (pos % TILE_SIZE) * (game->img_bits_per_pixel / 8);
###### ➡ This calculates the exact position of the pixel that retrieves the color data from the tile.

###### ➡ Now that the exact locations of the pixel data to retrieve and where to copy it to are known, the data is copied using: *(int *)(game->buffer_data + buffer_pos) = *(int *)(tile_data + tile_pos);

##### ➡ Next, loop_hook loads the move_enemies function (handle_enemy_funcs.c).
##### ➡ This function uses the clock() function and the constant CLOCKS_PER_SEC from time.h, along with rand() from the stdlib.h header file.
###### ➡ clock(): Returns the current processor time used by the program in clock ticks. It is used to measure intervals.
###### ➡ CLOCKS_PER_SEC: This constant defines the number of clock ticks per second and is used to convert the clock ticks returned by clock() into seconds.
###### ➡ rand(): Generates a random number. If used with a modulus (e.g., rand() % 4), it generates a random number between 0 and 3.
##### ➡ Local variables:

###### ➡ static clock_t last_move_time = 0: A static variable to retain its value between function calls, used to calculate the time passed since the last enemy movement. It starts at 0 but will be updated to current_time during the function execution.

###### ➡ clock_t current_time = clock(): This updates during the program's execution to reflect the current time in clock ticks.

###### ➡ const double move_interval = 0.5: A constant value defining the minimum time interval (0.5 seconds) between enemy movements.

###### ➡ double elapsed_time = (double)(current_time - last_move_time) / CLOCKS_PER_SEC: This calculates the time elapsed since the last enemy movement.

###### ➡ After calculating elapsed_time, an if clause checks if elapsed_time is less than move_interval. If it is, the function returns early, and clock() is called again to update current_time until elapsed_time meets or exceeds move_interval, allowing the enemies to move again.

###### ➡ After updating last_move_time, the function loops through all enemies and calls check_enemy_moves_direction_boundaries (handle_enemies.c) to determine the enemies' direction.
###### ➡ This function checks if the enemies should move in one of four possible directions (rand() % 4). It ensures the enemy doesn’t move into a wall and has a 20% chance of staying still (rand() % 5). If the enemy moves, rand() % 4 determines the direction: '0' for UP, '1' for DOWN, '2' for LEFT, and '3' for RIGHT. The enemies' positions are then updated with the new positions defined in the previous if clauses.

##### ➡ The next functions loop_hook loads are display_move_count, display_items_collected, and display_player_lives (window_put_image_and_text.c).
###### ➡ These functions are similar in purpose: they display text information on the screen, such as movement count, collected items, and player lives.
##### ➡ display_move_count:
###### ➡ It begins by creating a variable rectangle of type t_draw_shape for drawing the background, with sub-variables for color, width, and height.
###### ➡ A string is created to hold the value of game->move_count, converted to a string using the ft_itoa function. Variables x and y handle the shape and text positions on the screen, with defined text and rectangle colors and rectangle size.
##### ➡ The draw_rectangle function is called, which uses mlx_pixel_put to create a rectangle at the specified position on the screen.
###### ➡ For example, if x = 30 and width = 80, the rectangle spans from pixel 25 to pixel 105 on the x-axis. Similarly, if y = 20 and height = 20, the rectangle spans from pixel 5 to pixel 25 on the y-axis.
###### ➡ After drawing the rectangle, the string is placed inside it on the screen using the mlx_string_put function, which displays the text at the specified x, y position with the defined color and content.

