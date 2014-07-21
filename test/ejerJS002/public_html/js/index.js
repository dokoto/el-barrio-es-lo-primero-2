var game = new Phaser.Game(800, 600, Phaser.AUTO, '', { preload: preload, create: create, update:update, render: render });

function preload() {
    game.load.tilemap('map', 'js/assets/level3.json', null, Phaser.Tilemap.TILED_JSON);
    game.load.image('background', 'js/assets/fase_1_backgorund.png');
    game.load.spritesheet('character', 'js/assets/character.png', 30, 48);
}

var map; // The tilemap
var bg;
var layer; // A layer within a tileset
var player; // The player-controller sprite
var facing = "left"; // Which direction the character is facing (default is 'left')
var cursors; // A reference to the keys to use for input detection
var hozMove = 160; // The amount to move horizontally
var vertMove = -120; // The amount to move vertically (when 'jumping')

function create() {
    
    game.physics.startSystem(Phaser.Physics.P2JS);
    game.stage.backgroundColor = '#FFFFFF'; // white
    
    map = game.add.tilemap('map');
    bg = game.add.tileSprite(0, 0, 1670, 600, 'background');

    layer = map.createLayer('PatternLayer');
    layer.resizeWorld();
    
    obj1 = game.physics.p2.convertCollisionObjects(map, "ObjectsLayer");
    game.physics.p2.setPostBroadphaseCallback(checkIfCollide, this);
    
    player = game.add.sprite(50, 50, 'character');    
    game.physics.p2.enable(player);
    
    game.camera.follow(player);
    cursors = game.input.keyboard.createCursorKeys();

}

function update() {

    player.body.setZeroVelocity();

    // Check if the left arrow key is being pressed
    if (cursors.left.isDown)
    {
        // Set the 'player' sprite's x velocity to a negative number:
        //  have it move left on the screen.
        player.body.moveLeft(hozMove);

        // Check if 'facing' is not "left"
        if (facing !== "left")
        {
            // Set 'facing' to "left"
            facing = "left";
        }
    }
    // Check if the right arrow key is being pressed
    else if (cursors.right.isDown)
    {
        // Set the 'player' sprite's x velocity to a positive number:
        //  have it move right on the screen.
        player.body.moveRight(hozMove);

        // Check if 'facing' is not "right"
        if (facing !== "right")
        {
            // Set 'facing' to "right"
            facing = "right";
        }
    }
    else if (cursors.up.isDown)
    {
        player.body.moveUp(hozMove);
    }
    else if (cursors.down.isDown)
    {
        player.body.moveDown(hozMove);
    }

    // Check if 'facing' is "left"
    if (facing === "left") {
        // Set the 'player' to the second (1) frame
        //  ('facing' is "left")
        player.frame = 1;
    } else {
        // Set the 'player' to the first (0) frame
        //  ('facing' is "right").
        player.frame = 0;
    }

}  

function checkIfCollide(body1, body2)
{
    console.log(body1.x, body1.y, body2.x, body2.y);
    return true;
}

function render() {

    game.debug.body(player);

}
