var mCanvas, ctx;
var FACTOR = 50;
var SHIFT;
var POINT_POSITION = {"x": 0, "y": 0};
var CAMERA_SIZE = {"w": 800, "h": 600};
var CAMERA_POSITION = {"x": 0, "y": 0};
var CAMERA_MARGIN = 50;
var CURSOR_UP = 38, CURSOR_RIGHT = 39, CURSOR_DOWN = 40, CURSOR_LEFT = 37;

$(document).ready(function() {
    
    $("#Draw").click(function() {
        drawPoint(convTOPX(
                {
                    "x": parseFloat($("#CoorX").val()),
                    "y": parseFloat($("#CoorY").val())
                }));
    });

    $("#Clean").click(function() {
        reDraw();
    });

    $(document).keydown(function(e) {
        console.log(e.keyCode);
        SHIFT = parseFloat($("#Shift").val());
        if (e.keyCode == CURSOR_UP)
        {
            reDraw();
            var calc = parseFloat($("#CoorY").val()) + SHIFT;
            $("#CoorY").val(parseFloat(calc).toFixed(2));
            POINT_POSITION = convTOPX({"x": parseFloat($("#CoorX").val()), "y": $("#CoorY").val()});
            drawPoint(
                    {
                        "x": POINT_POSITION.x,
                        "y": POINT_POSITION.y
                    });
            drawCamera({"x": CAMERA_POSITION.x, "y": CAMERA_POSITION.y, "w": CAMERA_SIZE.w, "h": CAMERA_SIZE.h});
            drawPointCoords({"x": parseFloat($("#CoorX").val()), "y": parseFloat($("#CoorY").val())});
        }
        else if (e.keyCode == CURSOR_RIGHT)
        {
            reDraw();
            var calc = parseFloat($("#CoorX").val()) + SHIFT;
            $("#CoorX").val(parseFloat(calc).toFixed(2));
            POINT_POSITION = convTOPX({"x": parseFloat($("#CoorX").val()), "y": $("#CoorY").val()});
            drawPoint(
                    {
                        "x": POINT_POSITION.x,
                        "y": POINT_POSITION.y
                    });
            followPoint(POINT_POSITION);
            drawPointCoords({"x": parseFloat($("#CoorX").val()), "y": parseFloat($("#CoorY").val())});
        }
        else if (e.keyCode == CURSOR_DOWN)
        {
            reDraw();

            var calc = parseFloat($("#CoorY").val()) - SHIFT;
            $("#CoorY").val(parseFloat(calc).toFixed(2));
            POINT_POSITION = convTOPX({"x": parseFloat($("#CoorX").val()), "y": $("#CoorY").val()});
            drawPoint(
                    {
                        "x": POINT_POSITION.x,
                        "y": POINT_POSITION.y
                    });
            drawCamera({"x": CAMERA_POSITION.x, "y": CAMERA_POSITION.y, "w": CAMERA_SIZE.w, "h": CAMERA_SIZE.h});
            drawPointCoords({"x": parseFloat($("#CoorX").val()), "y": parseFloat($("#CoorY").val())});
        }
        else if (e.keyCode == CURSOR_LEFT)
        {
            reDraw();
            var calc = parseFloat($("#CoorX").val()) - SHIFT;
            $("#CoorX").val(parseFloat(calc).toFixed(2));
            POINT_POSITION = convTOPX({"x": parseFloat($("#CoorX").val()), "y": $("#CoorY").val()});
            drawPoint(
                    {
                        "x": POINT_POSITION.x,
                        "y": POINT_POSITION.y
                    });

            followPoint(POINT_POSITION);
            drawPointCoords({"x": parseFloat($("#CoorX").val()), "y": parseFloat($("#CoorY").val())});
        }

    });

    mCanvas = document.getElementById("dLayer");
    ctx = mCanvas.getContext("2d");
    CAMERA_POSITION.x = (mCanvas.width - CAMERA_SIZE.w) / 2;
    CAMERA_POSITION.y = 0;
    initGraph();
    initTextRefs();
    POINT_POSITION = convTOPX({"x": parseFloat($("#CoorX").val()), "y": $("#CoorY").val()});
    drawCamera({"x": CAMERA_POSITION.x, "y": CAMERA_POSITION.y, "w": CAMERA_SIZE.w, "h": CAMERA_SIZE.h});
});

