var scene, camera, debugRenderer, renderer;
var geometry, material, mesh;
var physicsWorld, ball, ground, bounds, square;
var stats;

$(document).ready(function() {
    initPhysics();
    addToPhysics();
    Physics.util.ticker.start();

    window.addEventListener('resize', function() {
        renderer.el.width = window.innerWidth;
        renderer.el.height = window.innerHeight;
    });

});

function initPhysics() {

    physicsWorld = Physics({
        // set the timestep
        timestep: 1000.0 / 160,
        // maximum number of iterations per step
        maxIPF: 16,
        // set the integrator (may also be set with world.add())
        integrator: 'verlet'
    });

    var gravity = Physics.behavior('constant-acceleration', {
        acc: {x: 0, y: 0.0004} // this is the default
    });

    var viewportBounds = Physics.aabb(0, 0, window.innerWidth, window.innerHeight);
    physicsWorld.add(Physics.behavior('edge-collision-detection', {
        aabb: viewportBounds,
        restitution: 1,
        cof: 5
    }));

    physicsWorld.add(gravity);
    gravity.setAcceleration({x: 0, y: -0.0004});

    physicsWorld.add(Physics.behavior('body-impulse-response'));
    physicsWorld.add(Physics.behavior('constant-acceleration'));
    physicsWorld.add(Physics.behavior('body-collision-detection'));
    physicsWorld.add(Physics.behavior('sweep-prune'));
    /*
     debugRenderer = Physics.renderer('canvas', {
     el: 'element-id',
     width: window.innerWidth,
     height: window.innerHeight,
     meta: true, // don't display meta data
     styles: {
     // set colors for the circle bodies
     'circle': {
     strokeStyle: 'hsla(60, 37%, 17%, 1)',
     lineWidth: 1,
     fillStyle: 'hsla(60, 37%, 57%, 0.8)',
     angleIndicator: 'hsla(60, 37%, 17%, 0.4)'
     },
     'rectangle': {
     strokeStyle: 'hsla(60, 37%, 17%, 1)',
     lineWidth: 1,
     fillStyle: 'hsla(60, 37%, 57%, 0.8)'
     }
     }
     });
     */

    renderer = Physics.renderer('pixi', {
        el: 'viewport', // The DOM element to append the stage to
        width: window.innerWidth,
        height: window.innerHeight,
        meta: true, // Turns debug info on/off
        styles: {
            // set colors for the circle bodies
            'color': '0x66FF99',
            'point': '0xE8900C',
            'circle': {
                strokeStyle: '0xE8900C',
                lineWidth: 3,
                fillStyle: '0xD5DE4C',
                angleIndicator: '0xE8900C'
            },
            'convex-polygon': {
                strokeStyle: '0xE8900C',
                lineWidth: 3,
                fillStyle: '0xD5DE4C',
                angleIndicator: '0xE8900C'
            },
            'rectangle': {
                strokeStyle: '0xE8900C',
                lineWidth: 3,
                fillStyle: '0xD5DE4C',
                angleIndicator: '0xE8900C'
            }
        }
    });

    physicsWorld.add(renderer);

    physicsWorld.on('collisions:detected', function(data) {
        var c;
        for (var i = 0, l = data.collisions.length; i < l; i++) {
            c = data.collisions[ i ];
            if (c.bodyA.collide) {
                c.bodyA.collide(c.bodyB);
            }
            if (c.bodyB.collide) {
                c.bodyB.collide(c.bodyA);
            }
        }
    });

    Physics.body.mixin('collide', function(other) {
        if (other) {
            // do some default action
        }
        return true;
    });

}

function addToPhysics() {
    ball = Physics.body('circle', {
        x: 10, // x-coordinate
        y: 0, // y-coordinate
        vx: 0.11, // velocity in x-direction
        vy: 0.11, // velocity in y-direction
        radius: 25
    });
    physicsWorld.add(ball);

    square = Physics.body('rectangle', {
        x: 0,
        y: 500,
        width: 500,
        height: 20
    });
    physicsWorld.add(square);
}

Physics.util.ticker.on(function(time) {    
    physicsWorld.render();
    physicsWorld.step(time);
});

