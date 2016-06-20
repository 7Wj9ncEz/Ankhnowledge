Universidade de Brasília – Faculdade UnB Gama  
Disciplina: Técnicas de Programação  
Professor: Maurício Serrano  
Período: 1º/2016  
Data de entrega: 30 de Março de 2016  
Estudantes:  

**11/0025229** - *Átilla Gallio*

**11/0064879** - *Nicolas Boarin*

#Stylesheet - Ankhnowledge

##1. Comments

Comments must obey the following pattern.

######a) One-line comments must be written using a double slash '//' before the comment, followed by a space ‘ ‘ and a capital letter. Do not finish it with a period.

```C++
// At this point the song ~3knights.wpm will play
```

######b) Comments in blocks must be written between the '/\*' and '\*/'. For each new line, there must have an asterisk aligned with the previous one.

```C++
/*
 * Third act begins
 * Now the Y and X positions will switch places
 */
```

######c) Comments which precede methods must be written in blocks explaining its use and its return.

```C++
/*
 * Function called to check if mouse position is hovering over the tile
 * Returns: TRUE or FALSE if the mouse is inside the tile
 */
bool Tile::inside_tile()
{
	InputManager* input;
	input = InputManager::get_instance();

	return ((input->mouse_pos_x() > this->x) && (input->mouse_pos_x() < (this->x + this->tile->get_width())) &&
			(input->mouse_pos_y() > this->y) && (input->mouse_pos_y() < (this->y + this->tile->get_height())));

}
```

######d) Comments explaining one line of the code must precede the line.

```C++
 int index = 0;
    // Picks the length, height and layers from the map, indicated in the first line of the file
    fscanf_return = fscanf(map_file, "%d,%d,%f,%f,%d,%d,", &map_columns, &map_rows, &pos_x_offset, &pos_y_offset, &p1_position, &p2_position);
```
######e) Comments exceeding 80 characters must be broken into multiple lines following the block pattern:

```C++
/*
 * Around this point the game physics will change because of the
 * New chapter that begun so all X coordinates will be now become
 * Y coordinates and the same other way around
 */
```

######f) Comments that are important messages through the code must have 5 asterisks at the beginning and end of it.
```C++
/*****
 * Optimized Area
 * Don't edit unless you really know what you're doing
 *****/
```

## 2. Types and Names

######a) Names of Classes, Attributes, and Methods must follow the C (underscore) pattern, which consists in instead of capitalizing the initial letters of each word, let all letters (except for class names) keep them in lowercase and setting an underscore `_` in the middle before the next word.

######b) Classes names initiates with capital case.
```C++
Sprite::Sprite(std::string file) {
	surface = NULL;
	load(file);
	current_alpha = 255;
	number_ref = 0;
}
```

######c) Attributes names initiates with lower case.
```C++
int sprite_width = 0;
```

######d) Methods names initiates with lower case.
```C++
void Animation::reset_start_frame() {
	this->current_frame = start_frame;
}
```

######e) Constants names must be capitalized and use underscore between names.
```C++
// Number of maps
const NUMBER_OF_MAPS = 3;
```

######f) Only one variable must be declared per line.
```C++
float mouse_x;
float mouse_y;
bool is_pressed;
bool change_scene;
bool change_sprite;
```

##3. Strings

######a) Strings must be written between double quotes ` " " `;

######b) If Strings are constants they follow the same rules as then;

```C++
const MAP_LOCATION = "maps/map_locale.cpp";
```

##4. Indentation

######a) The indentation must be written by 2 spaces or an equivalent tab.

```C++
Sprite::~Sprite() {
	if (surface) {
		SDL_FreeSurface(surface);
	}

	else {
		// Do nothing
	}
}
```

##5. Braces

######a) Opening braces must be used one space after the the block structure.

######b) Closing braces must be written aligned with the statement which opened the block.

```C++
void Map::spawn_sand(int id) {
	tiles.at(id)->create_sand_block();
}
```

##6. Classes
Classes must be according to the following model:

######a) Just like creating a Method, there should explain what the class represents in the game context.

```C++
/*
* Class made to be created to show the game credits
*/
SceneCredits::SceneCredits(string scene_name) : Scene (scene_name) {
	this->sprite = new Sprite(SDLBase::resourcesPath + "animacao_creditos.png");
	this->sprite->incNumRef();
	this->spriteAnimation = new Animation(20,40,sprite,0);
}
```

##7. Control Structure: `if`

######a) There must be a blank space immediately after the keyword `if`.

######b) The comparison operators must start immediately after the parentheses `()`.

######c) The body must be written between braces, even when it is a single line.

######d) Blocks of `else if` or `else` must be initiated on the second line bellow of the closing braces.

######e) There must have an `else` block after all `if` or `else if` block.

######f) The key `{` will begin a line bellow the condition and close one line after it finishes `}`.