function followPoint(point)
{
    if ((point.x - CAMERA_POSITION.x) < CAMERA_MARGIN)
    {
        if (CAMERA_POSITION.x - CAMERA_MARGIN > 0)
            CAMERA_POSITION.x -= SHIFT * FACTOR;
        else
            CAMERA_POSITION.x = 0;
    }
    else if ((point.x - CAMERA_POSITION.x) >= (CAMERA_SIZE.w - CAMERA_MARGIN))
    {
        if (CAMERA_POSITION.x + CAMERA_SIZE.w < mCanvas.width - CAMERA_MARGIN)
            CAMERA_POSITION.x += SHIFT * FACTOR;
        else
            CAMERA_POSITION.x = mCanvas.width - CAMERA_SIZE.w;
    }

    drawCamera({"x": CAMERA_POSITION.x, "y": CAMERA_POSITION.y, "w": CAMERA_SIZE.w, "h": CAMERA_SIZE.h});
}

function drawCamera(rect)
{
    ctx.beginPath();
    ctx.rect(rect.x, rect.y, rect.w, rect.h);
    ctx.strokeStyle = "green";
    ctx.stroke();
}

function reDraw()
{
    console.log("Limpiando Pantalla");
    ctx.clearRect(0, 0, mCanvas.width, mCanvas.height);
    initGraph();
    initTextRefs();
}

function initGraph() {
    ctx.beginPath();
    ctx.strokeStyle = "black";
    ctx.moveTo(mCanvas.width / 2, 0);
    ctx.lineTo(mCanvas.width / 2, mCanvas.height);
    ctx.moveTo(0, mCanvas.height / 2);
    ctx.lineTo(mCanvas.width, mCanvas.height / 2);
    ctx.stroke();
}

function initTextRefs() {
    ctx.font = "8px Verdana";

    ctx.fillText("(0px, 0px)|(" + -toCoor(mCanvas.width / 2) + ", " + toCoor(mCanvas.height / 2) + ")", 2, 8);
    ctx.fillText("(" + mCanvas.width / 2 + ", " + mCanvas.height / 2 + ")|(0, 0)", mCanvas.width / 2 + 2, mCanvas.height / 2 - 2);
    ctx.fillText("0px," + mCanvas.height + ")|(" + -toCoor(mCanvas.width / 2) + ", " + -toCoor(mCanvas.height / 2) + ")", 2, mCanvas.height - 2);
    ctx.fillText("(" + mCanvas.width + "px, " + mCanvas.height + "px)|(" + toCoor(mCanvas.width / 2) + ", " + -toCoor(mCanvas.height / 2) + ")",
            mCanvas.width - 115, mCanvas.height - 2);
    ctx.fillText("(" + mCanvas.width + "px,0px)|(" + toCoor(mCanvas.width / 2) + ", " + toCoor(mCanvas.height / 2) + ")",
            mCanvas.width - 95, 8);
}

function toPX(coor) {
    return coor * FACTOR;
}

function toCoor(px) {
    return px / FACTOR;
}

function drawPoint(PxPoint) {
    ctx.beginPath();
    ctx.arc(PxPoint.x, PxPoint.y, 2, 0, 2 * Math.PI);
    ctx.fillStyle = 'black';
    ctx.fill();
    ctx.stroke();

    ctx.beginPath();
    ctx.strokeStyle = "blue";
    ctx.moveTo(0, PxPoint.y);
    ctx.lineTo(mCanvas.width, PxPoint.y);
    ctx.moveTo(PxPoint.x, 0);
    ctx.lineTo(PxPoint.x, mCanvas.height);
    ctx.stroke();
}

function drawPointCoords(CoorPoint)
{
    ctx.fillText("(" + (parseInt(POINT_POSITION.x) - parseInt(CAMERA_POSITION.x)) + "px, " + parseInt(POINT_POSITION.y) + "px)|" +
            "(" + parseInt(POINT_POSITION.x) + "px, " + parseInt(POINT_POSITION.y) + "px)|("
            + parseFloat(CoorPoint.x).toFixed(2) + ", " + parseFloat(CoorPoint.y).toFixed(2) + ")",
            POINT_POSITION.x + 5, POINT_POSITION.y + 9);
}

function convTOPX(CoorPoint)
{
    var PxPoint = {};
    console.log("CoorPoint: (" + CoorPoint.x + ", " + CoorPoint.y + ")");

    if (CoorPoint.x < 0)
        PxPoint.x = (mCanvas.width / 2) - (Math.abs(CoorPoint.x) * FACTOR);
    else
        PxPoint.x = (mCanvas.width / 2) + (Math.abs(CoorPoint.x) * FACTOR);

    if (CoorPoint.y < 0)
        PxPoint.y = (mCanvas.height / 2) + (Math.abs(CoorPoint.y) * FACTOR)
    else
        PxPoint.y = (mCanvas.height / 2) - (Math.abs(CoorPoint.y) * FACTOR)

    console.log("PxPoint: (" + PxPoint.x + ", " + PxPoint.y + ")");
    
    return PxPoint;
}

