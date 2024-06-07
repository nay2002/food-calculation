import pyglet
import os
import random
import time
import pyglet.media as media

# creating a costom window , tuning its configrations and maximizing the window on execution
window = pyglet.window.Window(
    width=1920, height=1080, resizable=True, caption="meteor maze"
)
window.set_fullscreen(True)

# initializing three hud labels at the rightmost , center , leftmost corners at the bottom of the screen.
hud_labels = [
    pyglet.text.Label(
        "",
        x=20,
        y=20,
        anchor_x="left",
        anchor_y="bottom",
    ),
    pyglet.text.Label(
        "",
        x=window.width // 2 - 250,
        y=20,
        anchor_x="center",
        anchor_y="bottom",
    ),
    pyglet.text.Label(
        "",
        x=window.width // 2 + 420,
        y=20,
        anchor_x="right",
        anchor_y="bottom",
    ),
]


# used as a flag variable to keep track of the time from the moment the game starts
start_time = None

"""relative path extraction 
    * @ param - media which is the name of the file with extension
    * the curren_dir - stores the path of the current directory of the python script
    * relative_dir - stores the path of the media file relative to the current directory"""


def get_media_path(media):
    current_dir = os.path.dirname(os.path.abspath(__file__))
    relative_dir = os.path.join(current_dir, media)
    return relative_dir


# importing the background sprite and scaling it with respect to the window dimensions
background_sprite = pyglet.sprite.Sprite(pyglet.image.load(get_media_path("bg2.jpg")))
background_sprite.scale_x = window.width / background_sprite.width
background_sprite.scale_y = window.height / background_sprite.height

# importing the player sprite and assigning its dimensions and position
player_sprite = pyglet.sprite.Sprite(pyglet.image.load(get_media_path("sp.png")))
player_sprite.height = 120
player_sprite.width = 120
player_sprite.position = 25, window.height / 2, 0


# imports the background music from the storage and plays it when the game starts
background_music = media.load(get_media_path("bg.mp3"))
player = media.Player()
player.queue(background_music)
player.play()


"""generation of individual meteor sprites
    * meteor_sprite - imports the meteor sprite from the storage
    @param:- None
    @algorithm: * initializes the dimensions and positions as per the given specifications
                * keeps track of the time from the moment the game starts
    @return: meteor_sprite"""


def create_meteor():
    meteor_sprite = pyglet.sprite.Sprite(
        pyglet.image.load(get_media_path("meteor.png"))
    )
    meteor_sprite.width = random.randint(80, 130)
    meteor_sprite.height = random.randint(50, 135)
    meteor_sprite.x = window.width - meteor_sprite.width
    meteor_sprite.y = random.randint(0, int(window.height - meteor_sprite.height / 2))

    global start_time
    if start_time is None:
        start_time = time.time()

    return meteor_sprite


# creating a variable for setting the number of meteors to be created per iteration
number_meteor = 135
meteor_sprites = []

# creating dictionary to store each individual meteors velocity and collision status
meteor_velocity = {}
meteor_collision = {}

# initializing the collision status of each meteor as false
for meteor in meteor_sprites:
    meteor_collision[meteor] = False

# creating meteors and storeing them in a list and assigning each meteor a random velocity
for meteor in range(number_meteor):
    meteor = create_meteor()
    meteor_sprites.append(meteor)
    meteor_velocity[meteor] = random.randint(60, 180)

"""enhancing contrast of the sprites
    * @param -  1 sprite - the sprite to be enhanced
                2 contrast_factor - the factor by which the sprite is to be enhanced
    * @algorithm - it enhances the contrast of the sprite by multiplying its color with the contrast factor 
                  and choses the min value between 255 and the claculated one
    * @return - None"""


def enhance_contrast(sprite, contrast_factor):
    sprite.color = (
        int(min(255, sprite.color[0] * contrast_factor)),
        int(min(255, sprite.color[1] * contrast_factor)),
        int(min(255, sprite.color[2] * contrast_factor)),
    )


enhance_contrast(background_sprite, 0.6)
enhance_contrast(player_sprite, 10.0)

