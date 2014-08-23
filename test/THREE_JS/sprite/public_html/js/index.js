var engine;

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
    var container = document.getElementById('canvas-container');
    var options = {
        positionIterations: 6,
        velocityIterations: 4,
        enableSleeping: false
    };
    
    engine = Matter.Engine.create(container, options);
    Matter.Engine.run(engine);    
}

function addToPhysics() {
    var world = engine.world;
    var rect = Matter.Bodies.rectangle(10, 10, 50, 50, { chamfer: chamfer });
    Matter.World.add(world, rect);    
}