######g) There must have a blank space between the parentheses and the `if` condition.

######h) If your else doesn't necessarily is supposed to happen, log it also add `// Nothing to do`.

```C++
void Tile::set_clickable_tiles(Tile *origin, int reach, bool consider_block, bool clickable) {
	int i = 1;
	Tile *tile = origin;

	if (i <= reach && tile->get_up_tile()) {
		tile = tile->get_up_tile();

		if (!tile->get_character())	{

			if (!tile->get_block())	{
				tile->set_clickable(clickable);
			}

			else if (consider_block) {
				if (tile->get_block()->get_type() == "BlockSand" || tile->get_block()->get_type() == "BlockWater")	{
					// Do nothing
				}

				else	{
					tile->set_clickable(clickable);
				}
			}

			else {
			    // Do nothing
			}
		}

		else {
		    // Do nothing
		}

		Tile::setClickableTiles(tile, reach-1, consider_block, clickable);
	}

	else {
	    // Do nothing
	}

	tile = origin;
}
```

##8. Control structure: `while`

######a) `While` follows the `if` pattern:

```C++
while (count < num_maps) {
  sum_maps = sum_maps + 1;
}
```

##9. Control structure: `for`

######a) The `for` structure follows the `if` pattern.

######b) Semicolon must be placed immediately after the assignment and the comparison, and an empty space after it.

```C++
for (list<Game_object *>::iterator it = game_objects.begin(); it != game_objects.end(); it++) {
		(*it)->render(camera_x, camera_y);
}
```

##10. Control structure: `switch`

######a. Defaults and cases must not be indented;

######b) Case blocks and default blocks must be indented.

######c) `break` must be indented as well.

######d) Must also follow the `if` patterns.

```C++
void load_map( current_map ) {
  char* map_name = "";
  switch (current_map) {
    case DUNGEON:
      map_name = DUNGEON_NAME;
      break;

    case VILLAGE:
      map_name = VILLAGE_NAME;
      break;

    case RESIDENCE:
      map_name = RESIDENCE_NAME;
      break;

    case FIELD:
      map_name = FIELD_NAME;
      break;

    default:
      // Should never be reached. .
  }
}
```

##11. Asserts

######a) If it's inside a Function there must be a comment `// Asserts` on the line above it.

######b) Asserts must have their parentheses right after the word, unlike the Control Structures and more like a Function.

```C++
void Animation::render(int index, float pos_x, float pos_y) {

	// Asserts
	assert(index >= 0);
	assert(pos_x >= 0);
	assert(pos_y >= 0);

	int x = index % columns;
	int y = index / columns;

	int clip_x = x * sprite_width;
	int clip_y = y * sprite_height;

	animation->clip(clip_x, clip_y, sprite_width, sprite_height);
	animation->render(pos_x, pos_y);
}
```

##12. Tests

######a) If it's inside a Function there must be a comment `// Tests` on the line above it.

######b) Tests must have their parentheses right after the word, unlike the Control Structures and more like a Function.

######c) Because of the library `catch.hpp` all tests will be inside the functions it tests.

######c) It's structure is `TEST_CASE("Testing XXX", [Class]);`.

```C++
// Tests
TEST_CASE("Testing Animation Constructor", "[Animation]") {
	REQUIRE(this->animation == sprite);
	REQUIRE(this->sprite_width = sprite_width);
	REQUIRE(this->sprite_height = sprite_height);
	REQUIRE(this->columns =  animation->getWidth() / sprite_width);
	REQUIRE(this->detective = 0);
	REQUIRE(this->start_frame = direction * columns);
	REQUIRE(this->previous_direction = direction);
	REQUIRE(this->current_frame = start_frame);
	REQUIRE(this->animate_sprite = true);
	REQUIRE(this->finished_animation = false);
}
```
##13. Logs

######a) If it's inside a Function right at the beginning there must be a comment `// Init-Function Logs` on the line above it.

######b) If it's inside a Function, but in the middle there must be a comment `// Mid-Function Logs` on the line above it.

######c) If it's inside a Function, but at the end there must be a comment `// Post-Function Logs` on the line above it.

######d) It's structure is `log("log message", Class);`

######e) The library used is `#include "log.h"`.

```C++
// Init-Function Logs
log("Animation rendered", Animation);
log("render -> index" + index, Animation);
log("render -> pos_x" + pos_x, Animation);
log("render -> pos_y" + pos_y, Animation);

// Mid-Function Logs
log("render -> x" + x, Animation);
log("render -> y" + y, Animation);
log("render -> clip_x" + clip_x, Animation);
log("render -> clip_y" + clip_y, Animation);

// Post-Function Logs
log("render called clip()", Animation);
log("animate called render()", Animation);
log("render has ended", Animation);
```

##14. Coding language

###The program code must be made in English in its entirety.