# creating variables for player sprites speed , velocity and collision count with meteor
player_speed = 400
player_velocity = 0
collision_count = 0

# creating variabels to keep track of the respawn of the meteors
time_since_last_spawn = 0
respawn_interval = 15

# creating a flag variable to keep track of the game
game_over = False

# creating a list to store the bullets and assigning a common velocity to each keping track of the fire rate of the bullet
bullet_sprites = []
bullet_velocity = 600
bullet_shot = False


"""creating three hud labels at the bottom of the screen 
    * hits remaining  - number of collisions that the player_sprite can take  before it vanishes which is a maximum of 3 hits
    * time elapsed - this is a timer which starts with the game and shows how much time did the player survived
    * meteor respawn - it is a countdown which starts with the game and when the timer reaches 0.000 the meteors will respawn 
                       and the countdown will reset to 15.000"""


def update_hud_labels(dt):
    global start_time, game_over
    hits_remaining = 3 - collision_count

    if hits_remaining >= 0:
        hud_labels[0].text = f"Hits remaining: {hits_remaining}"

    if start_time is not None and not game_over:
        elapsed_time = time.time() - start_time
        minutes = int(elapsed_time // 60)
        seconds = int(elapsed_time % 60)
        milliseconds = int((elapsed_time % 1) * 1000)
        hud_labels[
            1
        ].text = f"Time elapsed: {minutes:02d}:{seconds:02d}.{milliseconds:03d}"

    meteoroid_respawn = float(respawn_interval - time_since_last_spawn)
    hud_labels[2].text = f"Meteoroid respawn: {meteoroid_respawn:.3f}"


"""assigning of the trigger keys
    * @param - symbol - it reffers to the trigger key for the specific job
               modifiers - it is used to indicate the keys pressed by the user which are not triggering an event
    * @algorithm - it assigns the trigger key to the player sprite 
                   for the movement in +ve y axis i is assigned 
                    and for the movement in -ve y axis k is assigned
                   the trigger key assigned to bullet is z and Space.
    *@return - None"""


@window.event
def on_key_press(symbol, modifiers):
    global player_velocity, bullet_shot
    if symbol == pyglet.window.key.UP or symbol == pyglet.window.key.I:
        player_velocity = player_speed
    elif symbol == pyglet.window.key.DOWN or symbol == pyglet.window.key.K:
        player_velocity = -player_speed
    elif (
        symbol == pyglet.window.key.SPACE
        or symbol == pyglet.window.key.Z
        and not bullet_shot
    ):
        bullet = pyglet.sprite.Sprite(pyglet.image.load(get_media_path("bullet.png")))
        bullet.update(scale=0.075)
        bullet.x = player_sprite.x + player_sprite.width
        bullet.y = player_sprite.y + player_sprite.height // 3 - 4
        bullet_sprites.append(bullet)
        bullet_shot = True


"""resetting the defalut values of sprites after the release of the trigger keys
    * @param - symbol - it reffers to the trigger key for the specific job
               modifiers - it is used to indicate the keys pressed by the user which are not triggering an event
    * @algorithm -it stops the action of the assigns the trigger key to the player sprite
                  it stops the action of the assigns the trigger key to the bullet sprite
    *@return - None"""


@window.event
def on_key_release(symbol, modifiers):
    global player_velocity, bullet_shot
    if (
        symbol == pyglet.window.key.UP or symbol == pyglet.window.key.I
    ) and player_velocity > 0:
        player_velocity = 0
    elif (
        symbol == pyglet.window.key.DOWN or symbol == pyglet.window.key.K
    ) and player_velocity < 0:
        player_velocity = 0
    elif symbol == pyglet.window.key.SPACE or symbol == pyglet.window.key.Z:
        bullet_shot = False


"""
Checks if two sprites collide with each other.

Parameters:
- `sprite1`: The first sprite to check for collision.
- `sprite2`: The second sprite to check for collision.

algorithm: checks if the x and y coordinates on left or right are overlapping simultaneously

Returns:
- `True` if the sprites collide.
- `False` if the sprites do not collide.
"""


def check_collision(sprite1, sprite2):
    if (
        sprite1.x < sprite2.x + sprite2.width
        and sprite1.x + sprite1.width > sprite2.x
        and sprite1.y < sprite2.y + sprite2.height
        and sprite1.y + sprite1.height > sprite2.y
    ):
        return True
    return False


"""showing game over screen
    * @param - dt - delta time
    * @algorithm - it shows the game over screen which has the time elapsed (time since the game started)for 5 secs
    * @return - None"""


def show_game_over_screen(dt):
    global game_over
    game_over = True
    window.clear()
    game_over_label = hud_labels[1]
    game_over_label.bold = True
    game_over_label.font_name = "Arial"
    game_over_label.font_size = 36
    game_over_label.color = (255, 215, 0, 255)
    game_over_label.x = window.width // 2
    game_over_label.y = window.height // 2
    game_over_label.anchor_x = "center"
    game_over_label.anchor_y = "center"
    game_over_label.draw()
    pyglet.clock.schedule_interval(lambda dt: pyglet.app.exit(), 5)


"""drawing of contents of the window
    * @param - None
    * @algorithm - it draws the background sprite , player sprite and meteors, bullets and hud labels if the game_over flag is false
    * @return - None"""


@window.event
def on_draw():
    window.clear()
    if game_over:
        show_game_over_screen(0)
    else:
        background_sprite.draw()
        player_sprite.draw()
        for meteor in meteor_sprites:
            meteor.draw()

        for label in hud_labels:
            label.draw()

        for bullet in bullet_sprites:
            bullet.draw()


"""gameing loop
    * @param - dt - delta time
    * @algorithm - it draws the background sprite , player sprite and meteors, bullets and hud labels in dt time interval.
    * @return - None"""


def game_loop(dt):
    update(dt)
    window.clear()
    background_sprite.draw()
    player_sprite.draw()
    for meteor in meteor_sprites:
        meteor.draw()

    update_hud_labels(dt)
    for label in hud_labels:
        label.draw()

    for bullet in bullet_sprites:
        bullet.x += bullet_velocity * dt


"""
- Manages sprite movement, collisions, and game mechanics.
- `update(dt)` function handles sprite positions, collisions, and interactions.
- Key variables: timers, sprite lists, velocities, collision counts.
- Meteors move left; player moves vertically within the window.
- Meteor spawn interval and speed increase over time.
- Tracks collisions to limit player hits; exceeding 3 triggers game over.
- Bullet-meteor collisions remove both sprites.
"""


def update(dt):
    global time_since_last_spawn, meteor_sprites, meteor_velocity, collision_count, game_over

    for meteor in meteor_sprites:
        meteor.x -= meteor_velocity[meteor] * dt
        if meteor.x + meteor.width < 0:
            meteor.x -= meteor.width
    player_sprite.y += player_velocity * dt
    if player_sprite.y + player_sprite.height > window.height:
        player_sprite.y = window.height - player_sprite.height
    elif player_sprite.y < 0:
        player_sprite.y = 0

    for meteor in meteor_sprites:
        collision_occurred = meteor_collision.get(meteor, False)
        if not collision_occurred and check_collision(player_sprite, meteor):
            collision_count += 1
            meteor_collision[meteor] = True
            if meteor_collision[meteor] == True:
                meteor.x = -1000

            if collision_count > 3:
                player_sprite.x = -1000

    time_since_last_spawn += dt

    if time_since_last_spawn >= respawn_interval:
        for _ in range(number_meteor):
            meteor = create_meteor()
            meteor_sprites.append(meteor)
            meteor_velocity[meteor] = random.randint(20, 70)

        time_since_last_spawn = 0

    execution_time = time.time()
    if execution_time % 45.05 == 0:
        for meteor in meteor_sprites:
            meteor_velocity[meteor] += 15

    if player_sprite.x == -1000:
        game_over = True
        show_game_over_screen(dt)

    for bullet in bullet_sprites:
        for meteor in meteor_sprites:
            if check_collision(bullet, meteor):
                meteor_sprites.remove(meteor)
                bullet_sprites.remove(bullet)
                break


pyglet.clock.schedule_interval(game_loop, 1 / 120.0)
pyglet.app.run()
